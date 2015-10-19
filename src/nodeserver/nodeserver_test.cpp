#include<iostream>
#include "RootSession.h"
#include "DBManager.h"
#include "IOServicePool.h"
#include "SessionManager.h"
#include "../../common/includeopencv/interface.h"
#include "NodeUtil.h"


using namespace std;
using namespace NodeServer;

Matcher* g_pic_matcher;
DBManager* g_db_manager;
IOServicePool* g_io_service_pool = NULL;
SessionManager* g_session_manager; 

int main(int argn, char** argv)
{
    if(argn !=1)
    {
        cout<< "Do not need parameter " <<argv[1]<<endl;
    }

	g_pic_matcher = new Matcher();
    if((access (INDEXPATH,F_OK)) == 0)
    {
        g_pic_matcher->loadIndex(INDEXPATH);
    }
    else
    {
        g_pic_matcher->train(TRANDIR, FEATUREPATH, INDEXPATH);
    }
	
	g_io_service_pool = new IOServicePool(1);//传入的线程池的大小
	g_session_manager = new SessionManager();
    RootSession *root_session = g_session_manager->CreateSession<RootSession>(6002);
    root_session->Run();
	g_io_service_pool->start();
    g_db_manager = new DBManager();
    g_db_manager->init();
	g_io_service_pool->join();
    /*while(true)
    {
        sleep(1000);
    }*/
    return 0;
}
