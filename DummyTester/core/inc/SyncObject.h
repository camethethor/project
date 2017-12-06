#pragma once
#include <windows.h>

class SyncObject  
{
public:
	SyncObject();
	virtual ~SyncObject() = 0;

	CRITICAL_SECTION* GetCS()	 {return &_cs; }

private:
	CRITICAL_SECTION	_cs;
};