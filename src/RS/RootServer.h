//server.h
#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>     //socket
#include <unistd.h>            //gethostname
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
#include "IOServerPool.h"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

#define DEBUG   1
 
using std::cout;
using std::cin;
using std::endl;
using boost::asio::ip::tcp;


namespace cjtech{
    namespace RootServer{
        class RootServer
        {
            public:
                RootServer(short cli_port, int thread_cnt);
                void handle_accept(ClientSession* new_session, 
                        const boost::system::error_code& error);
                void run();
            public:
                IOServerPool io_service_pool_;
            private:
                tcp::acceptor acceptor_;
        };
    }
}

#endif
