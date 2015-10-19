/*
 * =====================================================================================
 *
 *       Filename:  testtool.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/23/2013 07:56:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao(ly), liangyao.ndsl@gmail.com 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef TESTTOOL_H
#define TESTTOOL_H

#include <iostream>
#include <list>
#include <sys/time.h>
#include <assert.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <dirent.h>

class TestTool
{
public:
    TestTool(){};
    static void getFilenameList(
            std::list<std::string> &fileNameList, 
            std::string dirname);
    static std::string getFilename(std::string path); 
    static bool samePrefix(std::string path1, std::string path2);
    
    void setBeginMoment();
    void setEndMoment();
    long getTime();

private:
    struct timeval time_begin, time_end;
};


#endif
