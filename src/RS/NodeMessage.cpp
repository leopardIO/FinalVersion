/*************************************************************************
  > File Name: NodeMessage.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 08 Aug 2015 01:37:43 AM UTC
 ************************************************************************/

#include "NodeMessage.h"

#include<iostream>
#include<openssl/md5.h>

using namespace std;

void md5cout(char* data, int len)
{
    MD5_CTX x;
    MD5_Init(&x);
    unsigned char d[16];
    MD5_Update (&x, (char *)data, len);
    MD5_Final(d, &x);
    char out[35];
    int i;
    for (i = 0; i < 16; i++)
    {
        sprintf (out + (i*2), "%02X", d[i]);
    }
    out[32] = 0;
    cout<<"the md5 is : "<< out <<endl;
}

namespace cjtech
{
    namespace RootServer
    {
        NodeMessage::NodeMessage()
        {
            send_or_not_ = false;
        }

        NodeMessage::~NodeMessage()
        {
            //~inner_msg();
        }

        char* NodeMessage::GetInnerMsgLoc()
        {
            return _pb_c_;
        }

        uint32_t NodeMessage::GetInnerMsgLen()
        {
            //cout<<" struct head len : "<< _inner_msg_.len << endl;
            //cout<<" struct head type : "<< _inner_msg_.type << endl;
            return _inner_msg_.len;
        }

        char* NodeMessage::GetFileBodyLoc()
        {
            return _file_body_c_;
        }

        size_t NodeMessage::GetFileBodyLen()
        {
            return _file_body_len_;
        }

        char* NodeMessage::GetInnerMsgHeaderLoc()
        {
            return (char*)&_inner_msg_;
        }

        size_t NodeMessage::GetInnerMsgHeaderLen()
        {
            return _proto_len_;
        }

        size_t NodeMessage::GetOutLen()
        {
            return _out_len_;
        }

        char* NodeMessage::GetOutLoc()
        {
            return _data_out_;
        }

        bool NodeMessage::InnerMsgAlloc()
        {
            cout<<" struct head len : "<< _inner_msg_.len << endl;
            cout<<" struct head type : "<< _inner_msg_.type << endl;
            if(_inner_msg_header_len_>=1024*1024)
                return false;
            _pb_c_ = (char*)malloc(sizeof(char)*_inner_msg_.len);
            //_file_body_len_ = inner_msg.result_length();
            //return inner_msg.ParseFromArray( _inner_msg_c_, _inner_msg_header_len_);
            return true;
        }

        bool NodeMessage::ParserProtoBuf()
        {
            return inner_msg.ParseFromString( 
                    string(_pb_c_, _inner_msg_.len));
        }

        bool NodeMessage::FileAlloc()
        {
            if(!ParserProtoBuf())
                return false;
            _file_body_len_ = inner_msg.result_length();
            _file_body_c_ = (char*)malloc(sizeof(char)*_file_body_len_);
            return true;
        }

        void NodeMessage::ClearFileBody()
        {
            if(_file_body_c_ != NULL)
            {
                free(_file_body_c_);
                _file_body_c_ = NULL;
            }
            _file_body_len_ = 0;
        }

        void NodeMessage::SetFileBody(const char* msg , size_t len)
        {
            _file_body_c_ = (char*)malloc(len);
            memcpy(_file_body_c_ , msg , len);
            _file_body_len_ = len;
        }

        void NodeMessage::SetWriteBuf()
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

        void NodeMessage::SetBufMsg2Node()
        {
            uint32_t cmd = 0xa0;
            size_t protofbuf_len = out_msg.ByteSize();
            cout<<"protofbuf_len ::"<< protofbuf_len<<endl;
            cout<<"_file_body_len_ ::"<< write_len_ <<endl;
            cout<<"string pb ::"<< out_msg.SerializeAsString() <<endl;
            cout<<"string pb ::"<< out_msg.picture_name() <<endl;
            cout<<"string pb ::"<< out_msg.picture_length() <<endl;
            cout<<"string pb ::"<< out_msg.task_id() <<endl;
            cout<<"string pb ::"<< out_msg.start_time() <<endl;
            cout<<"string pb ::"<< out_msg.end_time() <<endl;
            _out_len_ = 2*sizeof(uint32_t) + write_len_ + protofbuf_len;
            uint32_t pb_len_ = protofbuf_len;
            cout<<" _out_len_ ::"<<_out_len_<<endl;
            _data_out_ = (char*)malloc(_out_len_);
            //memset(_data_out_, 'a', sizeof(char)*_out_len_);
            if(_data_out_ == NULL)
                cout<<"data out is NULL"<<endl;
            cout<<"before _data_out_ ::"<<_data_out_<<endl;
            char* buf_ptr = _data_out_;
            memcpy( buf_ptr, &pb_len_, sizeof(uint32_t));
            buf_ptr = _data_out_+sizeof(uint32_t);
            memcpy( buf_ptr, &cmd, sizeof(uint32_t));
            buf_ptr = _data_out_+2*sizeof(uint32_t);
            char* pbspace = (char*)malloc(sizeof(char)*protofbuf_len);
            out_msg.SerializeToArray(pbspace, protofbuf_len);
            char* pbspace1 = (char*)malloc(sizeof(char)*protofbuf_len);
            out_msg.SerializeToArray(pbspace1, protofbuf_len);
            cout<<" fuck pb : "<<string(pbspace, protofbuf_len)<<endl;
            out_msg.SerializeToArray( buf_ptr, protofbuf_len);
            buf_ptr = _data_out_+2*sizeof(uint32_t)+protofbuf_len; 
            memcpy( buf_ptr, write_buf_, write_len_);
            string md5("test");
            md5cout((char*)md5.c_str(),md5.length());
            md5cout(pbspace,protofbuf_len);
            md5cout(pbspace1,protofbuf_len);
            md5cout(_data_out_, _out_len_);
        }

        void NodeMessage::SetPB2Node(std::string picture_name,std::string picture_length,
                long int start_time, long int end_time)
        {
        }

        void NodeMessage::SetTaskID(int id)
        {
            out_msg.set_task_id(id);
        }
    }
}
