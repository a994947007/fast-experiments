#pragma once
#include <stdlib.h>
#include <cstring>
#include "iostream"
using namespace std;

class ResultWriter
{
private:
	FILE * pFile;
public:
	/** �ļ�д��Ĭ�ϼ��أ���config.h�м���д��·��
	*/
	ResultWriter();
	/** �ļ�д����ָ���ļ�д��·��
	*/
	ResultWriter(const char * path);

	~ResultWriter();

	ResultWriter& writeLine(const char* str);
	ResultWriter& write(const char* str);

	void close();
};

