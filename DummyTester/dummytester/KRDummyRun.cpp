#include "KRDummyRun.h"
#include "KRDummy.h"
#include "Protocol.h"
#include "Errcode.h"
#include "config.h"
#include "loginsession.h"

KRDummyRun::KRDummyRun() 
{

}

KRDummyRun::~KRDummyRun(void)
{
}

Dummy*	KRDummyRun::CreateDummy( const unsigned int id )
{
	Dummy* dmy = new KRDummy(id);
	return dmy;
}

void KRDummyRun::Run()
{
	if( false == LoginSessionRun() )
	{
		Destroy();
		return;
	}
	
	Packet sendmsg( SF_LOGIN_REQ );
	sendmsg << KR_CLIENT_VERSION << static_cast<long>(_dummy->GetID()) << "account" << static_cast<long>(GetTickCount()) << "1QA3ASLDKJAWJKASSD";
	_login_session->SendPacket(sendmsg);
}

int KRDummyRun::LocalPacketParsing(Packet& packet)
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