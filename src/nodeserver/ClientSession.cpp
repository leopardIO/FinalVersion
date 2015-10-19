#include "ClientSession.h"
#include "SearchSession.h"

using std::cout;
using std::cin;
using std::endl;
using boost::asio::ip::tcp;


extern NodeServer::IOServicePool *g_io_service_pool;
extern NodeServer::SessionManager* g_session_manager; 
namespace NodeServer
{
	ClientSession::~ClientSession()
	{
	}

    ClientSession::ClientSession( tcp::socket *temp_socket)
        :_socket_(g_io_service_pool->GetIoService())
    {
      int socketDup = dup(temp_socket->native());  
        _socket_.assign(boost::asio::ip::tcp::v4(), socketDup); 
    }
	void ClientSession::Start()
	{
        cout<<"ClientSession::Run"<<endl;
        cout<<"ClientSession::Run begin read header..."<<endl;
			boost::asio::async_read(_socket_,
				boost::asio::buffer(&_header_,sizeof(struct  HeadStructMessage)),
				boost::bind(&ClientSession::H_Read_Proto, this,
				boost::asio::placeholders::error));
    }
	void ClientSession::H_Read_Header(const boost::system::error_code& error)
	{
		if (!error)
		{
		//async_read 保证将数据读取完毕后才会调用回调函数
            cout<<"Send to Root OK!"<<endl;
            cout<<"ClientSession::H_Read_Header begin read header sizeof head strutct size "<<sizeof(struct  HeadStructMessage)<<endl;
			boost::asio::async_read(_socket_,
				boost::asio::buffer(&_header_,sizeof(struct  HeadStructMessage)),
				boost::bind(&ClientSession::H_Read_Proto, this,
				boost::asio::placeholders::error));
		}
		else
		{
#ifdef DEBUG
			cout<<"error in rootserver"<<endl;
#endif
			g_session_manager->Recycle(GetSessionID());
		}

	}
    void ClientSession::H_Read_Proto(const boost::system::error_code& error)
    {
        if(!error)
        {
            cout<<"ClientSession::H_Read_Header begin read proto : lenght : "<<_header_.length <<endl;
            _proto_buf_ptr_ = new char[_header_.length + 1];
            memset(_proto_buf_ptr_ , 0 ,_header_.length + 1); 
            boost::asio::async_read(_socket_,boost::asio::buffer(_proto_buf_ptr_,(_header_.length)), 
                    boost::bind(&ClientSession::H_Read_File, this,
                        boost::asio::placeholders::error));
        }
        else
        {
        
        }
    }
    void ClientSession::H_Read_File(const boost::system::error_code& error)
    {
        if(!error)
        {
            switch (_header_.type)
            {
                case SEARCH_REQUEST:
                    {
                        cout<<"ClientSession::H_Read_File:search request recved"<<endl;   
                        SearchProtoMessage search_proto_message;  
                        if(!search_proto_message.ParseFromArray(_proto_buf_ptr_,_header_.length))
                        {
#ifdef DEBUG
                            cout<<"ClientSession::H_Read_File: parse error"<<endl;
#endif
                            //g_session_manager->Recycle(GetSessionID());
                            return ;
                        }				
                        cout<<"ClientSession::H_Read_File: parse SUCCESS "<<endl;
                        //获取到picture的length				
                        uint32_t picture_length = search_proto_message.picture_length();
#ifdef DEBUG
                        cout<<"ClientSession::pic len : "<< picture_length <<endl;
#endif
                        _content_buf_ptr_ = new char[search_proto_message.picture_length() + 1];
                        memset(_content_buf_ptr_ , 0 ,search_proto_message.picture_length() + 1);
                        boost::asio::async_read(_socket_,
                            boost::asio::buffer(_content_buf_ptr_,picture_length),
                            boost::bind(&ClientSession::H_New_Search_Session, this,
                                boost::asio::placeholders::error , search_proto_message , _content_buf_ptr_));	
                        break; 
                    }
                default : 
                    cout<<"ClientSession::header.type not recongnize :"<<_header_.type<<endl; 
                break;
            }
        }
        else
        {
        
        }
    
    }

	void ClientSession::H_New_Search_Session(const boost::system::error_code& error ,
            SearchProtoMessage msg,char * content_buf_ptr)
	{
		if (!error)
		{
		//根据任务类型创建新的session，然后再继续监听接下来的连接的请求
			SearchSession * session = g_session_manager->CreateSession<SearchSession>( msg , content_buf_ptr ,GetSessionID());
            session->Start();
            WritePacket();
		}
		else
		{
#ifdef DEBUG
			cout<<"error in rootserver H_New_Session"<<error.message()<<endl;
#endif
			g_session_manager->Recycle(GetSessionID());
		}

	}
    void ClientSession::WritePacket()
    {
        boost::asio::async_write(_socket_,
            boost::asio::buffer(_sring_for_RS_.c_str() , _sring_for_RS_.length()),
                boost::bind(&ClientSession::H_Read_Header, this,
                    boost::asio::placeholders::error));	
        
    }

}

