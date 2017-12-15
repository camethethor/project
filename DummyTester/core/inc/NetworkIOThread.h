#pragma once
#include "Thread.h"

class NetworkIOThread : public Thread
{
public:
	NetworkIOThread();
	~NetworkIOThread();

	virtual void Run();
	void Close();
};

