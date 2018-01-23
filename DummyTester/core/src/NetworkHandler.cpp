#include "NetworkHandler.h"
#include "NetworkIOThread.h"

NetworkHandler* NetworkHandler::_self_instance = NULL;

NetworkHandler::NetworkHandler() 
:_iocp_hdle( NULL ), _work_thread_arr( NULL ), _work_thread_cnt( 0 )
{
}

NetworkHandler::~NetworkHandler()
{
	ReleaseInstance();
}

NetworkHandler* NetworkHandler::GetInstance()
{
	if( NULL == _self_instance )
		_self_instance = new NetworkHandler();

	return _self_instance;
}

void NetworkHandler::ReleaseInstance()
{
	DestroyIOCP();

	if( _self_instance )
	{
		delete _self_instance;
		_self_instance = NULL;
	}
}

bool NetworkHandler::Initialize()
{
	WSADATA wsd;
	_iocp_hdle = NULL;

	if(::WSAStartup(MAKEWORD(2, 2), &wsd) !=0 )
		return false;

	if( false == CreateIOCP() )
		return false;

	return true;
}

bool NetworkHandler::CreateIOCP()
{
	_iocp_hdle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if( false == _iocp_hdle )
		return false;
	
	if( false == CreateThreadPool() )
		return false;

	return true;
}

bool NetworkHandler::CreateThreadPool()
{
	SYSTEM_INFO systemInfo;

	GetSystemInfo(&systemInfo);
	_work_thread_cnt = systemInfo.dwNumberOfProcessors * 2 + 2;

	_work_thread_arr = new NetworkIOThread[_work_thread_cnt];

	for( int idx = 0; idx != _work_thread_cnt; ++idx )
	{
		_work_thread_arr[idx].Begin();	
	}
	
	return true;
}

bool NetworkHandler::Associate( HANDLE hDevice, ULONG_PTR pCompletionKey )
{
	HANDLE hdle;

	hdle = CreateIoCompletionPort( hDevice, _iocp_hdle, pCompletionKey, 0 );
	
	if( hdle != _iocp_hdle )
		return false;

	return true;
}

void NetworkHandler::DestroyIOCP()
{	
	if( _iocp_hdle )
	{
		for( DWORD i = 0; i != _work_thread_cnt; ++i )
		{
			PostQueuedCompletionStatus(_iocp_hdle, 0, NULL, NULL);
		}

		CloseHandle(_iocp_hdle);
		_iocp_hdle = NULL;
	}
	
	::Sleep( 1000 );

	for( int idx = 0; idx != _work_thread_cnt; ++idx )
	{
		((NetworkIOThread*)&_work_thread_arr[idx])->Close();
	}

	if( _work_thread_arr )
	{
		delete [] _work_thread_arr;
		_work_thread_arr = NULL;
	}

	::WSACleanup();
}