/*************************************************************************
  > File Name: ioserverpool.h
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 25 Jul 2015 06:24:18 PM UTC
 ************************************************************************/

#ifndef _IOSERVERPOOL_H
#define _IOSERVERPOOL_H
#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

namespace cjtech
{
    namespace NodeServer
    {
        class IOServerPool{
            public:
                explicit IOServerPool(std::size_t pool_size);
                void start();
                void join();
                void stop();
                boost::asio::io_service& get_io_service();
            private:
                typedef boost::shared_ptr<boost::asio::io_service> io_service_sptr;
                typedef boost::shared_ptr<boost::asio::io_service::work> work_sptr;
                typedef boost::shared_ptr<boost::thread> thread_sptr;
                boost::mutex mtx;
                std::vector<io_service_sptr> io_services_;
                std::vector<work_sptr> work_;
                std::vector<thread_sptr> threads_; 
                std::size_t next_io_service_;
        };
    }
}
#endif
