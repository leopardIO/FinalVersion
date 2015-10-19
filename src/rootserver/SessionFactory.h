#ifndef _SessionFactory_H
#define _SessionFactory_H

#include <map>
#include <list>
#include<string>
#include <boost/thread/mutex.hpp>
#include <boost/asio.hpp>
#include "Singleton.h"
using namespace std;

class Session;
class SessionFactory: public Singleton<SessionFactory>
{
   friend class Singleton<SessionFactory>;
public:
    //add a session to SessionFactory.
    int add( Session* const );
    //get a session base on id.
    Session* get( int ) const;
    //find is there have a session's ID is id.
    bool find( int ) const;
    //SessionFactory will not manager the session.
    bool remove( int );
    //add a session to recycle list.
    void recycle( int );
    //destructor session in recycle list.
    void recycleAll( void );
	void clearAllSession();
    template<typename T>    T* createSession();
    template<typename T>    T* createSession(boost::asio::io_service& io_service,                   
                                        string &str,                                    
                                        string ip , string port);
    template<typename T>    T* createSession(boost::asio::io_service& io_service);
    
    void recyclerSession( Session* );
private:
    SessionFactory();
    ~SessionFactory();

private:
    typedef std::map<int, Session*> SessionMap;
    typedef std::list<Session*> SessionList;

    int generateID( void );

    int sessionID_;
    SessionMap map_;
    SessionList recycleList_;
	boost::mutex mutex_;
};

template<typename T>
T* SessionFactory::createSession()
{
    T* session;
    session = new T();
    if ( session != NULL )
    {
        add( session );
    }

    return session;
}
template<typename T>    
T* createSession(boost::asio::io_service& io_service,                   
                string &str,                                    
                string ip , string port)
{
    T *session;
    session = new T(io_service,str,ip,port);
    if ( session != NULL )
    {
        add( session );
    }

    return session;
    

}
template<typename T>    
T* createSession(boost::asio::io_service& io_service)
{
    T *session;
    session = new T(io_service);
    if ( session != NULL )
    {
        add( session );
    }

    return session;
    


}



#endif

