#ifndef ClientSession_H
#define ClientSession_H

#include <sys/socket.h>
#include <netinet/in.h>     //socket
#include <unistd.h>            //Gethostname
#include <arpa/inet.h>
#include <string.h>            //memset
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

#include "ClientSession.h"
#include "IOServicePool.h"
#include "HeadStructMessage.h"
#include "SessionManager.h"
#include "Session.h"

typedef int SOCKET;
typedef struct sockAddr_in SOCKADDR_IN;
typedef struct sockAddr SOCKADDR;

 
using std::cout;
using std::cin;
using std::endl;
using boost::asio::ip::tcp;


/*************************************************************************
 *
 *整个系统发送的报文的格式
 *+--------------------+--------------+------------------------+
 *|		       	       |		      |						   |												
 *+--------------------+--------------+------------------------+
 * length&type of proto     proto body        file body
 *
 ************************************************************************/

namespace NodeServer{

	class ClientSession :public Session
	{
	public:
        ClientSession( tcp::socket *temp_socket);
		virtual ~ClientSession();
		void H_Read_Header(const boost::system::error_code& error);
        void H_Read_Proto(const boost::system::error_code& error);
        void H_Read_File(const boost::system::error_code& error);  
        void H_New_Search_Session(const boost::system::error_code& error , 
            SearchProtoMessage msg,char * content_buf_ptr);

        void SetWritePacket(string &str)//将外部的数据包加入到回写队列
        {
            _sring_for_RS_ = str;
        }
        void WritePacket();//
		void Start();
	private:
        string _sring_for_RS_;
        tcp::socket _socket_;
		struct  HeadStructMessage _header_	;
        char * _proto_buf_ptr_;
        char * _content_buf_ptr_;
	};
}


#endif
