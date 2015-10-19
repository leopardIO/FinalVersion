#ifndef RootSession_H
#define RootSession_H

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

#include "RootSession.h"
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

	class RootSession :public Session
	{
	public:
		RootSession(short port);
		virtual ~RootSession();
//		void H_Read_Header(const boost::system::error_code& error);
        void H_New_Session(const boost::system::error_code& error);

		void Run();
	private:
		tcp::acceptor _acceptor_;
		tcp::socket *_p_socket_temp_;
//		struct  HeadStructMessage _header_	;
		
	};
}


#endif
