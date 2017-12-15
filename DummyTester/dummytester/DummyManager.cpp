#include "DummyManager.h"
#include "DummyFactory.h"
#include "Config.h"
#include "AutoCSLock.h"

DummyManager* DummyManager::_self_instance = NULL;

DummyManager::DummyManager(void) :_active_count(0) //, _inactive_count(0)
{
	_dummy_container.Clear();
}

DummyManager::~DummyManager(void)
{
    Dummy*	dummy = NULL;
	AutoCSLock cslock( _dummy_container.GetCS() );

    Map<unsigned long, Dummy*>::MAP_POSITION pos = _dummy_container.HeadPosition();

    while( false == _dummy_container.IsEnd(pos) )
    {		
        dummy = pos->second;
        dummy->Destroy();

        ++pos;
        delete dummy;
    }
}

DummyManager* DummyManager::GetInstance()
{
	if( _self_instance == NULL )
		_self_instance = new DummyManager();

	return _self_instance;
}

void DummyManager::ReleaseInstance()
{  
	if( _self_instance != NULL )
    {
        delete _self_instance;
        _self_instance = NULL;
    }
}

bool DummyManager::Initialize()
{
	Dummy* dmy = NULL;

	for( int index = ID_INITVAL; index < ID_INITVAL + SESSION_COUNT; ++index )
	{
		// ID_INITVAL 부터 ID_INITVAL+SESSION_COUNT 만큼의 ID를 가진 더미 생성
		dmy = DummyFactory::GetInstance()->CreateDummy( DUMMYTYPE_KR, index );

		if( NULL != dmy )
			_dummy_container.Insert( index, dmy );
	}

	return true;
}

//bool DummyManager::RemoveSession( Session* session, int type )
//{
//	if( session == NULL )
//		return false;
//
//	Dummy* dmy = NULL;
//	AutoCSLock sync( &_dummy_container );
//	Map<unsigned short, Dummy*>::MAP_POSITION pos = _dummy_container.HeadPosition();
//
//	while( false == _dummy_container.IsEnd(pos) )
//	{
//		dmy = pos->second;
//		dmy->Destroy();
//		
//		++pos;
//		delete dmy;
//	}
//
//	//List< Object* >::LIST_POSITION pos = _session_list.Find( session );
//
//	//if( _session_list.IsEnd( pos ) != true )
//	//{
//	//	_session_list.RemoveItem( pos );
//	//	session->OnDestroy();
//	//}
//	//else
//	//	return false;
//
//	return true;
//}

//bool DummyManager::Run()
//{
//	List<Object*>::LIST_POSITION pos = _session_list.HeadPosition();
//
//	while( !_session_list.IsEnd(pos) )
//	{
//		static_cast<Session*>(*pos)->OnCreate();
//		++pos;
//	}
//
//	return true;
//}

bool DummyManager::Start()
{
	Map<unsigned long, Dummy*>::MAP_POSITION pos = _dummy_container.HeadPosition();

	while( false == _dummy_container.IsEnd( pos ))
	{
		if( false == pos->second->GetAlive())
		{
			pos->second->Run();
			//Sleep(100);
		}
		++pos;
	}
	
	return true;
}

//bool DummyManager::SessionDestroy( unsigned long session_id )
//{
//    Map<unsigned long, Dummy*>::MAP_POSITION pos = _dummy_container.Find( session_id );
//    if( !_dummy_container.IsEnd( pos ) )
//    {
//        Dummy* dummy = pos->second;
//        dummy->Destroy();
//        return true;
//    }    
//
//    return false;
//}


//bool DummyManager::ReStartSession( unsigned long session_id )
//{
//    Map<unsigned long, Dummy*>::MAP_POSITION pos = _dummy_container.Find( session_id );
//    if( !_dummy_container.IsEnd( pos ) )
//    {
//        Dummy* dummy = pos->second;
//        dummy->LoginSessionRun();
//        return true;
//    }    
//
//    return false;
//}



