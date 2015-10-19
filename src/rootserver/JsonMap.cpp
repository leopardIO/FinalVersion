#include "JsonMap.h"
#include <string.h>
#include <iostream>
using std::string;
using std::map;
using namespace std;

JsonMap::JsonMap(map<string, string> &jsonMap)
{
	m_jsonMap = jsonMap;	

    Json::Value value;
    Json::FastWriter writer;

    for (map<string, string>::iterator it = jsonMap.begin();
            it != jsonMap.end(); ++it)
    {
        value[it->first] = it->second;
    }
    m_jsonString = writer.write(value);
}

JsonMap::JsonMap(string &s)
{
    init(s);
}

JsonMap::JsonMap(const char *s, int len)
{
    if (len == 0)
    {
        len = strlen(s);
    }
    string temp(s, s + len);
    init(temp);
}

void JsonMap::init(string &s)
{
    Json::Reader reader;
    Json::Value value;
    Json::Value::Members member;

    if (reader.parse(s, value))
    {
        member = value.getMemberNames();
        for (Json::Value::Members::iterator it = member.begin();
                it != member.end(); ++it)
        {
            m_jsonMap[*it] = value[*it].asString();
        }
    }
}
