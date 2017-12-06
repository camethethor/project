#include "AutoCSLock.h"

AutoCSLock::AutoCSLock(CRITICAL_SECTION* cs) : _cs(cs)
{
	::EnterCriticalSection( _cs );
}

AutoCSLock::~AutoCSLock()
{
	::LeaveCriticalSection( _cs );
}
