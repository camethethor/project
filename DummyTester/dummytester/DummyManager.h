#pragma once

#include "Dummy.h"
#include "Map.h"

class DummyManager
{
public:
	static DummyManager* GetInstance();
	static void ReleaseInstance();

	bool	Initialize(void);
	bool	Start(void);

	long	IncreaseActiveCount() { return InterlockedIncrement(&_active_count); }
	long	DecreaseActiveCount() { return InterlockedDecrement(&_active_count); }

private:
	DummyManager(void);
	~DummyManager(void);

	long	_active_count;

	Map<unsigned long,Dummy*>		_dummy_container;
	static	DummyManager*			_self_instance;
};
