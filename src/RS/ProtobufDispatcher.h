/*************************************************************************
  > File Name: ProtobufDispatcher.h
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sun 23 Aug 2015 02:12:29 AM UTC
 ************************************************************************/

#ifndef _PROTOBUFDISPATCHER_H
#define _PROTOBUFDISPATCHER_H

#include <boost/function.hpp>
#include <sys/time.h>
#include <boost/asio.hpp>
#include <google/protobuf/message.h>

using boost::asio::ip::tcp;

namespace cjtech
{
    namespace RootServer
    {
        typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;
        typedef boost::function<void (tcp::socket,
                MessagePtr const&,
                struct timeval)> ProtobufMessageCallback;
        class ProtobufDispatcher
        {
            public:
                explicit ProtobufDispatcher(ProtobufMessageCallback const& callback):
                    _defaultcallback_(callback){};
                virtual ~ProtobufDispatcher();
                void onProtobufMessage(tcp::socket asio_socket, 
                        MessagePtr const& pbmsg,
                        struct timeval time_stmap);
                void onClientMessage();
                void RegisterMsgCallBack( google::protobuf::Descriptor const* desc,
                        ProtobufMessageCallback const& callback);
            private:
                ProtobufMessageCallback _defaultcallback_;
        };
    }
}

#endif
