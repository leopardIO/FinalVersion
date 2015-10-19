/*************************************************************************
  > File Name: message.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sun 26 Jul 2015 07:33:04 AM UTC
 ************************************************************************/
#include "ClientMessage.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/time.h>
#include "JsonMap.h"

using std::cout;
using std::endl;


using namespace std;
using std :: cout;
using std :: endl;

namespace cjtech
{
    namespace RootServer
    {
        bool ClientMessage::ParserJson()
        {
            _json_body_ = string(_json_body_c_, _json_body_len_);
            JsonMap json_map = JsonMap(_json_body_);
            _json_map_ = json_map.getMap();
            return true;
        }    
        bool ClientMessage::ParserProtoBuf()
        {
            return true;
        }
        void ClientMessage::TranJsonLenCharToInt()
        {
            string str_json_len = string( _json_header_len_c_, header_len);
            _json_body_len_ = atoi(str_json_len.c_str());
            _json_body_c_ = (char*)malloc(sizeof(char)*_json_body_len_);
            return;
        }

        int ClientMessage::GetJsonBodyLen()
        {
            return _json_body_len_;
        }

        int ClientMessage::GetOutLen()
        {
            return _out_len_;
        }

        void ClientMessage::TranFileLenToInt()
        {
            string file_len_str = _json_map_["Content-Length"];
            int file_len = atoi(file_len_str.c_str());
            _file_body_len_ = file_len;
            _file_c_ = (char*)malloc(sizeof(char)*file_len);
        }
    }
}

