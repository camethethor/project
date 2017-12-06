#include "LoginSession.h"
#include "Networkhandler.h"
#include "Dummy.h"
#include "Errcode.h"
#include "config.h"

LoginSession::LoginSession(Dummy* dmy )
: Session( INVALID_SOCKET ), _dummy(dmy)
{
}

LoginSession::~LoginSession(void)
{
}

bool LoginSession::Initialize()
{
	return true;
}

bool LoginSession::OnCreate()
{
	if( !ConnectTo( LOGINSERVER_IP, LOGINSERVER_PORT ) )
		return false;

	NetworkHandler::GetInstance()->Associate( ( HANDLE )_sock, ( ULONG_PTR )this );

	if( false == Session::OnCreate())
		return false;

	return true;
}

void LoginSession::OnDestroy()
{
	Session::OnDestroy();
}

int LoginSession::PacketParsing( const char* pRecvBuffer, const int nRecvSize )
{
	Packet packet;
	packet.CopyToBuffer( pRecvBuffer, nRecvSize );

	if( packet.IsValidHeader() == false )
	{
		ForcedDisconnect( INVALID_HEADER );
		return INVALID_HEADER;
	}

	return _dummy->MessageProc(packet);
}


int LoginSession::SendPacket( Packet& packet )
{
	return Session::SendPacket( packet.GetPacketBuffer(), packet.GetPacketSize());
}

