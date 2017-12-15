#include "Session.h"
#include "NetworkHandler.h"
#include "errcode.h"
#include <mstcpip.h>

Session::Session( SOCKET s, int max_sending_size, int recv_buf_size )
: _sock( s ), _recv_packet_size( 0 ), _event_hdle( INVALID_HANDLE_VALUE ), _active( false ), 
_send_packet_size( 0 ), _max_send_packet_size( max_sending_size ), _recv_buffer( NULL ), _recv_buf_size( recv_buf_size )
{
	if( !_recv_buffer )
	{
		_recv_buffer = new char[_recv_buf_size];
		memset( _recv_buffer, 0, _recv_buf_size );
	}

	_event_hdle = ::WSACreateEvent();
	strcpy_s( _ip, "0.0.0.0" );
}

Session::~Session()
{
	if( _event_hdle != INVALID_HANDLE_VALUE )
	{
		WSACloseEvent( _event_hdle );
		_event_hdle = INVALID_HANDLE_VALUE;
	}

	OnDestroy();

	if( _recv_buffer )
	{
		delete _recv_buffer;
		_recv_buffer = NULL;
	}
}

bool Session::OnCreate()
{
	_recv_packet_size = 0;

	if( _sock != INVALID_SOCKET )
	{
		GETIP gIP;
		SOCKADDR_IN sockAddr;
		int size = sizeof( sockAddr );

		if( ::getpeername( _sock, ( SOCKADDR* )&sockAddr, &size ) != SOCKET_ERROR )
		{
			gIP.ip = sockAddr.sin_addr.S_un.S_addr;
			sprintf_s( _ip, "%d.%d.%d.%d", gIP.bit_ip.ip_1, gIP.bit_ip.ip_2, gIP.bit_ip.ip_3, gIP.bit_ip.ip_4 );
		}
		else
			return false;

		_active = true;
		ReceivePost();
		return true;
	}
	else
	{
		CloseConnection();
		return false;
	}
}

void Session::OnDestroy()
{
	_active = false;
	CloseConnection();

	_recv_packet_size = 0;
	_send_packet_size = 0;
	memset( _recv_buffer, 0, _recv_buf_size );	
}

void Session::SetSocket( SOCKET sock )
{
	_sock = sock;

	DWORD bytes = 0;
	WSAIoctl( _sock, SIO_KEEPALIVE_VALS, &_keep_alive, sizeof( _keep_alive ), NULL, NULL, &bytes, &_recv_overlap, NULL );
}

bool Session::ConnectTo( const char* address, WORD port )
{
	CloseConnection();

	_sock = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED );
	if( _sock == INVALID_SOCKET )
		return false;

	bool reuse = true;
    ::setsockopt( _sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof( reuse ) );

	DWORD dwBytes = 0;
	WSAIoctl( _sock, SIO_KEEPALIVE_VALS, &_keep_alive, sizeof(TCP_KEEPALIVE), NULL, NULL, &dwBytes, &_recv_overlap, NULL );
	
	DWORD ret_ip = ::inet_addr( address );
	
	if( INADDR_NONE == ret_ip )		// DNS 일 경우
	{
		HOSTENT FAR * lphostent = gethostbyname( address );
		
		if( !lphostent )
			return false;

		_domain_name = address;
		ret_ip = 0;
		memcpy( &ret_ip, lphostent->h_addr, sizeof( DWORD ) );
	}

	SOCKADDR_IN serv_sock_addr;
	::ZeroMemory( &serv_sock_addr, sizeof( serv_sock_addr ) );
	serv_sock_addr.sin_family			= AF_INET;
	serv_sock_addr.sin_addr.s_addr		= ret_ip;
	serv_sock_addr.sin_port				= htons( port );

	if( ::connect( _sock, ( struct sockaddr* )&serv_sock_addr, sizeof( serv_sock_addr ) ) )
	{
		CloseConnection();
		return false;
	}

	return true;
}

void Session::CloseConnection()
{
	if( _sock == INVALID_SOCKET )
		return;

	::shutdown( _sock, SD_BOTH );
	::closesocket( _sock );
	_sock = INVALID_SOCKET;
}

void Session::ForcedDisconnect( int nErrorCode )
{
	if( _active && NetworkHandler::GetInstance()->GetIOCPHandle() != INVALID_HANDLE_VALUE )
	{
		PostQueuedCompletionStatus( NetworkHandler::GetInstance()->GetIOCPHandle(), 0, (ULONG_PTR)this, &_recv_overlap );
	}
	
	_active = false;
}

int Session::SendPacket( char* packet_buf, int nSize )
{
	if( _sock == INVALID_SOCKET )
		return 0;

	DWORD	send_bytes = 0;
	DWORD	flags		= 0;
	int		io_ret = 0;
	WSABUF	wsaBuffer;

	::ZeroMemory( &_send_overlap, sizeof( OVERLAPPEDEX ) );
	_send_overlap._flags = ASYNCFLAG_SEND;

	wsaBuffer.buf = packet_buf;
	wsaBuffer.len = nSize;

	io_ret = WSASend(	_sock, &wsaBuffer, 1, &send_bytes, flags, (OVERLAPPEDEX *)&_send_overlap, NULL);

	if( SOCKET_ERROR == io_ret )
	{
		int nErrorCode = WSAGetLastError();
		if( nErrorCode != ERROR_IO_PENDING )
		{
			if( nErrorCode == WSAECONNRESET || nErrorCode == WSAENETRESET || nErrorCode == WSAENOTCONN || nErrorCode == WSAECONNABORTED )
			{
				ForcedDisconnect( nErrorCode );
			}
			return 0;
		}
	}

	_send_packet_size += send_bytes;

	if( _send_packet_size > _max_send_packet_size || _send_packet_size < -_max_send_packet_size )
	{
		ForcedDisconnect( SENDINGPACKETSIZE_FULL );
	}

	return send_bytes;
}

bool Session::ReceivePost()
{
	if( _sock == INVALID_SOCKET )
		return false;

	DWORD	recv_bytes = 0;
	DWORD	flags = 0;
	DWORD   buf_size = _recv_buf_size - _recv_packet_size;
	int		io_ret = 0;
	WSABUF	wsaBuffer;

	::ZeroMemory( &_recv_overlap, sizeof( OVERLAPPEDEX ) );
	_recv_overlap._flags = ASYNCFLAG_RECEIVE;

	wsaBuffer.buf = _recv_buffer + _recv_packet_size;
	wsaBuffer.len = buf_size;

	io_ret = WSARecv(	_sock, &wsaBuffer, 1, &recv_bytes, &flags, (OVERLAPPEDEX *)&_recv_overlap, NULL);

	if( SOCKET_ERROR == io_ret )
	{
		int nErrorCode = WSAGetLastError();
		if( nErrorCode != ERROR_IO_PENDING )
		{
			if( nErrorCode == WSAECONNRESET || nErrorCode == WSAENETRESET || nErrorCode == WSAENOTCONN || nErrorCode == WSAECONNABORTED )
			{
				ForcedDisconnect( nErrorCode );
			}
			return false;
		}
	}
	return true;
}

void Session::Dispatch( DWORD transfer_bytes, OVERLAPPED* ov )
{
	if( transfer_bytes == 0 )
		return;

	OVERLAPPEDEX* overlapped = ( OVERLAPPEDEX* )ov;

	switch( overlapped->_flags )
	{
	case ASYNCFLAG_SEND:
		_send_packet_size -= transfer_bytes;
		break;

	case ASYNCFLAG_RECEIVE:
		DispatchReceive( transfer_bytes );
		return;
	}
}

void Session::DispatchReceive( DWORD transfer_bytes )
{
	_recv_packet_size += transfer_bytes;

	char * pReadPivot = _recv_buffer;

	while( _recv_packet_size > 0 )
	{
		if( _active )
		{
			int nPacketSize = PacketParsing( pReadPivot, _recv_packet_size );

			if( nPacketSize > 0 )
			{
				_recv_packet_size -= nPacketSize;
				pReadPivot += nPacketSize;
			}
			else
			{
				//! PacketParsing() 후 ForcedDisconnect() 를 호출했다면 _active 는 false
				//! 따라서 ReceivePost() 를 호출하지 않는다.
				if( _active )
					break;
				else
					return;
			}
		}
		else
			return;
	}

	if( _recv_packet_size > 0 )
	{
		::memmove( _recv_buffer, pReadPivot, _recv_packet_size );
	}

	if( _active )
		ReceivePost();
}

bool Session::IsConnected()
{
	if( _event_hdle == INVALID_HANDLE_VALUE || _sock == INVALID_SOCKET )
		return false;

	WSANETWORKEVENTS netEvent;
	bool ret = false;

	::ZeroMemory( &netEvent, sizeof( netEvent ) );
	::WSAEventSelect( _sock, _event_hdle, FD_READ | FD_CLOSE );
	::WSAEnumNetworkEvents( _sock, _event_hdle, &netEvent );

	ret = ( ( netEvent.lNetworkEvents & FD_CLOSE ) == FD_CLOSE );

	return !(ret);
}