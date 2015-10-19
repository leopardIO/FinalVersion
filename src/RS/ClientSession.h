#ifndef ClientSession_H
#define ClientSession_H

#include <deque>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>

using boost::asio::ip::tcp;  

namespace cjtech{
    namespace RootServer{
        class ClientMessage;
        class ClientSession
        {
            public:
                ClientSession(boost::asio::io_service& io_service);
                virtual ~ClientSession();
                tcp::socket& socket();
                void start();
                void h_json_header_len(const boost::system::error_code& error);
                void h_json_body(const boost::system::error_code& error);
                void h_file_body(const boost::system::error_code& error);
                void sent_result_back(const boost::system::error_code& error);
                void try_send_msg();
                void add_out_msg(ClientMessage* out_msg);
            private:
                boost::mutex _mtx_;
                ClientMessage* _on_recv_msg_;
                tcp::socket _socket_;
                std::deque<ClientMessage*> _cli_write_buf_;
        };
    }
}

#endif
