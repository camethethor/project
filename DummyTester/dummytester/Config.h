#pragma once

#define DUMMYMACHINE_IP			"192.168.103.20"		// ���� ���� ����� IP
#define LOGINSERVER_IP			"172.16.18.50"			// �α��μ���
#define GAMESERVER_IP			"172.16.18.51"			// ���Ӽ���

const int SESSION_COUNT			= 3000;
const int DUMMY_TRY_COUNT		= 100;
const int RECONNECT_INTERVAL	= 10000;

const unsigned short LOGINSERVER_PORT		= 1080;
const unsigned short GAMESERVER_PORT		= 1081;
const unsigned short UDP_PORT				= 1082;

const unsigned short TH_CLIENT_VERSION = 1802;	            // �±� Ŭ�����
const unsigned short KR_CLIENT_VERSION = 2123;				// �ѱ� Ŭ�����

const unsigned short LOGINSERVER_ID = 0;
const unsigned short GAMESERVER_ID  = 3;

const unsigned char SYSTEM_SPEC = 100;
const unsigned short PING_VALUE  = 110;

const unsigned short MAX_USER_COUNT		= 300;
const unsigned short MAX_GAMEROOM_COUNT	= 150;

const int MAX_NICKNAME_LENGTH = 16;
const int MAX_NICKFLAG_LENGTH = 4;

const unsigned char	MAX_CHANNEL_COUNT = 13;
const int	DEFAULT_CHARACTER_ITEMID = 2649;

enum GAMEMODE
{
	PERSONAL_GAME,			
	TEAM_GAME,				
	CLAN_GAME,				
	PERSONAL_GAME_NOTSNIPER,
	TEAM_GAME_NOTSNIPER,	
	CLAN_GAME_NOTSNIPER,	
	CONTEST_GAME,			
	EXERCISE_GAME,          
};

enum DUMMY_BEHAVIOR_TYPE
{
	DMY_CREATE_ROOM,
	DMY_JOIN_ROOM,
	DMY_CHAT_SEND,
	DMY_BEHAVIOR_COUNT,
};

struct SF_USER
{	
	char cpNick[MAX_NICKNAME_LENGTH];			
	int nRank;									
	int nMoney;									
	int nSalary;								
	int nQuestLevel;

	SF_USER()
	{
		memset( cpNick, 0, sizeof(SF_USER) );
	}
};

