
#ifndef COMMON_SYS_SINGLETON_H_
#define COMMON_SYS_SINGLETON_H_

#include <cstddef>
#include <pthread.h>

template <typename T>
class Singleton
{
public:

    virtual ~Singleton() {}

    static T* getInstance()
    {
        pthread_once( &m_instanceInitFlag, &Singleton::initInstance );
        return m_pInstance;
    }

	static void destroyInstance()
	{
	    pthread_once( &m_instanceDeleteFlag, &Singleton::deleteInstance );
	}
		
protected:
    // can't new
    Singleton() {}

private:
    static pthread_once_t m_instanceInitFlag;  // to protect m_pInstance
    static pthread_once_t m_instanceDeleteFlag;
    static T* m_pInstance;  // singleton

private:
    // can't copy
    Singleton( const Singleton& s );
    Singleton& operator=( const Singleton& s );

    // init m_pInstance
    static void initInstance()
    {
        m_pInstance = new T();
    }
	static void deleteInstance()
	{
	    if ( m_pInstance != NULL)
	    	{
	    	    delete m_pInstance;
		    m_pInstance = NULL;
	    	}
	}
};

template <typename T>
pthread_once_t Singleton<T>::m_instanceInitFlag 
   = PTHREAD_ONCE_INIT;

template <typename T>
pthread_once_t Singleton<T>::m_instanceDeleteFlag 
   = PTHREAD_ONCE_INIT;

template <typename T>
T* Singleton<T>::m_pInstance = NULL;

#endif  // COMMON_SYS_SINGLETON_H_

