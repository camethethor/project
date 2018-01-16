#include "THDummy.h"
#include "protocol.h"
#include "errcode.h"
#include "config.h"

THDummy::THDummy(const unsigned long id) : Dummy(id)
{
}

THDummy::~THDummy(void)
{
}

void THDummy::Run()
{
	if( false == LoginSessionRun() )
	{
		Destroy();
		return;
	}
	
	Packet sendmsg( SF_LOGIN_REQ );
	sendmsg << TH_CLIENT_VERSION << static_cast<long>(_id) << static_cast<long>(GetTickCount()) << "account" << "LKAJDSJDUW!@#KDD1" << "aa";
	_login_session->SendPacket(sendmsg);
}

int THDummy::LocalMessageProc(Packet& packet)
{
	switch( packet.GetProtocolID() )
	{
	case SF_INVALID_PROTOCOL:
		break;
	default:
		Destroy();
		return FORCED;
	}

	return packet.GetPacketSize();
}