/*************************************************************************
	> File Name: HeadStructMessage.h
	> Author: zhonghx
	> Mail: zhonghongxia@foxmail.com
	> Created Time: Sun 23 Aug 2015 06:57:52 AM UTC
 ************************************************************************/

#ifndef _HEADSTRUCTMESSAGE_H
#define _HEADSTRUCTMESSAGE_H
#include <stdint.h>
struct  HeadStructMessage
{
    uint32_t length; 
    uint32_t type;
    HeadStructMessage():length(0) , type(0){}
    ~HeadStructMessage(){}
}__attribute__( ( packed )) ;
#endif
