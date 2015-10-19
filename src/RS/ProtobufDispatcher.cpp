/*************************************************************************
	> File Name: ProtobufDispatcher.cpp
	> Author: cooperz
	> Mail: zbzcsn@qq.com
	> Created Time: Sat 29 Aug 2015 11:20:26 PM CST
 ************************************************************************/
#include "ProtobufDispatcher.h"

#include<iostream>
using namespace std;


namespace cjtech
{
    namespace RootServer
    {

        ProtobufDispatcher::~ProtobufDispatcher()
        {

        }
        
        void ProtobufDispatcher::onProtobufMessage(tcp::socket asio_socket, 
                MessagePtr const& pbmsg, struct timeval time_stmap)
        {
            
        }

        void RegisterMsgCallBack( google::protobuf::Descriptor const* desc,
                ProtobufMessageCallback const& callback)
        {

        }
    }
}
