/*************************************************************************
  > File Name: ClientSession.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 25 Jul 2015 05:19:21 PM UTC
 ************************************************************************/

#include "ClientSession.h"
#include<iostream>
#include "ClientMessage.h"

using namespace std;
using boost::asio::ip::tcp;  
namespace cjtech{
    namespace RootServer{
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
            _msg_ = new ClientMessage();
            boost::asio::async_read(_socket_, boost::asio::buffer(_msg_->GetJsonLenLoa(), 
                        _msg_->GetJsonHeaderLen()),
                    boost::bind(&ClientSession::h_json_header_len, this, 
                        boost::asio::placeholders::error));
        }

        void ClientSession::h_json_header_len(const boost::system::error_code& error)
        {        
            if(!error)
            {
                std::cout<<"clientsession::json lens recved"<<std::endl;
                _msg_->TranJsonLenCharToInt();
                boost::asio::async_read(_socket_, boost::asio::buffer(_msg_->GetJsonBodyLoc(), 
                            _msg_->GetJsonBodyLen()),
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
                _msg_->ParserJson();
                _msg_->TranFileLenToInt();
                boost::asio::async_read(_socket_, boost::asio::buffer(_msg_->GetFileBodyLoc(), 
                            _msg_->GetFileBodyLen()),
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
                *g_ClientSession_manager(_msg_);
                */

                std::cout<<"ClientSession::file body recved"<<std::endl;
                std::cout<<_msg_->GetJsonString()<<std::endl;;
                _msg_ = NULL;
                this->start();
            }
            else
            {
                delete this;
            }
        }

        void ClientSession::h_pic_match(const boost::system::error_code& error)
        {
            if (!error)
            {	
                //进行match的调用
                //
                //
                //
                //            
                query_db();
                //
                //
                //
                //
                sent_result_back();
            }
            else
            {
                delete this;
            }
        }

        void ClientSession::query_db(/*  */)
        {
            //进行数据库的操作  
            //返回的结果记录在my_msg_		
        }	

        void ClientSession::sent_result_back(/*  */)
        { 

        }
    }
}
