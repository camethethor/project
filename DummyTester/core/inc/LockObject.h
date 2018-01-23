#pragma once
#include <windows.h>
#include "SyncObject.h"

class LockObject
{
public:
	LockObject(SyncObject& sync);
	~LockObject();

private:
	CRITICAL_SECTION* _cs;
};

