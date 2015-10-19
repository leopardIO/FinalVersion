/*************************************************************************
  > File Name: message.h
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sun 26 Jul 2015 07:33:15 AM UTC
 ************************************************************************/

#ifndef _CLIMESSAGE_H
#define _CLIMESSAGE_H

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
                bool ParserJson();
                bool ParserProtoBuf();
                void TranJsonLenCharToInt();
                int GetJsonBodyLen();
                void TranFileLenToInt();
            private:
                enum { header_len = 12 };
                enum { max_body_len = 10240 };
                char data_[header_len + max_body_len];
                std::map<std::string,std::string> _json_map_;
                std::string _json_body_;
                std::string _proto_buf_body_;
                uint32_t _json_body_len_;
                uint32_t _file_body_len_;
                char _json_header_len_c_[12];
                char* _json_body_c_;
                char* _file_c_;
        };
    }
}

#endif



