#pragma once
/**
*	��־�࣬���ڱ��������־
*/

#include <iostream>
using namespace std;

class Log
{
public:
	static void add(string content);	// ������־
	static void create(const char * path);	// �����ļ�
	static void error(string content);	// ������־
};

