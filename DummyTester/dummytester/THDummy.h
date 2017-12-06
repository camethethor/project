#pragma once
#include "dummy.h"

class THDummy :	public Dummy
{
public:
	THDummy(const unsigned long id);
	~THDummy(void);
	
	virtual void	Run();

private:
	virtual int		LocalMessageProc(Packet& packet);
};
