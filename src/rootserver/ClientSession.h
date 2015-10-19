#ifndef ClientSession_H
#define ClientSession_H
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "Session.h"

using boost::asio::ip::tcp;  

namespace cjtech{
    namespace RootServer{
        class ClientMessage;
        class ClientSession :public Session
        {
            public:
                ClientSession(boost::asio::io_service& io_service);
                virtual ~ClientSession();
                tcp::socket& socket();
                void start();
                void h_json_header_len(const boost::system::error_code& error);
                void h_json_body(const boost::system::error_code& error);
                void h_file_body(const boost::system::error_code& error);
                void h_pic_match(const boost::system::error_code& error);
                void query_db(/*  */);
                void sent_result_back(/*  */);
            private:
                ClientMessage* _msg_;
                tcp::socket _socket_;   
        };
    }
}

#endif
