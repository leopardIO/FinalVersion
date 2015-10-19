#include "IOServicePool.h"

using namespace std;
using boost::asio::ip::tcp;

namespace NodeServer
{
    IOServicePool::IOServicePool(size_t pool_size)
        : _threads_(0), _next_io_service_(0)
    { 
        for (std::size_t i = 0; i < pool_size; ++ i)
        {
            io_service_sptr io_service(new boost::asio::io_service);
            work_sptr work(new boost::asio::io_service::work(*io_service));
            _io_services_.push_back(io_service);
            _work_.push_back(work);

        }
    }
    void IOServicePool::start()
    { 
        for (std::size_t i = 0; i < _io_services_.size(); ++ i)
        {
            boost::shared_ptr<boost::thread> thread(new boost::thread(
                        boost::bind(&boost::asio::io_service::run, _io_services_[i])));
            _threads_.push_back(thread);
        }
    }

    void IOServicePool::join()
    {
        for (std::size_t i = 0; i < _threads_.size(); ++ i)
        {
            _threads_[i]->join();
        } 
    }

    void IOServicePool::stop()
    { 
        for (std::size_t i = 0; i < _io_services_.size(); ++ i)
        {
            _io_services_[i]->stop();
        }
    }

    boost::asio::io_service& IOServicePool::GetIoService()
    {
        boost::mutex::scoped_lock lock(_mtx_);
        cout<<"next io service : "<<_next_io_service_<<endl;
        boost::asio::io_service& io_service = *_io_services_[_next_io_service_];
        ++ _next_io_service_;
        if (_next_io_service_ == _io_services_.size())
        {
            _next_io_service_ = 0;
        }
        return io_service;
    }
}
