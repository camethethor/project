#pragma once
#include <winsock2.h>

class Thread 
{
public:
	Thread();
	virtual ~Thread();

	void Begin();
	void End();	
	virtual void Run() = 0;

protected:
	HANDLE			_thread_hdle;				
	bool			_is_start;		
	unsigned int	_thread_id;

private:
	static unsigned int WINAPI HandleRunner( LPVOID param );
};
