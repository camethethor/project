#pragma once

#define DUMMYMACHINE_IP			"192.168.103.20"		// 더미 구동 장비의 IP
#define LOGINSERVER_IP			"172.16.18.50"			// 로그인서버
#define GAMESERVER_IP			"172.16.18.51"			// 게임서버

const int ID_INITVAL			= 5000;				// 더미 ID는 ID_INITVAL 부터 ID_INITVAL + SESSION_COUNT 까지 사용
const int SESSION_COUNT			= 3000;
const int RECONNECT_INTERVAL	= 10000;

const WORD LOGINSERVER_PORT		= 1080;
const WORD GAMESERVER_PORT		= 1081;
const WORD UDP_PORT				= 1082;

const WORD TH_CLIENT_VERSION = 1802;	            // 태국 클라버전
const WORD KR_CLIENT_VERSION = 2123;				// 한국 클라버전

const WORD LOGINSERVER_ID = 0;
const WORD GAMESERVER_ID  = 3;

const byte SYSTEM_SPEC = 100;
const WORD PING_VALUE  = 110;

const WORD MAX_USER_COUNT		= 300;
const WORD MAX_GAMEROOM_COUNT	= 150;

const BYTE	MAX_CHANNEL_COUNT = 13;
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