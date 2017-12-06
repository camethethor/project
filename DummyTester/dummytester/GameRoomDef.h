#pragma once

#define MAX_GAMEROOM_USERCOUNT				16

#define LENGTH_STARTDATE					20
#define LENGTH_PDATE						4



#ifdef SF_CONTEST_SERVER
#define NUM_PERSONGAME_VICTORYCONDITION		30			// �������� �⺻ ų ��
#define NUM_TEAMGAME_VICTORYCONDITION		7			// ������ �⺻ �¼�(��ȸ)
#define NUM_EXERCISEGAME_VICTORYCONDITION	0			// ������� �¼�
#define NUM_CLANGAME_VICTORYCONDITION		5			// Ŭ������ �¼�
#define NUM_CONTESTGAME_VICTORYCONDITION	5			// ��ȸ ��� �¼�
#define NUM_CLAN_LADDERGAME_VICTORYCONDITION             5           //Ŭ������ �¼�
#define NUM_PERSONAL_LADDERGAME_VICTORYCONDITION         10          //���η��� �¼�
#define NUM_CTC_VICTORYCONDITION            5           
#define NUM_TEAM_DEATH_VICTORYCONDITION     6           // ������ �¼�
#define NUM_OCCUPY_VICTORYCONDITION			5			// ������ �¼�
#define NUM_SNIPER_VICTORYCONDITION			8
#define NUM_CTCRENEWAL_VICTORYCONDITION     7           // ������ �¼�
#define	NUM_ZOMBIEMODE_VICTORYCONDITION		5
#define NUM_ADGAME_VICTORYCONDITION			2
#define NUM_PIRATE_VICTORYCONDITION			5			
#define	NUM_ZOMBIEMODE2_VICTORYCONDITION	4
#define	NUM_LEAGUEMODE_VICTORYCONDITION		5
#else
#define NUM_PERSONGAME_VICTORYCONDITION					30			// �������� �⺻ ų ��
#define NUM_TEAMGAME_VICTORYCONDITION					8			// ������ �⺻ �¼�
#define NUM_EXERCISEGAME_VICTORYCONDITION				0			// ������� �¼�
#define NUM_CLANGAME_VICTORYCONDITION					5			// Ŭ������ �¼�
#define NUM_CONTESTGAME_VICTORYCONDITION				5			// ��ȸ ��� �¼�
#define NUM_CLAN_LADDERGAME_VICTORYCONDITION            5           // Ŭ������ �¼�
#define NUM_PERSONAL_LADDERGAME_VICTORYCONDITION        10          // ���η��� �¼�
#define NUM_CTC_VICTORYCONDITION						5           
#define NUM_TEAM_DEATH_VICTORYCONDITION					1           // ������ �¼�
#define NUM_OCCUPY_VICTORYCONDITION						5			// ������ �¼�
#define NUM_SNIPER_VICTORYCONDITION						8
#define NUM_CTCRENEWAL_VICTORYCONDITION					2           // ������ �¼�
#define	NUM_ZOMBIEMODE_VICTORYCONDITION					5
#define NUM_ADGAME_VICTORYCONDITION						2
#define NUM_PIRATE_VICTORYCONDITION						0			
#define	NUM_ZOMBIEMODE2_VICTORYCONDITION				4
#define	NUM_LEAGUEMODE_VICTORYCONDITION					5
#endif

#define ERR_BEUNDERSTAFFED					0			// ������ �ο��� ����
#define ERR_NOTALLREADY						1			// ��� Ready ���°� �ƴ�
#define ERR_DONTEXIST_REALIP				2			// Real IP�� ����
#define ERR_NOT_TEAMGAMECONDITION			3			// ������ �ο��� ���� ����
#define ERR_NOT_CLANGAMECONDITION			4			// Ŭ���� 2�� �ʰ��ų� ���ʿ� ���� �ٸ� Ŭ���� ���� ����

#define TEAM_RED							0			// Red ���� ��ȣ
#define TEAM_BLUE							1			// Blue ���� ��ȣ
#define TEAM_ALL							2			// ���о���

#define NUM_MISSION_MIN						0		
#define NUM_MISSION_MAX						99

enum JudgeGameCloseState
{
	CHECK_GAMEROUND_STATE = 0,
	CHECK_KILLCOUNT_STATE = 1,
	CHECK_USERCOUNT_STATE = 2,
};

enum GAME_VICTORYCONDITION_TYPE
{
	GAME_VICTORYTYPE_ROUND,
	GAME_VICTORYTYPE_TIME,
	GAME_VICTORYTYPE_POINT,
};

enum GameRoom_Status
{
	WAITROOM_STATUS = 0,			
	LOADINGROOM_STATUS = 1,				
	GAMINGROOM_STATUS = 2, 
	MATCHINGROOM_STATUS = 3,
};




