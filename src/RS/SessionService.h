/*************************************************************************
	> File Name: SessionService.h
	> Author: cooperz
	> Mail: zbzcsn@qq.com
	> Created Time: Sun 23 Aug 2015 07:34:57 AM UTC
 ************************************************************************/

#ifndef _SESSIONSERVICE_H
#define _SESSIONSERVICE_H

#include <map>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "DataFromatSwitch.h"
#include "NodeManager.h"

namespace cjtech
{
    namespace RootServer
    {
        using boost::asio::ip::tcp;
        class ClientMessage;
        class NodeMessage;
        class ClientSession;
        class NodeSession;
        class SessionService
        {
            public:
                static SessionService* getInstance();
                virtual ~SessionService();
                void RequsetHandler( ClientSession* cli_session, 
                        ClientMessage* req_msg); 
                void NodeHandler( NodeSession* node_session,
                        NodeMessage* req_msg);
                void Run();
            private:
                SessionService();
                static SessionService* _pSessionService_;
                boost::mutex _mtx_;  
                uint64_t _task_id_;
                std::map< uint64_t, ClientSession*> _taskid_clises_;
                std::map< uint64_t, NodeSession*> _taskid_ndeses_;
                DataFromatSwitch _data_switcher_;
                NodeManager* node_manager_;
        };
    }
}

#endif
