#include "GameSession.h"
#include "Protocol.h"
#include "Networkhandler.h"
#include "errcode.h"
#include "Config.h"
#include "DummyManager.h"

GameSession::GameSession( Dummy* dmy )
: Session( INVALID_SOCKET ), _dummy(dmy)
{
}

GameSession::~GameSession(void)
{
}


bool GameSession::OnCreate()
{
	if( !ConnectTo( GAMESERVER_IP, GAMESERVER_PORT ) )
		return false;

	NetworkHandler::GetInstance()->Associate( ( HANDLE )_sock, ( ULONG_PTR )this );

	if( false == Session::OnCreate())
		return false;
	
	DummyManager::GetInstance()->IncreaseActiveCount();
	return true;
}

void GameSession::OnDestroy()
{
	DummyManager::GetInstance()->DecreaseActiveCount();
	Session::OnDestroy();
}

int GameSession::PacketParsing( const char* pRecvBuffer, const int nRecvSize )
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


int GameSession::SendPacket( Packet& packet )
{
	return Session::SendPacket( packet.GetPacketBuffer(), packet.GetPacketSize());
}

