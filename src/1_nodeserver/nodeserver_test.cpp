/*************************************************************************
  > File Name: test_rootserver.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 01 Aug 2015 08:52:50 AM UTC
 ************************************************************************/
//#include "IOServerPool.h"
//
#include<iostream>
#include "NodeServer.h"
#include "DBToMap.h"
#include "../../common/includeopencv/interface.h"
#include "NodeUtil.h"


using namespace std;
using namespace cjtech::NodeServer;

int main(int argn, char** argv)
{
    extern DBToMap* g_db_cache;
    extern Matcher* g_pic_matcher;
    g_pic_matcher = new Matcher();
    int fd;
    if((fd = access (INDEXPATH,F_OK)) == 0)
    {
        g_pic_matcher->loadIndex(INDEXPATH);
    }
    else
    {
        g_pic_matcher->train(TRANDIR, FEATUREPATH, INDEXPATH);
    }
    g_db_cache = new DBToMap();
    g_db_cache->init();
    NodeServer s(6002, 1);
    s.run();
    while(true)
    {
        sleep(1000);
    }
    return 0;
}
