#include "pch.h"
#include "FastExperiment.h"
#include "HSNPacketReader.h"

FastExperiment::FastExperiment(const UserConfig& userConfig)
{
	srand(unsigned(time(NULL)));
	init(userConfig);
}

FastExperiment::~FastExperiment()
{
	if (reader != NULL) {
		delete reader;
		reader = NULL;
	}

	if (baseScheme != NULL) {
		delete baseScheme;
		baseScheme = NULL;
	}

	if (resultWriter != NULL) {
		delete resultWriter;
		resultWriter = NULL;
	}
}

void FastExperiment::run()
{
	//1. 读取数据包
	Packet pkt;
	ULONG countNum = 0;

	reader->readPacket(pkt);

	//2. 方案
	list<string> results;
	while ( baseScheme->start(pkt, results) );

	//3. 输出结果
	resultWriter -> writeLine(baseScheme->getResultHeader().c_str());
	list<string>::iterator iter;
	for (iter = results.begin(); iter != results.end(); iter++)
	{
		resultWriter ->writeLine((*iter).c_str());
	}
}

// 需要修改成具体的方案
BaseScheme * FastExperiment::createScheme(const UserConfig & userConfig)
{
	return new DefaultScheme(userConfig);
}

PacketReader* FastExperiment::createPacketReader()
{
	return new HSNPacketReader();
}

ResultWriter* FastExperiment::createResultWriter(const char * resultPath)
{
	return new ResultWriter(resultPath);
}

void FastExperiment::init(const UserConfig&userConfig)
{
	ASSERT(!userConfig.fileList.empty());

	baseScheme = createScheme(userConfig);
	resultWriter = createResultWriter(userConfig.resultPath.c_str());

	// 交给数据包文件读取器读取
	reader = new HSNPacketReader();
	list<string> strList = userConfig.fileList;
	list<string>::iterator iter;
	for (iter = strList.begin(); iter != strList.end(); iter++)
	{
		reader->addFile(*iter);
	}
}
