/*************************************************************************
	> File Name: SessionManager.h
	> Author: zhonghx
	> Mail: zhonghongxia@foxmail.com
	> Created Time: Sat 08 Aug 2015 01:51:27 AM UTC
 ************************************************************************/

#ifndef _SESSIONMANAGER_H
#define _SESSIONMANAGER_H
#include <map>
#include <vector>
#include <string>
#include <utility>  
#include "IOServerPool.h"
#include "SessionFactory.h"
#include <boost/thread/thread.hpp>
using std::map;
using std::vector;
using std::string;
using std::pair;
using cjtech::RootServer;
extern IOServerPool g_ioservice_pool;
class SessionManager
{
public:
    SessionManager( SessionFactory &s);
    ~SessionManager();
    void AddNodeAddr(string ip ,string port);
    void GetNodeAddr(string &ip , string & port);
    void SendReqtoNode(string  req);
    void SendReqtoClient(string req);
private:
    vector<pair<string,string> >  ip_port_;
    int pos_;
    SessionFactory &sessionfactory_;
    boost::mutex mutex_;

};
#endif
