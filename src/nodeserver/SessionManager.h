#ifndef _SessionManager_H
#define _SessionManager_H


#include <map>
#include <list>
#include<string>
#include <boost/thread/mutex.hpp>
#include <boost/asio.hpp>
#include "Singleton.h"
#include "HeadStructMessage.h"
#include "SearchProtoMessage.pb.h"
#include "Session.h"
#include "NodeUtil.h"
#include "stdint.h"
using namespace std;
using namespace boost::asio::ip;

namespace NodeServer
{
    class SessionManager //: public Singleton<SessionManager>
    {
        //   friend class Singleton<SessionManager>;
        public:
            //Add a session to SessionManager.
            int Add( Session* const );
            //Get a session base on id.
            Session* Get( int ) const;
            //Find is there have a session's ID is id.
            bool Find( int ) const;
            //SessionManager will not manager the session.
            bool Remove( int );
            //Add a session to RecycleAll list.
            void Recycle( int );
            //destructor session in RecycleAll list.
            void RecycleAll( void );
            void ClearAllSession();
            //  template<typename T>    T* CreateSession(); 
            //  template<typename T>    T* CreateSession(boost::asio::io_service& io_service); 
            template <typename T > T* 
                CreateSession(tcp::socket *temp_socket, struct HeadStructMessage head_msg);   
            template <typename T > T* 
                CreateSession(tcp::socket *temp_socket);   
            template <typename T > T* 
                CreateSession(short port);   
            template <typename T > T* 
                CreateSession( SearchProtoMessage proto_msg , char * content , uint32_t id);   

            void RecycleSession( Session* );
            //private:
        public:
            SessionManager();
            ~SessionManager();
        private:
            typedef std::map<int, Session*> SessionMap;
            typedef std::list<Session*> SessionList;

            int GenerateID( void );

            int _sessionID_;
            SessionMap _map_;
            SessionList _recycle_all_list_;
            boost::mutex _mutex_;
    };


    template<typename T>    
    T* SessionManager:: CreateSession( tcp::socket *temp_socket, struct HeadStructMessage header)
    {
        T* session;
        session = new T( temp_socket , header);
        if ( session != NULL )
        {
            Add( session );
        }

        return session;
    }  
    template<typename T>    
    T* SessionManager:: CreateSession( tcp::socket *temp_socket)
    {
        T* session;
        session = new T( temp_socket );
        if ( session != NULL )
        {
            Add( session );
        }

        return session;
    }  
    template<typename T>    
    T* SessionManager:: CreateSession( short port)
    {
        T* session;
        session = new T( port);
        if ( session != NULL )
        {
            Add( session );
        }
        return session;
    }  
    template<typename T>    
    T* SessionManager:: CreateSession( SearchProtoMessage proto_msg , char * content ,uint32_t id)
    {
        T* session;
        session = new T( proto_msg,content , id);
        if ( session != NULL )
        {
            Add( session );
        }

        return session;
    }  
}        
#endif

