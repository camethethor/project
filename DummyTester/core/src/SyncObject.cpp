#include "SyncObject.h"

SyncObject::SyncObject()
{
	InitializeCriticalSection(&_cs);
}

SyncObject::~SyncObject()
{
	::DeleteCriticalSection(&_cs);
}
