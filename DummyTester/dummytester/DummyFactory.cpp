#include "DummyFactory.h"
#include "KRDummy.h"
#include "THDummy.h"

DummyFactory* DummyFactory::_self_instance = NULL;

DummyFactory::DummyFactory(void)
{
}

DummyFactory::~DummyFactory(void)
{
}

DummyFactory*  DummyFactory::GetInstance()
{
	if( NULL == _self_instance )
		_self_instance = new DummyFactory;

	return _self_instance;
}

// 팩토리패턴은 아니고 그냥 관용구
Dummy* DummyFactory::CreateDummy( const DUMMY_TYPE type, const unsigned long id )
{
	Dummy* dmy = NULL;

	switch( type )
	{
	case DUMMYTYPE_KR:
		dmy = new KRDummy(id);
		break;
	case DUMMYTYPE_TH:
		dmy = new THDummy(id);
		break;
	default:
		dmy = NULL;
		break;
	}

	return dmy;
}