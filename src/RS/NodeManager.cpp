/*************************************************************************
	> File Name: NodeManager.cpp
	> Author: cooperz
	> Mail: zbzcsn@qq.com
	> Created Time: Sat 29 Aug 2015 11:43:37 PM CST
 ************************************************************************/

#include "NodeManager.h"

#include<iostream>
#include<boost/asio.hpp>
#include"NodeSession.h"
#include"IOServerPool.h"

using namespace std;
using boost::asio::ip::tcp; 


namespace cjtech
{
    namespace RootServer
    {
        NodeManager::NodeManager(int threadnum)
            :io_service_pool_(threadnum)
        {
            char* ip = "127.0.0.1";
            char* port= "6002";
            node_num_ = 0;
            ConnectNodeServer( ip, port);
        }

        NodeManager::~NodeManager()
        {

        }

        NodeSession* NodeManager::GetNodeByRotate()
        {
            cout<<"we find nodesession num : "<< last_node_server_pos_++%node_num_ << " total num of node : "<< node_num_ <<endl;
            int node_id = last_node_server_pos_++%node_num_;
            return node_conn_list_[node_id];
        }

        void NodeManager::GetNodeByResource( char** node_ip, char** node_port)
        {

        }

        void NodeManager::ConnectNodeServer(char* ip, char* port)
        {
            cout<<"connect to ip:"<<ip<<"port :"<<port<<endl;
            boost::asio::io_service& io_service = \
               io_service_pool_.get_io_service();

            tcp::resolver resolver(io_service);
            tcp::resolver::query query(ip, port);
            tcp::resolver::iterator iterator = resolver.resolve(query);
            
            NodeSession* new_node = new NodeSession( io_service, iterator);
            node_conn_list_.push_back( new_node);
            node_num_++;
        }

        void NodeManager::run()
        {
            io_service_pool_.start();
            io_service_pool_.join();
        }
    }
}
