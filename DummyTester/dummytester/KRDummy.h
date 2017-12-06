#pragma once
#include "dummy.h"

class KRDummy :	public Dummy
{
public:
	KRDummy(const unsigned long id);
	~KRDummy(void);

	virtual void	Run();

private:
	virtual int		LocalMessageProc(Packet& packet);
};
