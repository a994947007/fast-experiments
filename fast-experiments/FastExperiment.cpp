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
	//1. ��ȡ���ݰ�
	Packet pkt;
	ULONG countNum = 0;

	reader->readPacket(pkt);

	//2. ����
	list<string> results;
	while ( baseScheme->start(pkt, results) );

	//3. ������
	resultWriter -> writeLine(baseScheme->getResultHeader().c_str());
	list<string>::iterator iter;
	for (iter = results.begin(); iter != results.end(); iter++)
	{
		resultWriter ->writeLine((*iter).c_str());
	}
}

// ��Ҫ�޸ĳɾ���ķ���
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

	// �������ݰ��ļ���ȡ����ȡ
	reader = new HSNPacketReader();
	list<string> strList = userConfig.fileList;
	list<string>::iterator iter;
	for (iter = strList.begin(); iter != strList.end(); iter++)
	{
		reader->addFile(*iter);
	}
}
