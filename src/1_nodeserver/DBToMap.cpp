#include "DBToMap.h"

void DBToMap::init(	const char * sql_host_name 	,const char * sql_user_name ,\
			const char * sql_passwd 	,const char * db_name)
{
	MYSQL mysql;
    MYSQL_RES *result = NULL;
    mysql_init(&mysql);
    if(NULL == mysql_real_connect(&mysql, sql_host_name, sql_user_name, sql_passwd,db_name, 3306, NULL, 0))
    {
        fprintf(stderr, "error: %s",mysql_error(&mysql)); 
        cout<<"127.0.0.1 connect error!"<<endl; 
    }
    string str = "select name, url from picture;";
    mysql_query(&mysql, str.c_str());
    result = mysql_store_result(&mysql);
    MYSQL_ROW row = NULL;
    row = mysql_fetch_row(result);
    while(NULL != row)
    {
        if(row[1] == NULL)
		    picture_map_[row[0]] = "NOT FOUND";
        else
            cout<<"插入"<<row[0]<<":"<<row[1]<<endl;
		    picture_map_[row[0]] = row[1];
		row = mysql_fetch_row(result);
    }
    mysql_close(&mysql);	
    cout<<"alter success !"<<endl;
}

const char * DBToMap::query(const char * name)
{
    cout<<"search in db cache:"<<name<<endl;
    iter_ = picture_map_.find(name);
    if(iter_ != picture_map_.end())
    {
       return iter_->second;
    }
    else
    {
       return "NOT FOUND IN MAP";
    }
}
