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
struct ltstr  
{  
	bool operator()(const char* s1, const char* s2) const  
	{  
		return strcmp(s1, s2) < 0;  
	}  
};  
class db_to_map
{
	public :
		const char* query(const char * name);
		void init(	const char * sql_host_name = "localhost",\
					const char * sql_user_name = "root",\
					const char * sql_passwd = "000000" ,\
					const char * db_name = "77db");
					
	private:
		map<const char * ,const char * ,ltstr> picture_map_;		
		map<const char * ,const char * ,ltstr>::iterator iter_;
};
