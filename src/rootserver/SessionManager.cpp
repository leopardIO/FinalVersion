/*************************************************************************
	> File Name: SessionManager.cpp
	> Author: zhonghx
	> Mail: zhonghongxia@foxmail.com
	> Created Time: Sat 08 Aug 2015 01:51:44 AM UTC
 ************************************************************************/

#include<iostream>
#include "SessionManager.h"
#include "NodeSession.h"
using namespace std;
using namespace cjtech::RootServer;
extern IOServerPool g_io_service_pool;
SessionManager::SessionManager(SessionFactory &s):pos_(0), sessionfactory_(s)
{
    
}
SessionManager::~SessionManager()
{

}
void SessionManager::AddNodeAddr(string ip,string  port)
{
    ip_port_.push_back(make_pair(ip,port));
}
void SessionManager::GetNodeAddr(string &ip, string &port )
{
    mutex_.lock();
    ip=ip_port_[pos_].first;    
    port=ip_port_[pos_].second;    
    pos_++;
    mutex_.unlock();
}
void SessionManager::SendReqtoNode(string req )
{
   //调用SessionFactory创建新的Nodesession 
   string ip;
   string port;
   GetNodeAddr(ip,port);
   g_io_service_pool.get_io_service();
   NodeSession * nodesession = SessionFactory::getInstance()->createSession<NodeSession>(
               g_io_service_pool.get_io_service(),req,ip,port);

   nodesession->Start();
      
   //将消息通过nodesession发送出去

}
void SessionManager::SendReqtoClient(string req)
{
    //NodeSession 读取到了result后，
    //通过解析消息，获取到消息中捎带的clientSession的id
    //然后调用SessionManager::SendReqtoClient函数

    //通过sessionfactory找到这个id对应的Session，将相应的req返回给客户
    //客户采用短链接
    //当
    //当ClientSession把数据发送完毕后，
}
