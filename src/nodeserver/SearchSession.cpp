#include "SearchSession.h"
#include<iostream>
#include "NodeUtil.h"
#include "SessionManager.h"
#include "ClientSession.h"
#include "DBManager.h"

using namespace std;

extern NodeServer::SessionManager *g_session_manager;
extern NodeServer::IOServicePool* g_io_service_pool;
extern NodeServer::SessionManager* g_session_manager; 
extern NodeServer::DBManager * g_db_manager;
namespace NodeServer
{
    
    SearchSession::SearchSession(SearchProtoMessage proto_msg , char * content_buf_ptr, uint32_t id)
        :_proto_msg_(proto_msg) , _content_str_(content_buf_ptr) , _client_session_id_(id)
    {
    }
	SearchSession::~SearchSession()
	{

	}
	void SearchSession::Start()
	{
			/*
			 * todo:error handle
			 * attention;
			 * */
			string filepath = 
				_WriteToFile_(_content_str_.c_str(), _proto_msg_.picture_length());
			cout<<"Write to file path:"<<filepath<<endl;
			string result = g_pic_matcher->match( filepath.c_str(), FEATUREPATH, TRANDIR);
			cout<<"Match result:"<<result<<endl;
            int index = result.find("&&", 0);
            string match_name = result.substr( 0, index );
            int index_pit = result.find(".",0);
            string only_name = result.substr( 0, index_pit );
            string tracker = "/mj/tracker/" + only_name + ".zip";
            char* name_c = (char*)match_name.c_str();
            vector<int> match_pic_id = g_db_manager->GetPicID(name_c);
            cout<<"search_result  pic id size: "<<match_pic_id.size()<<endl;
            string mj_id = g_db_manager->GetMJID(match_pic_id);
			string response = g_db_manager->Query(_file_name_.c_str());
			SearchResultMessage  search_result;
            search_result.set_picture_name(_file_name_);
            cout<<"search_result.set_picture_name : "<<match_name<<endl;
            search_result.set_result_length(response.length());
            cout<<"search_result.set_result_length : "<<response.length()<<endl;
            search_result.set_task_id(_proto_msg_.task_id());
            search_result.set_mj_id(mj_id);
            cout<<"search_result.set_mj_id : "<< mj_id <<endl;
            search_result.set_trackerurl(tracker);
            cout<<"search_result.set_trackerurl : "<< tracker <<endl;
            search_result.set_status(1);
            string proto_str_tmp ;
            search_result.SerializeToString(&proto_str_tmp);
            cout<<"search_result total length : "<< proto_str_tmp.length() <<endl;
            string response_msg =
               Session::FormMessage(proto_str_tmp.length(),SEARCH_REQUEST_RESULT_FROM_NODE,proto_str_tmp,response); 
            ClientSession *client_session = dynamic_cast<ClientSession *> (g_session_manager->Get(_client_session_id_));
            client_session->SetWritePacket(response_msg);
			cout<<"SearchSession::copy result to ClientSession "<<endl;
            g_session_manager->Recycle(GetSessionID());
	}
	string SearchSession::_RandomNum_()
	{
		int randnum = 0;
		stringstream rand_num_sstr;
		randnum = rand();
		rand_num_sstr<<randnum;
		return rand_num_sstr.str();
	}

	string SearchSession::_WriteToFile_(const char* msg, int len)
	{
		string rand_str = _RandomNum_();
		string filepath = string(TMP_PATH) + rand_str;
		cout<<"file path:"<<filepath<<endl;
		int fd = open( filepath.c_str() , O_CREAT | O_RDWR , 0666);
		if(fd<=0)
			perror("open error\n");
		int wnum = ::write(fd , msg, len);
		if(wnum <=0)
		{
			//cout<<"write error"<<endl;
			perror("write error\n");
			return "";
		}
        close(fd);
		return filepath;
	}
}

