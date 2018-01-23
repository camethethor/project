#pragma once
#include "Packet.h"

class IPacketParser
{
public:
	IPacketParser() {}
	virtual ~IPacketParser() {}

	virtual int PacketParsing( Packet& packet ) = 0;
};