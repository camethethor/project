#pragma once
#include "session.h"
#include "Packet.h"

class Dummy;
class LoginSession : public Session
{
public:
	LoginSession(Dummy* dmy );
	virtual ~LoginSession(void);

	bool Initialize();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual int SendPacket( Packet& packet  );

private:
	virtual int PacketParsing( const char* pRecvBuffer, const int nRecvSize );

private:
	Dummy*	_dummy;
};
