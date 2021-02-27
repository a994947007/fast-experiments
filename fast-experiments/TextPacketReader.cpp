#include "pch.h"
#include "TextPacketReader.h"
#include <vector>
#include <string.h>
#include <sstream>
#include < iostream >
#include < fstream >
#include < string >

#define LEN 16 

#pragma warning(disable:4996)

typedef unsigned int uint;

TextPacketReader::TextPacketReader(ifstream* ifFile) :PacketReader(ifFile)
{
}
TextPacketReader::TextPacketReader(const string src) : PacketReader(src)
{
}

TextPacketReader::TextPacketReader() :PacketReader()
{
}

TextPacketReader::~TextPacketReader()
{
}

/**
 * 字符串转整形
 */
/*
UINT IpTint(const char* ipstr)
{
    if (ipstr == NULL) return 0;

    char* token;
    UINT i = 3, total = 0, cur;

    token = strtok((char *)ipstr, "|");

    while (token != NULL) {
        cur = atoi(token);
        if (cur >= 0 && cur <= 255) {
            total += cur * pow(256, i);
        }
        i--;
        token = strtok(NULL, "|");
    }

    return total;
}
*/

/*
void split(const std::string& str,
    std::vector<std::string>& tokens,
    const char delim = ' ') {
    tokens.clear();

    std::istringstream iss(str);
    std::string tmp;
    while (std::getline(iss, tmp, delim)) {
        if (tmp != "") {
            // 如果两个分隔符相邻，则 tmp == ""，忽略。
            tokens.emplace_back(std::move(tmp));
        }
    }
}
*/

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

USHORT StringToUShort(const char * sNumber) {
    USHORT s = 0;
    char* c = (char*)sNumber;
    while (*c) {
        s *= 10;
        s += (*c) - '0';
        c++;
    }
    return s;
}

UCHAR StringToUCHAR(const char * sNumber) {
    UCHAR s = 0;
    char* c = (char*)sNumber;
    while (*c) {
        s *= 10;
        s += (*c) - '0';
        c++;
    }
    return s;
}

bool TextPacketReader::readPacket(ifstream* ifFile, Packet& pkt)
{
    string line;
    (*ifFile) >> line;
    
    /*
    char * token = strtok((char *)line.c_str(),"-");
    const char * srcIp = token;
    token = strtok(NULL, "-");
    const char* srcPort = token;
    token = strtok(NULL, "-");
    const char* dstIp = token;
    token = strtok(NULL, "-");
    const char* dstPort = token;
    token = strtok(NULL, "-");
    const char* type = token;


    pkt.src.ip = IpTint(srcIp);
    pkt.src.port = StringToUShort(srcPort);
    pkt.dst.ip = IpTint(dstIp);
    pkt.src.port = StringToUShort(dstPort);
    pkt.src.ip = StringToUCHAR(type);
     */

	return false;
}
