/*************************************************************************
  > File Name: test_rootserver.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 01 Aug 2015 08:52:50 AM UTC
 ************************************************************************/
#include "IOServerPool.h"
#include "RootServer.h"
#include "Protocol.h"
#include<iostream>

using namespace std;
using namespace cjtech::RootServer;
IOServerPool g_io_service_pool(IO_SEVICE_NUM);

int main(int argn, char** argv)
{
    //boost
    RootServer s(6002, g_io_service_pool);
    s.run();
    while(true)
    {
        sleep(1000);
    }
    return 0;
}
