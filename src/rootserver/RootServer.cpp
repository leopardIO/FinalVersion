#include "RootServer.h"

using std::cout;
using std::cin;
using std::endl;
using boost::asio::ip::tcp;

namespace cjtech{
    namespace RootServer{
        RootServer::RootServer(short port, IOServerPool &io_ser_po)
            : io_service_pool_(io_ser_po), 
            acceptor_(io_service_pool_.get_io_service(), tcp::endpoint(tcp::v4(), port))
        {
            ClientSession* new_session = new ClientSession(io_service_pool_.get_io_service());
            acceptor_.async_accept(new_session->socket(),
                    boost::bind(&RootServer::handle_accept, this, new_session, 
                        boost::asio::placeholders::error));
        }

        void RootServer::handle_accept(ClientSession* new_session, 
                const boost::system::error_code& error)
        {
            if (!error)
            {
                new_session->start();
            }
            else
            {
#ifdef DEBUG
                cout<<"error in rootserver"<<endl;
#endif
                delete new_session;
            }
#ifdef DEBUG
            cout<<"accept new Client"<<endl;
#endif
            new_session = new ClientSession(io_service_pool_.get_io_service());
            acceptor_.async_accept(new_session->socket(),
                    boost::bind(&RootServer::handle_accept, this, new_session, 
                        boost::asio::placeholders::error));
        }

        void RootServer::run()
        {
            io_service_pool_.start();
            io_service_pool_.join();
        }
    }
}
