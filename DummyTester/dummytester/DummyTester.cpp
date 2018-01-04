#include <tchar.h>

#include "NetworkHandler.h"
#include "DummyManager.h"
#include "Config.h"

int _tmain( int argc, _TCHAR* argv[] )
{
	if( NetworkHandler::GetInstance()->Initialize() == false )
	{
		return false;
	}

	if( DummyManager::GetInstance()->Initialize() == false )
	{
		return false;
	}

	for(int i = 0; i <= DUMMY_TRY_COUNT; i++ )
	{
		DummyManager::GetInstance()->Start();
		WaitForSingleObject( INVALID_HANDLE_VALUE, RECONNECT_INTERVAL );
	}

	NetworkHandler::GetInstance()->ReleaseInstance();
	DummyManager::GetInstance()->ReleaseInstance();
	
	return 0;
}

