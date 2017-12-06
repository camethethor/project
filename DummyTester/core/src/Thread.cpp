#include "Thread.h"
#include <process.h>

Thread::Thread()
:_is_start( false ), _thread_hdle( INVALID_HANDLE_VALUE ), _thread_id( 0 )
{
}

Thread::~Thread()
{
}

void Thread::Begin()
{
	if( _is_start )
		return;

	_is_start = true;
	_thread_hdle = (HANDLE)_beginthreadex(	NULL, 0, Thread::HandleRunner, this, 0, &_thread_id);
}

void Thread::End()
{
	if( !_is_start )
		return;

	_is_start = false;
	CloseHandle( _thread_hdle );
}

unsigned int Thread::HandleRunner( LPVOID param )
{
	Thread* th = (Thread*)param;
	th->Run();

	_endthreadex( 0 );
	return 0;
}