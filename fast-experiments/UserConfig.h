#pragma once

#include <string>
#include <list>

using namespace std;

typedef struct UserConfig {
	// ���ݰ��ļ��б�
	list<string> fileList;

	// ���������·��
	string resultPath;

}UserConfig;