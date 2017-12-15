#pragma once

#include <winsock2.h>
#include <string>

const int MAX_SENDINGPACKETSIZE	= (1024*20);
const int DATABUFFER_SIZE		= (1024*8);

class Session
{
private:
	enum IO_FLAG 
	{ 
		ASYNCFLAG_SEND = 0x01,
		ASYNCFLAG_RECEIVE = 0x02,
	};

	struct BIT_IP 
	{
		DWORD ip_1 : 8;
		DWORD ip_2 : 8;
		DWORD ip_3 : 8;
		DWORD ip_4 : 8;
	};

	typedef union _GETIP
	{
		DWORD	ip;
		BIT_IP	bit_ip;
	} GETIP;

	typedef struct OVERLAPPEDEX : OVERLAPPED
	{
		DWORD _flags;
	} OVERLAPPEDEX;

	typedef struct tcp_keepalive 
	{
		u_long  onoff;
		u_long  keepalivetime;
		u_long  keepaliveinterval;
	} TCP_KEEPALIVE;

public:
	Session( SOCKET s, int max_sending_size = MAX_SENDINGPACKETSIZE, int recv_buf_size = DATABUFFER_SIZE );
	virtual ~Session() = 0;

	virtual bool OnCreate();
	virtual	void OnDestroy();

	void Dispatch( DWORD transfer_bytes, OVERLAPPED* ov );

	SOCKET GetSocketValue(){ return _sock; }
	OVERLAPPEDEX& GetOverlappedValue() { return _recv_overlap; }

	const char* GetIP() { return _ip; }
	const WORD GetPort() { return _port; }
	const std::string& GetDomainName() { return _domain_name; }
	
	bool IsConnected();
	bool IsActive() { return _active; }

	void SetSocket( SOCKET hSocket );
	int SendPacket( char* packet_buf, int nSize );

	bool ConnectTo( const char* address, WORD wPort );
	void CloseConnection();
	void ForcedDisconnect( int nErrorCode );

protected:		
	virtual int PacketParsing( const char* pRecvBuffer, const int nRecvSize ) = 0;
	virtual void DispatchReceive( DWORD transfer_bytes );

private:
	bool ReceivePost();

protected:
	SOCKET			_sock;			
	char			_ip[32];		
	std::string		_domain_name;	
	WORD			_port;			
	bool			_active;		

private:
	TCP_KEEPALIVE		_keep_alive;
	OVERLAPPEDEX		_send_overlap;
	OVERLAPPEDEX		_recv_overlap;

	char*		_recv_buffer;	
	const int	_recv_buf_size;	
	int			_recv_packet_size;

	HANDLE		_event_hdle;
	int			_send_packet_size;	
	const int	_max_send_packet_size;
};
