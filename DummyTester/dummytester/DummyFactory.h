#pragma once

enum DUMMY_TYPE
{
	DUMMYTYPE_NONE,
	DUMMYTYPE_KR,
	DUMMYTYPE_TH,
};

class Dummy;
class DummyFactory
{
public:
	static DummyFactory* GetInstance();
	Dummy* CreateDummy( const DUMMY_TYPE type, const unsigned long id );

private:
	DummyFactory(void);
	~DummyFactory(void);

	static DummyFactory* _self_instance;
};
