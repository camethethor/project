#include <tchar.h>

#include "NetworkHandler.h"
#include "DummyManager.h"
#include "Config.h"

int _tmain( int argc, _TCHAR* argv[] )
{
	if( NetworkHandler::GetInstance()->Start() == false )
	{
		return false;
	}

	if( DummyManager::GetInstance()->Initialize() == false )
	{
		return false;
	}

	while(true)
	{
		DummyManager::GetInstance()->Start();
		WaitForSingleObject( INVALID_HANDLE_VALUE, RECONNECT_INTERVAL );
	}

	NetworkHandler::GetInstance()->Stop();
	DummyManager::GetInstance()->ReleaseInstance();
	
	return 0;
}

