#include "LockObject.h"

LockObject::LockObject(SyncObject& sync) : _cs(sync.GetCS())
{
	::EnterCriticalSection( _cs );
}

LockObject::~LockObject()
{
	::LeaveCriticalSection( _cs );
}
