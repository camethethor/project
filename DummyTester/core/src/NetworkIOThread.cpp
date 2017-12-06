#include "NetworkIOThread.h"
#include "NetworkHandler.h"
#include "Session.h"

NetworkIOThread::NetworkIOThread()
{	
}

NetworkIOThread::~NetworkIOThread()
{
}

void NetworkIOThread::Close()
{
	End();
	WaitForSingleObject( _thread_hdle, 5000 );
}

void NetworkIOThread::Run()
{ 
    DWORD			io_bytes = 0;
	LPOVERLAPPED	ov = NULL;
	BOOL			io_ret = 0;
	HANDLE			iocp_hdle = NetworkHandler::GetInstance()->GetIOCPHandle();
	Session*		session = NULL;
	ULONG_PTR		completion_key = NULL;

	while( _is_start )
	{
		io_ret = ::GetQueuedCompletionStatus( iocp_hdle, &io_bytes, &completion_key, &ov, INFINITE );

		if( NULL == ov )
		{
			continue;
		}
		else
		{
			if( !io_ret && ERROR_NETNAME_DELETED == GetLastError() )
			{
				(( Session* )completion_key)->OnDestroy();
				continue;
			}
			if( io_ret && io_bytes == 0 )
			{
				(( Session* )completion_key)->OnDestroy();
				continue;
			}
		}

		session = ( Session* )completion_key;

		try
		{
			session->Dispatch( io_bytes, ov );
		}
		catch ( ... ) 
		{
			(( Session* )completion_key)->OnDestroy();
			continue;
		}
	}
}