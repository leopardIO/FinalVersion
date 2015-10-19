/*************************************************************************
  > File Name: ioserverpool.h
  > Author: cooperz
  > Mail: zbzcsn@qq.com
  > Created Time: Sat 25 Jul 2015 06:24:18 PM UTC
 ************************************************************************/

#ifndef _IOSERVICEPOOL_H
#define _IOSERVICEPOOL_H
#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <boost/asio.hpp>


namespace NodeServer
{
	class IOServicePool{
		public:
			explicit IOServicePool(std::size_t pool_size);
			void start();
			void join();
			void stop();
			boost::asio::io_service& GetIoService();
		private:
			typedef boost::shared_ptr<boost::asio::io_service> io_service_sptr;
			typedef boost::shared_ptr<boost::asio::io_service::work> work_sptr;
			typedef boost::shared_ptr<boost::thread> thread_sptr;
			boost::mutex _mtx_;
			std::vector<io_service_sptr> _io_services_;
			std::vector<work_sptr> _work_;
			std::vector<thread_sptr> _threads_; 
			std::size_t _next_io_service_;
	};
}

#endif
