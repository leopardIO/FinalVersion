/*************************************************************************
  > File Name: ClientSession.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 25 Jul 2015 05:19:21 PM UTC
 ************************************************************************/

#include "ClientSession.h"
#include <iostream>
#include <sys/syscall.h>
#include <pthread.h>
#include <glog/logging.h>

#include "ClientMessage.h"
#include "SessionService.h"

using namespace std;
using boost::asio::ip::tcp;  

extern cjtech::RootServer::SessionService* g_session_service;

namespace cjtech{
    namespace RootServer{
        boost::mutex g_mtx;
        ClientSession::ClientSession(boost::asio::io_service& io_service)
            : _socket_(io_service)
        {

        }

        ClientSession::~ClientSession()
        {
            //        boost::mutex::scoped_lock lock(cout_mtx);
        }

        tcp::socket& ClientSession::socket()
        {
            return _socket_;
        }

        void ClientSession::start()
        {
            std::cout<<"clientsession::start"<<std::endl;
            pthread_t tid =  pthread_self();
            std::cout<<"clientsession::start::tid"<<tid<<std::endl;
            printf("child thread lwpid = %u\n", syscall(SYS_gettid));
            printf("child thread tid = %u\n", pthread_self()); 
            _on_recv_msg_ = new ClientMessage();
            boost::asio::async_read(_socket_, boost::asio::buffer(_on_recv_msg_->GetJsonLenLoa(), 
                        _on_recv_msg_->GetJsonHeaderLen()),
                    boost::bind(&ClientSession::h_json_header_len, this, 
                        boost::asio::placeholders::error));
        }

        void ClientSession::h_json_header_len(const boost::system::error_code& error)
        {        
            if(!error)
            {
                pthread_t tid =  pthread_self();
                std::cout<<"clientsession::json_header_len_recved::tid"<<tid<<std::endl;
                std::cout<<"clientsession::json lens recved"<<std::endl;
                _on_recv_msg_->TranJsonLenCharToInt();
                boost::asio::async_read(_socket_, boost::asio::buffer(_on_recv_msg_->GetJsonBodyLoc(), 
                            _on_recv_msg_->GetJsonBodyLen()),
                        boost::bind(&ClientSession::h_json_body, this, 
                            boost::asio::placeholders::error));
            }
            else 
            {
                delete this;
            }
        }

        void ClientSession::h_json_body(const boost::system::error_code& error)
        {
            if (!error)
            {
                std::cout<<"ClientSession::json body recved"<<std::endl;
                _on_recv_msg_->ParserJson();
                _on_recv_msg_->TranFileLenToInt();
                boost::asio::async_read(_socket_,boost::asio::buffer(_on_recv_msg_->GetFileBodyLoc(),
                            _on_recv_msg_->GetFileBodyLen()),
                        boost::bind(&ClientSession::h_file_body, this, 
                            boost::asio::placeholders::error));
            }
            else
            {
                delete this;
            }
        }

        void ClientSession::h_file_body(const boost::system::error_code& error)
        {
            if (!error)
            {	
                /*todo:handle file body
                 *g_ClientSession_manager(_on_recv_msg_);
                 */
                SessionService* g_session_service = SessionService::getInstance();
                g_session_service->RequsetHandler(this, this->_on_recv_msg_);
                //LOG(INFO) <<"my first info";
                std::cout<<"ClientSession::file body recved"<<std::endl;
                std::cout<<_on_recv_msg_->GetJsonString()<<std::endl;
                _on_recv_msg_ = NULL;
                this->start();
            }
            else
            {
                delete this;
            }
        }

        void ClientSession::sent_result_back(const boost::system::error_code& error)
        { 
            if(!error){
                int out_que_size = _cli_write_buf_.size();
                while( _cli_write_buf_.front()->send_or_not_)
                {
                    out_que_size = _cli_write_buf_.size();
                    if(out_que_size == 0)
                    {
                        break;
                    }
                    delete _cli_write_buf_.front();
                    _cli_write_buf_.pop_front();
                }
                if( out_que_size>=1)
                {
                    _cli_write_buf_.front()->send_or_not_ = true;
                    async_write(_socket_,boost::asio::buffer(
                                _cli_write_buf_.front()->GetOutLoc(),
                                _cli_write_buf_.front()->GetOutLen()),
                            boost::bind(&ClientSession::sent_result_back, this,
                                boost::asio::placeholders::error ));
                }
            }else
            {

            }
        }

        void ClientSession::try_send_msg()
        {
            /*这个函数的存在书为了线程的切换*/
            boost::mutex::scoped_lock locker(g_mtx);
            int out_que_size = _cli_write_buf_.size();
            if(out_que_size>=1)
            {
                _cli_write_buf_.front()->send_or_not_ = true;
                async_write(_socket_,boost::asio::buffer(
                            _cli_write_buf_.front()->GetOutLoc(),
                            _cli_write_buf_.front()->GetOutLen()),
                        boost::bind(&ClientSession::sent_result_back, this,
                            boost::asio::placeholders::error ));
            }
        }

        void ClientSession::add_out_msg(ClientMessage* out_msg)
        {
            boost::mutex::scoped_lock locker(g_mtx);
            _cli_write_buf_.push_back(out_msg);
        }
    }
}
