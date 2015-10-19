#ifndef _JSON_MAP_H_
#define _JSON_MAP_H_
#include "../../common/json/json.h"
#include <map>
#include <string>

class JsonMap
{
public:
    JsonMap(std::map<std::string, std::string> &jsonMap);
    JsonMap(std::string &s);
    JsonMap(const char *s, int len = 0);
    ~JsonMap() { }

    std::map<std::string, std::string> getMap()
    { return m_jsonMap; }

    std::string toString()
    { return m_jsonString; }

private:
    void init(std::string &s);
    std::string m_jsonString;
    std::map<std::string, std::string> m_jsonMap;
};

#endif // _JSON_MAP_H_
