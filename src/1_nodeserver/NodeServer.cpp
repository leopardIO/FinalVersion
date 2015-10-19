#include "NodeServer.h"

using std::cout;
using std::cin;
using std::endl;
using boost::asio::ip::tcp;

namespace cjtech{
    namespace NodeServer{
        NodeServer::NodeServer(short port, int thread_cnt)
            : io_service_pool_(thread_cnt), 
            acceptor_(io_service_pool_.get_io_service(), tcp::endpoint(tcp::v4(), port))
        {
            RootSession* new_session = new RootSession(io_service_pool_.get_io_service());
            acceptor_.async_accept(new_session->GetSocket(),
                    boost::bind(&NodeServer::handle_accept, this, new_session, 
                        boost::asio::placeholders::error));
        }

        void NodeServer::handle_accept(RootSession* new_session, 
                const boost::system::error_code& error)
        {
            if (!error)
            {
                new_session->Start();
            }
            else
            {
#ifdef DEBUG
                cout<<"error in rootserver"<<endl;
#endif
                delete new_session;
            }
#ifdef DEBUG
            cout<<"accept new task"<<endl;
#endif
            new_session = new RootSession(io_service_pool_.get_io_service());
            acceptor_.async_accept(new_session->GetSocket(),
                    boost::bind(&NodeServer::handle_accept, this, new_session, 
                        boost::asio::placeholders::error));
        }

        void NodeServer::run()
        {
            io_service_pool_.start();
            io_service_pool_.join();
        }
    }
}
