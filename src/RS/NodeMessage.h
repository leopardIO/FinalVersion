/*************************************************************************
  > File Name: NodeMessage.h
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 08 Aug 2015 01:37:25 AM UTC
 ************************************************************************/

#ifndef _ROOTMESSAGE_H
#define _ROOTMESSAGE_H

#include "SearchProtoMessage.pb.h"
#include "SearchResultMessage.pb.h"

/*************************************************************************
 *
 *_____________________________________________________________
 *          |              |
 *__________|______________|____________________________________
 *proto len   proto body        file body
 *
 ************************************************************************/

namespace cjtech
{
    namespace RootServer
    {
        struct InnerHead
        {
            uint32_t len;
            uint32_t type;
        };
        class NodeMessage
        {
            public:
                NodeMessage();
                virtual ~NodeMessage();
                char* GetInnerMsgLoc();
                uint32_t GetInnerMsgLen();
                char* GetFileBodyLoc();
                size_t GetFileBodyLen();
                char* GetInnerMsgHeaderLoc();
                size_t GetInnerMsgHeaderLen();
                size_t GetOutLen();
                char* GetOutLoc();
                void ClearFileBody();
                void SetFileBody(const char* msg, size_t len);
                void SetWriteBuf();
                bool InnerMsgAlloc();
                bool ParserProtoBuf();
                bool FileAlloc();
                void SetPB2Node(std::string picture_name,std::string picture_length,
                        long int start_time, long int end_time);
                void SetBufMsg2Node();
                void SetTaskID(int);
            public:
                ::SearchResultMessage inner_msg;//从node节点读出来的数据
                ::SearchProtoMessage out_msg;//从client接过来的数据
                char* write_buf_;//只填充协议外内容
                size_t write_len_;//只负责协议外内容大小
                bool send_or_not_;
            private:
                struct InnerHead _inner_msg_;
                char* _file_body_c_;
                char* _pb_c_;
                std::size_t _file_body_len_;
                std::size_t _inner_msg_header_len_;
                enum{ _proto_len_ = sizeof(struct InnerHead)};
                uint32_t _out_len_;
                char* _data_out_;
        };
    }
}

#endif
