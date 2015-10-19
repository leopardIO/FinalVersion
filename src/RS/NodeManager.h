/*************************************************************************
	> File Name: NodeManager.h
	> Author: cooperz
	> Mail: zbzcsn@qq.com
	> Created Time: Sun 23 Aug 2015 02:23:39 AM UTC
 ************************************************************************/

#ifndef _NODEMANAGER_H
#define _NODEMANAGER_H

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include "NodeSession.h"
#include "IOServerPool.h"

namespace cjtech
{
    namespace RootServer
    {
        struct NodeInfo
        {
            std::string node_ip_;
            std::string node_port_;
            uint32_t node_cpu_;
            uint32_t node_net_io_;
        };

        class NodeManager
        {
            public:
                NodeManager(int threadnum);
                virtual ~NodeManager();
                void UpdateNodeResource( const char* node_ip, const char* port,
                        uint32_t cpu, uint32_t net_io);
                NodeSession* GetNodeByRotate( );
                void GetNodeByResource( char** node_ip, char** node_port);
                void ConnectNodeServer(char* ip, char* port);
                void run();
            private:
                IOServerPool io_service_pool_;
                /*遍历此数据结构*/
                std::vector<boost::shared_ptr<NodeInfo>> node_list_;
                /**/
                std::map< std::string, std::map< std::string , 
                    boost::shared_ptr<NodeInfo>>> node_info_map;
                std::vector<NodeSession*> node_conn_list_;
                uint32_t node_num_;
                uint32_t last_node_server_pos_;
        };
    }
}

#endif
