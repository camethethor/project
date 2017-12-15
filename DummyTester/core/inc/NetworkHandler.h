#pragma once
#include "Thread.h"

class NetworkHandler  
{
public:
	static NetworkHandler* GetInstance();

	bool Initialize();
	void ReleaseInstance();

	bool Associate( HANDLE hDevice, ULONG_PTR pCompletionKey );
	HANDLE GetIOCPHandle() { return _iocp_hdle; }

private:
	NetworkHandler();
	~NetworkHandler();
	
	bool CreateIOCP();
	void DestroyIOCP();
	bool CreateThreadPool();

private:
	static NetworkHandler* _self_instance;

	HANDLE		_iocp_hdle;						
	DWORD		_work_thread_cnt;				
	Thread*		_work_thread_arr;			
};
