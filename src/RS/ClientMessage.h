/*************************************************************************
  > File Name: message.h
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sun 26 Jul 2015 07:33:15 AM UTC
 ************************************************************************/

#ifndef _MESSAGE_H
#define _MESSAGE_H

/***********************************************
  +-----------------------+-------------------------+------------------+
  |		        		  |						    |                  |
  +-----------------------+-------------------------+------------------+
  +<---jsonheader_len---->|<--------json_len------->|<---file_body---->|

 ***********************************************/

#include <iostream>
#include <cstring>
#include <map>

namespace cjtech
{
    namespace RootServer
    {

        class ClientMessage
        {
            public:
                ClientMessage()
                {
                    send_or_not_ = false;
                    _json_body_len_ = 0;
                    _file_body_len_ = 0;
                }
                inline char* GetJsonLenLoa()
                {
                    return _json_header_len_c_;
                }
                inline int GetJsonHeaderLen()
                {
                    return header_len;
                }
                inline char* GetJsonBodyLoc()
                {
                    return _json_body_c_;
                }
                inline char* GetOutLoc()
                {
                    return data_;
                }
                inline int GetFileBodyLen()
                {
                    return _file_body_len_;
                }
                inline char* GetFileBodyLoc()
                {
                    return _file_c_;
                }
                inline std::string GetJsonString()
                {
                    return _json_body_;
                }
                std::string findInJsonMap(std::string key)
                {
                    auto it = _json_map_.find(key);
                    if(it!=_json_map_.end())
                        return it->second;
                    else
                        return "";
                }
                std::string findInJsonMap(const char* keyc)
                {
                    std::string key(keyc);
                    auto it = _json_map_.find(key);
                    if(it!=_json_map_.end())
                        return it->second;
                    else
                        return "";
                }
                void ClearFileLoc()
                {
                    _file_c_ = NULL;
                }
                bool ParserJson();
                bool ParserProtoBuf();
                void TranJsonLenCharToInt();
                int GetJsonBodyLen();
                int GetOutLen();
                void TranFileLenToInt();
            public:
                bool send_or_not_;
                char* out_buf_;
            private:
                enum { header_len = 12 };
                enum { max_body_len = 10240 };
                char* data_;
                std::map<std::string,std::string> _json_map_;
                std::string _json_body_;
                std::string _proto_buf_body_;
                uint32_t _json_body_len_;
                uint32_t _file_body_len_;
                uint32_t _out_len_;
                char _json_header_len_c_[12];
                char* _json_body_c_;
                char* _file_c_;
        };
    }
}

#endif



