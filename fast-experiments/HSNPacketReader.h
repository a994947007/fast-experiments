#pragma once

#include <string>
#include <fstream>
#include <list>
#include "PacketReader.h"

using namespace std;

class HSNPacketReader : public PacketReader
{
public:
	HSNPacketReader(ifstream * ifFile);
	HSNPacketReader(const string src);
	HSNPacketReader();

	~HSNPacketReader();

protected:
	bool readPacket(ifstream * ifFile, Packet& pkt);
};

