#include "Dummy.h"
#include "Protocol.h"
#include "Errcode.h"
#include "Config.h"

Dummy::Dummy(const unsigned long id)
:_id(id), _is_alive(false), _new_user(false), _login_session(this), _game_session(this)
{
}

Dummy::~Dummy(void)
{
}

void Dummy::Destroy()
{
	_is_alive = false;
	_login_session.OnDestroy();
	_game_session.OnDestroy();
}

void Dummy::Initialize()
{
	_new_user = false;
	_code_name.clear();
	
	char code_name[MAX_NICKNAME_LENGTH]=""; 
	sprintf_s( code_name, "%d", _id);
	_code_name = code_name;
}

bool Dummy::LoginSessionRun()
{
	if( _login_session.IsActive())
		_login_session.OnDestroy();
	
	if(false == _login_session.OnCreate())
	{
		_is_alive = false;
		return false;
	}

	_is_alive = true;
	return true;
}


bool Dummy::GameSessionRun()
{
	if( _game_session.IsActive())
		_game_session.OnDestroy();
	
	if(false == _game_session.OnCreate())
	{
		_is_alive = false;
		return false;
	}

	Initialize();
	return true;
}


int Dummy::MessageProc( Packet& packet )
{
	try
	{
		switch( packet.GetProtocolID() )
		{
		case SF_LOGIN_ACK:
			OnLoginAck( packet );
			break;
		case SF_SERVERLIST_ACK:
			OnServerListAck( packet );
			break;
		case SF_SERVERIP_ACK:
			OnServerIPAck( packet );
			break;
		case SF_CONNECTION_ACK:
			OnConnectionAck(packet);
			break;
		case SF_SENDUSERDATA_ACK:
			OnSendUserDataAck(packet);
			break;
		case SF_MATCH_TEAM_INFO_NOTICE:
			break;
		case SF_ENTERROOM_ACK:
			OnSFEnterRoomAck(packet);
			break;
		case SF_USERDATAINDB_NOTICE:
			OnSFUserDataInDBNotice(packet);
			break;
		case SF_CLANINFO_NOTICE:
			break;
		case SF_CHECKOVERLAPNICKNAME_ACK:
			OnSFCheckOverlapNickNameAck(packet);
			break;
		case SF_SAVENICKNAME_ACK:
			OnSFSaveNickNameAck(packet);
			break;
		case SF_ENTERFORCESETTING_ACK:
			OnSFEnterFoceSettingAck(packet);
			break;
		case SF_DONTSELLITEMLIST_NOTICE:
			break;
		case SF_CHECKPCBANGIP_NOTICE:
			break;
		case SF_CHARACTERDATAINDB_NOTICE:
			break;
		case SF_CLIENTITEM_NOTICE:
			break;
		case SF_ITEMDATAINDB_NOTICE:
			break;
		case SF_WAREDATAINDB_NOTICE:
			OnWebItemWareDataAck(packet);
			break;
		case SF_CHANNELLIST_ACK:
			break;
		case SF_LOCATION_ACK:
			break;
		case SF_MESSENGER_LOGIN_ACK:
			break;
        case SF_ENTERCHANNEL_NOTICE:
            break;
		case SF_LEAVECHANNEL_NOTICE:
			break;
        case SF_ENTERCHANNEL_ACK:
            OnEnterChannelAck(packet);                        
            break;
        case SF_LEAVECHANNEL_ACK:
            OnLeaveChannelAck(packet);
            break;
        case SF_EXITGAMESERVER_ACK:
            OnExitServerAck(packet);
            break;
        case SF_USERLISTINCHANNEL_ACK:
            break;
        case SF_ROOMLIST_ACK:
            break;
		case SF_MATCHROOMINFO_ACK:
			OnMatchRoomInfoAck(packet);
			break;
		case SF_XIGNCODE_NOTICE:
			break;
		case SF_REGISTERTEAMMATCH_ACK:
			break;
		case SF_CREATEROOM_ACK:
			OnSFCreateRoomAck(packet);
			break;
		case SF_REWARDITEM_NOTICE:
			break;
		case SF_ACCKEY_NOTCIE:
			break;
		case SF_CREATEROOM_NOTICE:
			break;
		case SF_CHANGEROOMCOUNT_NOTICE:
			break;
		case SF_CHANGEUSERLOCATION_NOTICE:
			break;
		case SF_MESSENGER_FRIENDLOGOUT_NOTICE:
			break;
		case SF_MESSENGER_FRIENDLIST_NOTICE:
			break;
		case SF_MESSENGER_CHANGEFRIENDSTATUS_NOTICE:
			break;
		case SF_MESSENGER_LEAGUEMEMBER_NOTICE:
			break;
		case SF_QUESTINFO_NOTICE:
			break;
		case SF_CLANMEDAL_NOTICE:
			break;
		case SF_SPRAYSLOTDATAINDB_NOTICE:
			break;
		case SF_VCHARSLOT_SLOTDATAINDB_NOTICE:
			break;
		case SF_ICONLIST_NOTICE:
			break;
		case SF_EVENTINFO_NOTICE:
			break;
		case SF_WEBITEM_NOTICE:
			break;
		case SF_GRADE_LEV_NOTICE:
			break;
		case SF_ASSISTRATE_NOTICE:
			break;
		case SF_CLANLADDER_NOTICE:
			break;
		case SF_CLANMASTER_NOTICE:
			break;
		case SF_CLANMEMBERLIST_NOTICE:
			break;
		case SF_ENTER_CLAN_CHANNEL_ACK:
			break;
		default:
			return LocalMessageProc( packet );
		}
	}
	catch (...)
	{
		Destroy();
		return EXCEPTION; 
	}

	return packet.GetPacketSize();
}

void Dummy::OnLoginAck( Packet& packet )
{
	byte err_code;
	packet >> err_code;

	if( err_code != LOGIN_SUCCESS )
		Destroy();

	Packet sendmsg(SF_CONNECTCLOSE_REQ);
	_login_session.SendPacket( sendmsg );

	Packet reqmsg(SF_SERVERLIST_REQ);
	reqmsg << LOGINSERVER_ID << true;
	_login_session.SendPacket(reqmsg);
}

void Dummy::OnServerListAck( Packet& packet )
{
	Packet sendmsg(SF_SERVERIP_REQ);
	sendmsg << LOGINSERVER_ID << GAMESERVER_ID;
	_login_session.SendPacket(sendmsg);
}

void Dummy::OnServerIPAck( Packet& packet )
{
	GameSessionRun();

	Packet sendmsg( SF_CONNECTION_REQ );
	sendmsg << static_cast<long>(_id) << LOGINSERVER_ID << false << false << "T.K";
	_game_session.SendPacket(sendmsg);
}


void Dummy::OnSFCheckOverlapNickNameAck( Packet& packet )
{
	char result;
	packet >> result;

	if( result == 1 )
	{
		Packet sendmsg(SF_SAVENICKNAME_REQ);
		sendmsg << _code_name;
		_game_session.SendPacket(sendmsg);
	}		
	else
		Destroy();
}

void Dummy::OnSFSaveNickNameAck(Packet& packet)
{
	bool result;
	packet >> result;

	if( result == true)
	{
		Packet sendmsg(SF_ENTERFORCESETTING_REQ);
		sendmsg << static_cast<byte>(1);
		_game_session.SendPacket(sendmsg);
	}
	else
		Destroy();
}

void Dummy::OnSFCreateRoomAck(Packet packet)
{
	byte err_code = 0;
	packet >> err_code;

	if( err_code != 0)
	{
		Packet sendmsg(SF_ENTERROOM_REQ);
		sendmsg << "" << "";
		_game_session.SendPacket(sendmsg);
	}
}

void Dummy::OnSFEnterFoceSettingAck(Packet& packet)
{
	// CheckBalanceReq()

	Packet sendmsg(SF_BUYCHARACTER_REQ);
	sendmsg << static_cast<long>(DEFAULT_CHARACTER_ITEMID);
	_game_session.SendPacket(sendmsg);

	Sleep(1000);
	sendmsg.Clear();
	sendmsg.SetProtocolID( SF_LEAVEFORCESETTING_REQ );
	_game_session.SendPacket(sendmsg);

	sendmsg.Clear();
	sendmsg.SetProtocolID(SF_ENTERCHANNEL_REQ);
	sendmsg << static_cast<byte>((_id % MAX_CHANNEL_COUNT)+1);
	_game_session.SendPacket(sendmsg);
}

void Dummy::OnConnectionAccept( Packet& packet )
{
	Packet sendmsg( SF_CONNECTION_REQ );
	sendmsg << static_cast<long>(_id) << LOGINSERVER_ID >> false >> false >> "tt";
	_game_session.SendPacket(sendmsg);
}

void Dummy::OnSFEnterRoomAck(Packet& packet)
{
	BYTE error_code;
	packet >> error_code;

	if( error_code != SUCCESS_ENTER_ROOM )
	{
		//Destroy();
	}
}

void Dummy::OnSFUserDataInDBNotice( Packet& packet )
{
	SF_USER user;
	packet.ReadData(&user, sizeof(SF_USER));
	
	_code_name = user.cpNick;
}

void Dummy::OnMatchTeamInfoNotice(Packet& packet)
{
	int team_id = 0; 
	std::string team_name;
	int win = 0;
	int lose = 0;
	int con_win = 0;
	int con_lose = 0;
	int rating = 0;
	int grade = 0;

	packet >> team_id >> team_name >> win >> lose >> con_win >> con_lose >> rating >> grade;

	Packet sendmsg(SF_MATCHROOMINFO_REQ);
	_game_session.SendPacket(sendmsg);
}

void Dummy::OnMatchRoomInfoAck(Packet& packet )
{
	int room_id = 0;
	bool is_match_room = false;
	byte room_state = 0;

	packet >> room_id >> is_match_room >> room_state;

	Packet sendmsg(SF_OTHERCHANNELENTERROOM_REQ);
	sendmsg << 1 << room_id << "";
	_game_session.SendPacket(sendmsg);
}


void Dummy::OnConnectionAck( Packet& packet )
{
	BYTE err_code;
	packet >> err_code;

	if( err_code != LOGIN_SUCCESS )
	{
		Destroy();
		return;
	}

	int time_stamp = GetTickCount();
	DWORD ip = inet_addr(DUMMYMACHINE_IP);

	Packet sendmsg( SF_SENDUSERDATA_REQ );
	sendmsg << "account" << "0011" << ip << UDP_PORT;
	_game_session.SendPacket(sendmsg);

}

void Dummy::OnSendUserDataAck( Packet& packet )
{
	bool result;
	packet >> result;

	if( result == false )
		Destroy();
	else
	{
		Packet sendmsg( SF_SAVESYSTEMSPEC_REQ);
		sendmsg << SYSTEM_SPEC;
		_game_session.SendPacket(sendmsg);

		sendmsg.Clear();
		sendmsg.SetProtocolID(SF_GETDBDATA_REQ);
		_game_session.SendPacket(sendmsg);
	}
}

void Dummy::OnWebItemWareDataAck( Packet& packet )
{
	Packet sendmsg(SF_UDPDATASTORE_REQ);
	sendmsg << PING_VALUE;
	_game_session.SendPacket(sendmsg);

	//sendmsg.Clear();
	//sendmsg.SetProtocolID(SF_MATCHROOMINFO_REQ);
	//_game_session.SendPacket(sendmsg);

	sendmsg.Clear();
	sendmsg.SetProtocolID(SF_CHANNELLIST_REQ);
	_game_session.SendPacket(sendmsg);

	sendmsg.Clear();
	sendmsg.SetProtocolID(SF_LOCATION_REQ);
	_game_session.SendPacket(sendmsg);

	//sendmsg.Clear();
	//sendmsg.SetProtocolID(SF_MESSENGER_LOGIN_REQ);
	//_game_session.SendPacket(sendmsg);

	sendmsg.Clear();
	sendmsg.SetProtocolID(SF_ENDCLIENTLOADING_REQ);
	sendmsg << false;
	_game_session.SendPacket(sendmsg);

	if( _new_user )
	{
		sendmsg.Clear();
		sendmsg.SetProtocolID(SF_CHECKOVERLAPNICKNAME_REQ);
		sendmsg << _code_name;
		_game_session.SendPacket(sendmsg);
	}
	else
	{
		sendmsg.Clear();
		sendmsg.SetProtocolID(SF_ENTERCHANNEL_REQ);
		sendmsg << static_cast<byte>((_id % MAX_CHANNEL_COUNT)+1);
		_game_session.SendPacket(sendmsg);
	}
}

void Dummy::OnEnterChannelAck( Packet& packet )
{
    bool bSuccess;

    packet >> bSuccess;

    if( bSuccess )
    {
		Packet sendmsg(SF_CREATEROOM_REQ);
		sendmsg << static_cast<byte>(TEAM_GAME)			//byteGameType 
			<< "Åä¸£´Ô ¸ÚÀÖ¾î¿ä"			//strRoomName 
			<< static_cast<byte>(16)		//byteMaxUser 
			<< static_cast<byte>(0)			//byteThirdView 
			<< static_cast<byte>(0)			//byteEnemyView 
			<< static_cast<bool>(false)		//bPrivate 
			<< ""							//strPassword 
			<< static_cast<byte>(0)			//byteRoomNameColorID
			<< false						//bObserver 
			<< ""							//strObserverPassword 
			<< static_cast<WORD>(20)		//wMapType 
			<< false						//bArmsChange
			<< true							//bIntrude 
			<< false						//bTracerBullet 
			<< true;						//bTeamSwap;

        _game_session.SendPacket(sendmsg);
    }    
	else 
		Destroy();
}

void Dummy::OnLeaveChannelAck( Packet& packet )
{
    Packet sendmsg( SF_EXITGAMESERVER_REQ );
    _game_session.SendPacket(sendmsg);
}

void Dummy::OnExitServerAck( Packet& packet )
{
	Destroy();
}