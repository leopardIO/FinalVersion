/*************************************************************************
	> File Name: NodeSession.h
	> Author: zhonghx
	> Mail: zhonghongxia@foxmail.com
	> Created Time: Sat 01 Aug 2015 07:36:35 AM UTC
 ************************************************************************/
//最后可以抽象出一个BaseSession出来
#ifndef _NODESESSION_H
#define _NODESESSION_H
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <string>
#include <boost/bind.hpp>  
#include "ProInnerMessage.pb.h"
using boost::asio::ip::tcp;
using namespace std;
//using  NodeSession;
class NodeSession
{
public:

    NodeSession(boost::asio::io_service& io_service, string & str, string ip , string port);
    virtual ~NodeSession();
public:
    void Start();
    void SendRequstToNode(const boost::system::error_code& error);
    void ReadResultHeader(const boost::system::error_code& error);
    void ReadResultProto(const boost::system::error_code& error);
    void ReadResultContent(const boost::system::error_code& error);
    void SendtoClient(const boost::system::error_code& error);
private:
    int session_id_;
    char * data_;
    boost::asio::io_service& io_service_;  
    tcp::socket socket_; 
    char ip_[16];
    char port_[6];
    InnerMessage inner_message_;
};




#endif
