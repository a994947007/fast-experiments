#pragma once

#include "common.h"
#include <list>
#include <string>

using namespace std;

class BaseScheme
{
public:
	BaseScheme(const UserConfig & userConfig) {}

	virtual bool start(Packet&, list<string>&) = 0;

	virtual string getResultHeader() = 0;
};

// 提供一个默认的BaseScheme
class DefaultScheme : public BaseScheme {
private:
	UserConfig* userConfig;

public:
	DefaultScheme(const UserConfig & userConfig):BaseScheme(userConfig){
		this->userConfig = &(UserConfig &)userConfig;
	}

	virtual bool start(Packet& pkt, list<string>& results) {
		return false;
	}

	virtual string getResultHeader() {
		return "default scheme arguments";
	}
};