#pragma once
#include "Thread.h"

class NetworkIOThread : public Thread
{
public:
	virtual void Run();
	void Close();

	NetworkIOThread();
	~NetworkIOThread();
};

