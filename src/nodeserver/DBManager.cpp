#include "DBManager.h"

using std::pair;
namespace NodeServer
{

    void DBManager::init(const char * sql_host_name ,const char * sql_user_name ,
            const char * sql_passwd ,const char * db_name)
    {
        MYSQL mysql;
        MYSQL_RES *result = NULL;
        mysql_init(&mysql);
        if(NULL == mysql_real_connect(&mysql, sql_host_name, sql_user_name, 
                    sql_passwd,db_name, 3306, NULL, 0))
        {
            fprintf(stderr, "error: %s",mysql_error(&mysql)); 
            cout<<"127.0.0.1 connect error!"<<endl; //#最后要改成是log格式
        }
        string str = "select name, url, id, video_id, keepword1 from picture;";
        mysql_query(&mysql, str.c_str());
        result = mysql_store_result(&mysql);
        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(result);
        while(NULL != row)
        {
            if(row[0] == NULL)
            {
                row = mysql_fetch_row(result);
                continue;
            }
            if(row[1] == NULL)
                _picture_map_[row[0]] = "NOT FOUND";
            else
                cout<<"key : "<<row[0]<<" value : \""<<row[2]<<"\" get "<<endl;// for test 
            _picture_map_[row[0]] = row[1];

            struct Picture pic_struct;
            pic_struct.pic_name_ = row[0] != NULL ? row[0] : "NULL";
            pic_struct.picture_id_ = atoi(row[2]);
            pic_struct.vedio_id_ = row[3] != NULL ? atoi(row[3]) : -1;
            pic_struct.web_url_ = row[4] != NULL ? row[4] : "NULL";
            _pic_struct_map_.insert(std::make_pair(row[0],pic_struct));
            row = mysql_fetch_row(result);
        }
        mysql_close(&mysql);	
        cout<<"DB get success !"<<endl;//最后要改成log


        MYSQL mysql_two;
        MYSQL_RES *result_two = NULL;
        mysql_init(&mysql_two);
        if(NULL == mysql_real_connect(&mysql_two, sql_host_name, sql_user_name, 
                    sql_passwd,db_name, 3306, NULL, 0))
        {
            fprintf(stderr, "error: %s",mysql_error(&mysql_two)); 
            cout<<"127.0.0.1 connect error!"<<endl; //#最后要改成是log格式
        }
        string str_two = "select id, picture_id from mjproduct;";
        mysql_query(&mysql_two, str_two.c_str());
        result_two = mysql_store_result(&mysql_two);
        MYSQL_ROW row2 = NULL;
        row2 = mysql_fetch_row(result_two);
        while(NULL != row2)
        {
            int pic_id = atoi(row2[1]);
            struct MJproduct mj;
            mj.picture_id_ = pic_id;
            mj.mjproduct_id_ = row2[0];
            _mj_struct_map_[pic_id] = mj;
            cout<<"mj id : "<<mj.mjproduct_id_<< " pic Id : "<< pic_id<<endl;
            row2 = mysql_fetch_row(result_two);
        }
        mysql_close(&mysql_two);
    }

    const char * DBManager::Query(const char * name)
    {
        cout<<"Search in db cache :"<<name<<endl;
        _iter_ = _picture_map_.find(name);
        if(_iter_ != _picture_map_.end())
        {
            return _iter_->second;
        }
        else
        {
            //最后要改成log
            return "NOT FOUND IN MAP";
        }
    }

    string DBManager::GetMJID(vector<int> pic_id)
    {
        int j = 0;
        int vec_len = pic_id.size();
        for( ; j <vec_len; j++){
            cout<<"find in mj struct : " << pic_id[j] <<endl;
        }
        int i;
        int len = pic_id.size();
        string rt;
        for( i = 0; i < len; i ++)
        {
            rt = _mj_struct_map_[pic_id[i]].mjproduct_id_;
            if(rt.length()>1)
                return rt;
        }
        return string("");
    }

    vector<int> DBManager::GetPicID(char* match_name)
    {
        vector<int> temp_rt;
        cout<<"find in pic struct : " << match_name <<endl;
        pair<multimap<string , struct Picture>::iterator, 
            multimap<string , struct Picture>::iterator> rt = _pic_struct_map_.equal_range(string(match_name));
        multimap<string , struct Picture>::iterator ite;      
        for(ite = rt.first; ite != rt.second; ite++)
        {
            temp_rt.push_back(ite->second.picture_id_);
        }
        return temp_rt;
    }
}
