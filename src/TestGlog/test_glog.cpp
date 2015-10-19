/*************************************************************************
  > File Name: test_glog.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 22 Aug 2015 02:14:27 AM UTC
 ************************************************************************/

#include<iostream>
#include <glog/logging.h>
using namespace std;

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO,"../log/myInfo");
    LOG(INFO) << "HELLO" << "ok!"; 
    return 0;
}
