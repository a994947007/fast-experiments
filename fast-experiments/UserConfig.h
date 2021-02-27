#pragma once

#include <string>
#include <list>

using namespace std;

typedef struct UserConfig {
	// 数据包文件列表
	list<string> fileList;

	// 结果集保存路径
	string resultPath;

}UserConfig;