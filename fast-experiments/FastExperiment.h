#pragma once

#include "UserConfig.h"
#include "PacketReader.h"
#include "BaseScheme.h"
#include "ResultWriter.h"

class FastExperiment
{
private:
	PacketReader* reader;
	BaseScheme * baseScheme;
	ResultWriter * resultWriter;

public:
	FastExperiment(const UserConfig &);
	virtual ~FastExperiment();

	void run();

protected:
	BaseScheme * createScheme(const UserConfig & userConfig);
	PacketReader * createPacketReader();
	ResultWriter* createResultWriter(const char * resultPath);
	

private: 
	void init(const UserConfig&);
};

