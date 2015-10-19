/*************************************************************************
	> File Name: SearchSession.h
	> Author: cooperz
	> Mail: zbzcsn@qq.com
	> Created Time: Sat 08 Aug 2015 01:39:35 AM UTC
 ************************************************************************/

#ifndef _SearchSession_H
#define _SearchSession_H

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "SearchResultMessage.pb.h"
#include "SearchProtoMessage.pb.h"
#include "HeadStructMessage.h"
#include "Session.h"
#include "IOServicePool.h"
#include "NodeUtil.h"
#include "../../common/includeopencv/interface.h"
#define DEBUG 1
using boost::asio::ip::tcp;  
extern	Matcher* g_pic_matcher;
namespace NodeServer{

	class SearchSession : public  Session 
	{
		public:
//			SearchSession( tcp::socket *temp_socket, struct HeadStructMessage header);
			SearchSession(SearchProtoMessage proto_msg , char * content_buf_ptr, uint32_t id);
			virtual ~SearchSession();
			void Start();
			void PicMatch(const boost::system::error_code& error);

		private:
			std::string _RandomNum_();
			std::string _WriteToFile_(const char* msg, int len);

		private:		
//			char * _proto_buf_ptr_;
//			char * _content_buf_ptr_;
            SearchProtoMessage _proto_msg_;
            string _content_str_;
			string _file_name_;
            uint32_t _client_session_id_;
//			typedef struct HeadStructMessage Header;
//			tcp::socket _socket_;   
//			Header _header_ ;
			
	};
}


#endif
