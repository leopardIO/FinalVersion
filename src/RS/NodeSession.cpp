/*************************************************************************
  > File Name: NodeSession.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 08 Aug 2015 01:39:38 AM UTC
 ************************************************************************/
#include "NodeSession.h"
#include <iostream>
#include<stdlib.h>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include "../../common/includeopencv/interface.h"
#include "NodeMessage.h"
#include "SessionService.h"

using namespace std;

namespace cjtech
{
    namespace RootServer
    {
        NodeSession::NodeSession(boost::asio::io_service& io_service,
                tcp::resolver::iterator endpoint_iterator):
            _socket_(io_service)
        {
            boost::asio::async_connect(_socket_, endpoint_iterator,
                    boost::bind(&NodeSession::ConnectAfter, this,
                        boost::asio::placeholders::error));
            cout<<"bind connecct after"<<endl;
        }

        NodeSession::~NodeSession()
        {
            cout<<"+++++++++++++++++++++node session delete"<<endl;
        }

        tcp::socket& NodeSession::GetSocket()
        {
            return _socket_;
        }

        void NodeSession::ConnectAfter(const boost::system::error_code& error)
        {
#ifdef DEBUG
            cout<<"rootsession::start"<<endl;
#endif
            if(!error){
                cout<<"connect after read pb head :"<< _on_recv_msg_->GetInnerMsgHeaderLen()<<endl;
                _on_recv_msg_ = new NodeMessage();
                boost::asio::async_read(_socket_,
                        boost::asio::buffer(_on_recv_msg_->GetInnerMsgHeaderLoc(),
                            _on_recv_msg_->GetInnerMsgHeaderLen()),
                        boost::bind(&NodeSession::HandleProtobufHeaderLen, this,
                            boost::asio::placeholders::error));
            }else
            {
                cout<<"error happen while connect to ns"<<endl;
                std::cout << boost::system::system_error(error).what() << std::endl;
            }
        }

        void NodeSession::HandleProtobufHeaderLen(const boost::system::error_code& error)
        {
            //cout<<"pb head len : "<< *(_on_recv_msg_->GetInnerMsgHeaderLoc())<<endl;
            cout<<"recv pb len : "<<(_on_recv_msg_->GetInnerMsgLen())<<endl;
            bool alloc = _on_recv_msg_->InnerMsgAlloc();
            if(!error && alloc)
            {
#ifdef DEBUG
                cout<<"rootsession::protobuf head recved"<<endl;
#endif
                boost::asio::async_read(_socket_, boost::asio::buffer(_on_recv_msg_->GetInnerMsgLoc(), 
                            _on_recv_msg_->GetInnerMsgLen()),
                        boost::bind(&NodeSession::HandleProtobufBody, this, 
                            boost::asio::placeholders::error));
            }
            else
            {

            }
        }

        void NodeSession::HandleProtobufBody( const boost::system::error_code& error)
        {
            bool alloc = _on_recv_msg_->FileAlloc();
            if( !error && alloc)
            {
                cout<<"protobuf body recved"<<endl;
                boost::asio::async_read(_socket_, boost::asio::buffer(_on_recv_msg_->GetFileBodyLoc(), 
                            _on_recv_msg_->GetFileBodyLen()),
                        boost::bind(&NodeSession::SendbackResult, this, 
                            boost::asio::placeholders::error));
            }
            else
            {
                RAW_LOG(INFO,"NodeSession::HandleProtobufBody find error");
            }
        }

        void NodeSession::HandleFileBody( const boost::system::error_code& error)
        {
            if(!error)
            {
                /*
                cout<<"Match resved"<<_on_recv_msg_->GetFileBodyLen()<<endl;
                 * todo:error handle
                 * attention;
                 * 
                boost::asio::async_write(_socket_, 
                        boost::asio::buffer(_on_recv_msg_->write_buf_,_on_recv_msg_->write_len_),  
                        boost::bind(&NodeSession::SendbackResult, this, 
                            boost::asio::placeholders::error));
                 */
            }
            else
            {
                RAW_LOG(INFO,"NodeSession::HandleFileBody find error");
            }
        }

        void NodeSession::SendbackResult( const boost::system::error_code& error)
        {
            if(!error)
            {
                cout<<"Send back OK!"<<endl;
                SessionService* g_session_service = SessionService::getInstance(); 
                g_session_service->NodeHandler(this, _on_recv_msg_);
                _on_recv_msg_ = new NodeMessage();
                boost::asio::async_read(_socket_,
                        boost::asio::buffer(_on_recv_msg_->GetInnerMsgHeaderLoc(),
                            _on_recv_msg_->GetInnerMsgHeaderLen()),
                        boost::bind(&NodeSession::HandleProtobufHeaderLen, this,
                            boost::asio::placeholders::error));
            }
            else
            {
                RAW_LOG(INFO,"NodeSession::SendbackResult find error");
            }
        }

        void NodeSession::DoWrite(const boost::system::error_code& error)
        {
            RAW_LOG(INFO,"On write");
            if(!error){
                //boost::mutex::scoped_lock locker(_mtx_);
                if( _node_write_buf_.size() == 0 )
                {
                    return ;
                }
                cout<<" size of que = "<<_node_write_buf_.size()<<endl;
                while(_node_write_buf_.size() != 0)
                {
                    NodeMessage* msg = _node_write_buf_.front();
                    if( msg->send_or_not_)// while to if  zhx 
                    {
                        RAW_LOG(INFO,"delete MSG");
                        _node_write_buf_.pop();
                        delete msg;
                        if(_node_write_buf_.empty())
                        {
                            return ;
                        }
                    }
                    else 
                    {
                        break; 
                    }
                }
                cout<<" size of que = "<<_node_write_buf_.size()<<endl;
                if( _node_write_buf_.size()>=1)
                {
                    RAW_LOG(INFO,"Do write");
                    cout<<"NodeSession out len: "<<_node_write_buf_.front()->GetOutLen()<<endl;
                    async_write(_socket_,boost::asio::buffer(
                                _node_write_buf_.front()->GetOutLoc(),
                                _node_write_buf_.front()->GetOutLen()),
                            boost::bind(&NodeSession::DoWrite, this,
                                boost::asio::placeholders::error ));
                    _node_write_buf_.front()->send_or_not_ = true;
                }
            }
            else
            {
                std::cout << boost::system::system_error(error).what() << std::endl;
            }
        }

        void NodeSession::TrySendMsg(NodeMessage* msg)
        {
            RAW_LOG(INFO,"node try send");
            boost::mutex::scoped_lock locker(_mtx_);
            _node_write_buf_.push(msg);
            int out_que_size = _node_write_buf_.size();
            boost::system::error_code error;
            DoWrite(error);

            /*
            if(0 < out_que_size){
                _node_write_buf_.front()->send_or_not_ = true;
                async_write(_socket_,boost::asio::buffer(
                            _node_write_buf_.front()->GetOutLoc(),
                            _node_write_buf_.front()->GetOutLen()),
                        boost::bind(&NodeSession::DoWrite, this,
                            boost::asio::placeholders::error ));
            }*/
        }

        void NodeSession::addOutMsg(NodeMessage* out_msg)
        {
            //boost::mutex::scoped_lock locker(_mtx_);
            _node_write_buf_.push(out_msg);
        }

        string NodeSession::_RandomNum()
        {
            int randnum = 0;
            stringstream rand_num_sstr;
            randnum = rand();
            rand_num_sstr<<randnum;
            return rand_num_sstr.str();
        }

        string NodeSession::_WriteToFile(char* msg, int len)
        {
            string store_name;
            return store_name;
        }
    }
}
