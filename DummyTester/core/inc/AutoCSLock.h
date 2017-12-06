#pragma once
#include <windows.h>

class AutoCSLock
{
public:
	AutoCSLock(CRITICAL_SECTION* obj);
	~AutoCSLock();

private:
	CRITICAL_SECTION* _cs;
};

