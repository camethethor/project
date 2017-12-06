#pragma once

enum DISCONNECT_TYPE 
{ 
	GRACEFUL				= -1, 
	FORCED					= -2, 
	EXCEPTION				= -3, 
	SENDINGPACKETSIZE_FULL	= -4, 
	INVALID_HEADER			= -5,
};

enum CREATEGAMEROOM_ERRORCODE
{
	ERR_NONE,
	ERR_NOTENOUGH_ROOM,
	ERR_DONOTJOIN_CLAN,
	ERR_DONTSETTING_BASICCHACTER,
	ERR_WRONG_USERCOUNT,
};

enum ENTERROOM_ERRORCODE
{
	SUCCESS_ENTER_ROOM,			
	ERR_DEFAULT_CHARACTER,					// �⺻ ĳ���� ����
	ERR_NOT_EXIST_ROOM,						// �������� �ʴ� ��
	ERR_INVALID_PASSWORD,					// �н����尡 Ʋ��
	ERR_ISGAMING,							// ������ ������
	ERR_BEOVERSTAFFED,						// �ο��� �� á��
	ERR_DONTJOIN_CLAN,						// Ŭ���� �������� ����
	ERR_PROGRESS_CLANMATCHING,				// Ŭ����Ī ���� �濡 ������ Ŭ���� �������� ����
};
