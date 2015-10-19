/*************************************************************************
	> File Name: mainthread.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 11 Jul 2015 02:10:27 AM UTC
 ************************************************************************/

#include<iostream>
#include<pthread.h>
#include<string.h>
#include <sys/time.h>

#include "../../common/includeopencv/interface.h"
#include "./JsonMap.h"

#define THREADNUM 10
#define RETIMES 10
#define PICPATH "./test.jpg"
#define FEATUREPATH "./dest/"
#define TRANDIR "./trandir/"
#define INDEXPATH "./index"


using namespace std;

pthread_t* tid;
Matcher* test;

void *opencvMatch( void* arg)
{
    int j = 0;
    for( ; j < RETIMES; j++)
    {
        string ret =  test->match( PICPATH, FEATUREPATH, TRANDIR);
    }
    return NULL;
}

int main( int argc, char** argv)
{
    struct timeval tv_begin, tv_end;
    int pc_ret = 0;
    int i = 0;
    gettimeofday(&tv_begin, NULL);
    tid = ( pthread_t*)malloc( sizeof(pthread_t)*THREADNUM);
    test = new Matcher();
    test->train( TRANDIR, FEATUREPATH, INDEXPATH);
    for( i = 0; i < THREADNUM; i++ ){
    if ( 0 !=  (pc_ret = pthread_create( &tid[i], NULL, opencvMatch, NULL)))
    {
        printf("pc_ret %d\n", pc_ret);
    }
    }
    for( i = 0; i < THREADNUM; i++)
    {
        pthread_join( tid[i], NULL);
    }
    gettimeofday(&tv_end, NULL);
    int sec = tv_end.tv_sec - tv_begin.tv_sec;
    int usec = tv_end.tv_usec - tv_begin.tv_usec;
    printf("calculate %d times\ntime used: %d s %d us\n", RETIMES*THREADNUM ,sec,usec);
    return 0;
}
