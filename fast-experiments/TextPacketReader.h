#pragma once
#include "PacketReader.h"
class TextPacketReader :
    public PacketReader
{
public:
	TextPacketReader(ifstream* ifFile);
	TextPacketReader(const string src);
	TextPacketReader();
	virtual ~TextPacketReader();

protected:
	bool readPacket(ifstream* ifFile, Packet& pkt);
};

