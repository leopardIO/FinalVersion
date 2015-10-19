
#ifndef COMMON_SYS_SINGLETON_H_
#define COMMON_SYS_SINGLETON_H_

#include <cstddef>
#include <pthread.h>

template <typename T>
class Singleton
{
public:

    virtual ~Singleton() {}

    static T* GetInstance()
    {
        pthread_once( &_instance_initflag_, &Singleton::InitInstance );
        return _p_instance_;
    }

	static void DestroyInstance()
	{
	    pthread_once( &_instance_deleteflag_, &Singleton::DeleteInstance );
	}
		
protected:
    // can't new
    Singleton() {}

private:
    static pthread_once_t _instance_initflag_;  // to protect _p_instance_
    static pthread_once_t _instance_deleteflag_;
    static T* _p_instance_;  // singleton

private:
    // can't copy
    Singleton( const Singleton& s );
    Singleton& operator=( const Singleton& s );

    // init _p_instance_
    static void InitInstance()
    {
        _p_instance_ = new T();
    }
	static void DeleteInstance()
	{
	    if ( _p_instance_ != NULL)
	    	{
	    	    delete _p_instance_;
				_p_instance_ = NULL;
	    	}
	}
};

template <typename T>
pthread_once_t Singleton<T>::_instance_initflag_ 
   = PTHREAD_ONCE_INIT;

template <typename T>
pthread_once_t Singleton<T>::_instance_deleteflag_ 
   = PTHREAD_ONCE_INIT;

template <typename T>
T* Singleton<T>::_p_instance_ = NULL;

#endif  // COMMON_SYS_SINGLETON_H_

