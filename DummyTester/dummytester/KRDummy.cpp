#include "KRDummy.h"
#include "Protocol.h"
#include "Errcode.h"
#include "config.h"

KRDummy::KRDummy(const unsigned long id) : Dummy(id)
{
}

KRDummy::~KRDummy(void)
{
}

void KRDummy::Run()
{
	if( false == LoginSessionRun() )
	{
		Destroy();
		return;
	}
	
	Packet sendmsg( SF_LOGIN_REQ );
	sendmsg << KR_CLIENT_VERSION << static_cast<long>(_id) << "account" << static_cast<long>(GetTickCount()) << "1QA3ASLDKJAWJKASSD";
	_login_session->SendPacket(sendmsg);
}

int KRDummy::LocalMessageProc(Packet& packet)
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