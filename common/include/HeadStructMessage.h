/*************************************************************************
	> File Name: HeadStructMessage.h
	> Author: zhonghx
	> Mail: zhonghongxia@foxmail.com
	> Created Time: Sun 23 Aug 2015 06:57:52 AM UTC
 ************************************************************************/

#ifndef _HEADSTRUCTMESSAGE_H
#define _HEADSTRUCTMESSAGE_H
#include <stdint.h>
typedef struct  HeadStructMessage
{
    uint32_t protolen; 
    uint32_t proto_type;
    HeadStructMessage():protolen(0) , proto_type(0){}
    ~HeadStructMessage(){}
}__attribute__( ( packed )) HeadStructMessage;
#endif
