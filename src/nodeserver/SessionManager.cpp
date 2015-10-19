#include <cassert>
#include <algorithm>

#include "Session.h"
#include "SessionManager.h"

#include <cstdio>
using std::for_each;

namespace NodeServer
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


    SessionManager::SessionManager():
        _sessionID_( 0 ),
        _map_(),
        _recycle_all_list_()
    {
    }

    SessionManager::~SessionManager()
    {
        ;

    }

    int SessionManager::Add( Session* session )
    {
        int id = GenerateID();
        _map_[id] = session;
        session->SetSessionID( id );
        return id;
    }

    Session* SessionManager::Get( int id )const
    {
        Session* session = NULL;
        SessionMap::const_iterator it = _map_.find( id );
        if ( it != _map_.end() )
        {
            session = it->second;
        }
        return session;
    }

    bool SessionManager::Find( int id )const
    {
        SessionMap::const_iterator it = _map_.find( id );
        if ( it != _map_.end() )
        {
            return true;
        }
        return false;
    }

    bool SessionManager::Remove( int id )
    {
        SessionMap::size_type eraseCount = _map_.erase( id );
        return ( eraseCount != 0 );
    }

    void SessionManager::Recycle( int id )
    {
        Session* session = NULL;

        if ( Find( id ) )
        {
            session = Get( id );
            if ( !Remove( id ) )//将这个session id 从map里面删除
            {
            }
            SessionList::iterator ait = 
                _recycle_all_list_.insert( _recycle_all_list_.end(), session );
            if ( ait == _recycle_all_list_.end() )
            {
            }

            session->Recycler();
        }
        return;
    }

    void SessionManager::RecycleAll()
    {
        if ( !_recycle_all_list_.empty() )
        {
            for_each( 
                _recycle_all_list_.begin(), _recycle_all_list_.end(), SessionDeleter() );
            _recycle_all_list_.clear();
        }
        return;
    }

    void
    SessionManager::ClearAllSession()
    {
        if ( !_map_.empty() )
        {
            for (SessionMap::iterator it = _map_.begin();
                it != _map_.end();)
            {
                SessionMap::iterator tempit = it;
                ++it;
                Recycle( tempit->first );
            }
        }
    }

    int SessionManager::GenerateID()
    {
        ++_sessionID_;
        return _sessionID_;
    }

    void SessionManager::RecycleSession( Session* session )
    {
        if ( session != NULL )
        {
            session->Recycler();
            Recycle( session->GetSessionID() );//对于取数据的函数，直接用小写
        }
        return;
    }

}
