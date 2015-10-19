#ifndef SESSION_H
#define SESSION_H
#include <stdint.h>
#include <string>
#include <string.h>
#include "HeadStructMessage.h"
using namespace std;
namespace NodeServer
{
	class Session
	{
	public:
		Session();
		virtual ~Session();
	public :
		void Recycler( void )
		{
			_is_recycler_ = true;
		}
		bool IsRecycler( void )
		{
			return _is_recycler_;
		}
		void SetSessionID( uint32_t id )
		{
			_sessionID_ = id;
		}
		uint32_t GetSessionID()
		{
			return _sessionID_;
		}		
		string FormMessage(uint32_t proto_length , uint32_t  proto_type , string &proto_str,string & content_str);
		
	private :
		uint32_t _sessionID_ ;
		bool _is_recycler_ ; 
	};




}

#endif
