/*************************************************************************
  > File Name: RootMessage.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 08 Aug 2015 01:37:43 AM UTC
 ************************************************************************/

#include "RootMessage.h"

#include<iostream>

using namespace std;

namespace cjtech
{
    namespace NodeServer
    {
        RootMessage::RootMessage()
        {

        }

        RootMessage::~RootMessage()
        {
            //~inner_msg();
        }

        char* RootMessage::GetInnerMsgLoc()
        {
            return _inner_msg_c_;
        }

        size_t RootMessage::GetInnerMsgLen()
        {
            return _inner_msg_header_len_;
        }

        char* RootMessage::GetFileBodyLoc()
        {
            return _file_body_c_;
        }

        size_t RootMessage::GetFileBodyLen()
        {
            return _file_body_len_;
        }

        size_t* RootMessage::GetInnerMsgHeaderLoc()
        {
            return &_inner_msg_header_len_;
        }

        size_t RootMessage::GetInnerMsgHeaderLen()
        {
            return _proto_len_;
        }

        bool RootMessage::InnerMsgAlloc()
        {
            if(_inner_msg_header_len_>=1024*1024)
                return false;
            _inner_msg_c_ = (char*)malloc(sizeof(char)*_inner_msg_header_len_);
            _file_body_len_ = inner_msg.content_length();
            //return inner_msg.ParseFromArray( _inner_msg_c_, _inner_msg_header_len_);
            return true;
        }

        bool RootMessage::ParserProtoBuf()
        {
            return inner_msg.ParseFromArray( _inner_msg_c_, _inner_msg_header_len_);
        }

        bool RootMessage::FileAlloc()
        {
            if(!ParserProtoBuf())
                return false;
            _file_body_len_ = inner_msg.content_length();
            _file_body_c_ = (char*)malloc(sizeof(char)*_file_body_len_);
            return true;
        }

        void RootMessage::ClearFileBody()
        {
            if(_file_body_c_ != NULL)
            {
                free(_file_body_c_);
                _file_body_c_ = NULL;
            }
            _file_body_len_ = 0;
        }

        void RootMessage::SetFileBody(const char* msg , size_t len)
        {
            _file_body_c_ = (char*)malloc(len);
            memcpy(_file_body_c_ , msg , len);
            _file_body_len_ = len;
        }

        void RootMessage::SetWriteBuf()
        {
            size_t protofbuf_len = inner_msg.ByteSize();
            write_len_ = _proto_len_ + _file_body_len_ + protofbuf_len;
            write_buf_ = (char*)malloc(write_len_);
            char* buf_ptr = write_buf_;
            memcpy( buf_ptr, &protofbuf_len, sizeof(protofbuf_len));
            buf_ptr = buf_ptr+sizeof(protofbuf_len);
            inner_msg.SerializeToArray( buf_ptr, protofbuf_len);
            buf_ptr = buf_ptr+protofbuf_len;
            memcpy( buf_ptr, _file_body_c_, _file_body_len_);
            cout<<"write_len_"<<write_len_<<endl;
        }
    }
}
