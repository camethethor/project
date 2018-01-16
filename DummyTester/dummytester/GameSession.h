#pragma once
#include "session.h"
#include "Packet.h"

const int MAX_NICKNAME_LENGTH = 16;
const int MAX_NICKFLAG_LENGTH = 4;

class Dummy;
class GameSession : public Session
{
public:
	GameSession( Dummy* dmy );
	virtual ~GameSession(void);
	
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual int SendPacket( Packet& packet );

private:
	virtual int PacketParsing( const char* pRecvBuffer, const int nRecvSize );

private:
	Dummy*	_dummy;
};
