/*************************************************************************
	> File Name: DBManager.h
	> Author: cooperz
	> Mail: zbzcsn@qq.com
	> Created Time: Sat 08 Aug 2015 09:17:25 AM UTC
 ************************************************************************/

#ifndef _DBManager_H
#define _DBManager_H
#include <iostream>
#include <string.h>
#include <string>
#include <mysql/mysql.h>
#include <stdio.h>
#include <map>

using std::cout;
using std::endl;
using std::map;
using std::string;

struct ltstr  //定义比较操作符的，如果是小于则返回的是1
{  
	bool operator()(const char* s1, const char* s2) const  
	{  
		return strcmp(s1, s2) < 0;  
	}  
};  

class DBManager
{
	public :
		const char* query(const char * name);
		void init(	const char * sql_host_name = "localhost",
					const char * sql_user_name = "root",
					const char * sql_passwd = "1314159" ,
					const char * db_name = "picdb");
					
	private:
		map<const char * ,const char * ,ltstr> picture_map_;		
		map<const char * ,const char * ,ltstr>::iterator iter_;
};
#endif
