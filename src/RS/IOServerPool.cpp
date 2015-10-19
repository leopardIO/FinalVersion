/*************************************************************************
  > File Name: ioserverpool.cpp
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 25 Jul 2015 06:24:03 PM UTC
 ************************************************************************/
#include "IOServerPool.h"

using namespace std;

namespace cjtech{
    namespace RootServer{
        IOServerPool::IOServerPool(size_t pool_size)
            : next_io_service_(0)
        { 
            for (std::size_t i = 0; i < pool_size; ++ i)
            {
                io_service_sptr io_service(new boost::asio::io_service);
                work_sptr work(new boost::asio::io_service::work(*io_service));
                io_services_.push_back(io_service);
                work_.push_back(work);
            }
        }
        void IOServerPool::start()
        { 
            for (std::size_t i = 0; i < io_services_.size(); ++ i)
            {
                boost::shared_ptr<boost::thread> thread(new boost::thread(
                            boost::bind(&boost::asio::io_service::run, io_services_[i])));
                threads_.push_back(thread);
            }
        }

        void IOServerPool::join()
        {
            for (std::size_t i = 0; i < threads_.size(); ++ i)
            {
                threads_[i]->join();
            } 
        }

        void IOServerPool::stop()
        { 
            for (std::size_t i = 0; i < io_services_.size(); ++ i)
            {
                io_services_[i]->stop();
            }
        }

        boost::asio::io_service& IOServerPool::get_io_service()
        {
            boost::mutex::scoped_lock lock(mtx);
            boost::asio::io_service& io_service = *io_services_[next_io_service_];
            ++ next_io_service_;
            if (next_io_service_ == io_services_.size())
            {
                next_io_service_ = 0;
            }
            return io_service;
        }
    }
}
