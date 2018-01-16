#pragma once

#include "LoginSession.h"
#include "GameSession.h"
#include "Packet.h"
#include "string.h"

class Dummy
{
public:
	Dummy(const unsigned long id);
	virtual ~Dummy(void);

	void Initialize();
	void Destroy();
	bool LoginSessionRun();
	bool GameSessionRun();

	bool	GetAlive() { return _is_alive; }
	void	SetAlive(bool alive) { _is_alive = alive; }

	int MessageProc(Packet& packet);
	virtual void Run() = 0;

private:
	virtual void OnLoginAck( Packet& packet );
	virtual void OnServerListAck( Packet& packet );
	virtual void OnServerIPAck( Packet& packet );
	virtual void OnConnectionAccept( Packet& packet );
	virtual void OnConnectionAck( Packet& packet );
	virtual void OnSendUserDataAck( Packet& packet );
	virtual void OnWebItemWareDataAck( Packet& packet );
	virtual void OnMatchTeamInfoNotice( Packet& packet );
	virtual void OnMatchRoomInfoAck( Packet& packet );
    virtual void OnEnterChannelAck( Packet& packet );
    virtual void OnLeaveChannelAck( Packet& packet );
    virtual void OnExitServerAck( Packet& packet );
	virtual void OnSFEnterRoomAck( Packet& packet );
	virtual void OnSFUserDataInDBNotice(Packet& packet);
	virtual void OnSFCheckOverlapNickNameAck(Packet& packet);
	virtual void OnSFSaveNickNameAck(Packet& packet);
	virtual void OnSFEnterFoceSettingAck(Packet& packet);
	virtual void OnSFCreateRoomAck(Packet packet);

	virtual int LocalMessageProc(Packet& packet) = 0;

protected:
	LoginSession*		_login_session;
	GameSession*		_game_session;

protected:
	unsigned long	_id;
	bool			_is_alive;
	bool			_new_user;
	std::string		_code_name;
};
