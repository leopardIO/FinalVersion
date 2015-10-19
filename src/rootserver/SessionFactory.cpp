#include <cassert>
#include <algorithm>

#include "Session.h"
#include "SessionFactory.h"

#include <cstdio>
using std::for_each;

namespace
{

struct SessionDeleter
{
    void operator()( Session* session )const
    {
        //printf( "%p\n",session);
        if ( session != NULL)
        {
            delete session;
            session = NULL;
        }
    }
};

}

SessionFactory::SessionFactory():
    sessionID_( 0 ),
    map_(),
    recycleList_()
{
}

SessionFactory::~SessionFactory()
{
    ;

}

int SessionFactory::add( Session* session )
{
    int id = generateID();
    map_[id] = session;
    session->set_session_id( id );
    return id;
}

Session* SessionFactory::get( int id )const
{
    Session* session = NULL;
    SessionMap::const_iterator it = map_.find( id );
    if ( it != map_.end() )
    {
        session = it->second;
    }
    return session;
}

bool SessionFactory::find( int id )const
{
    SessionMap::const_iterator it = map_.find( id );
    if ( it != map_.end() )
    {
        return true;
    }
    return false;
}

bool SessionFactory::remove( int id )
{
    SessionMap::size_type eraseCount = map_.erase( id );
    return ( eraseCount != 0 );
}

void SessionFactory::recycle( int id )
{
    Session* session = NULL;

    if ( find( id ) )
    {
        session = get( id );
        if ( !remove( id ) )
        {
        }
        SessionList::iterator ait = 
            recycleList_.insert( recycleList_.end(), session );
        if ( ait == recycleList_.end() )
        {
        }

        session->recycler();
    }
    return;
}

void SessionFactory::recycleAll()
{
    if ( !recycleList_.empty() )
    {
        for_each( 
            recycleList_.begin(), recycleList_.end(), SessionDeleter() );
        recycleList_.clear();
    }
    return;
}

void
SessionFactory::clearAllSession()
{
    if ( !map_.empty() )
    {
        for (SessionMap::iterator it = map_.begin();
            it != map_.end();)
        {
            SessionMap::iterator tempit = it;
            ++it;
            recycle( tempit->first );
        }
    }
}

int SessionFactory::generateID()
{
    ++sessionID_;
    return sessionID_;
}

void SessionFactory::recyclerSession( Session* session )
{
    if ( session != NULL )
    {
        session->recycler();
        recycle( session->session_id() );
    }
    return;
}
