#include "mutex.h"

namespace Threads
{
    Mutex::Mutex()
    {
        pthread_mutex_init( &mutex, NULL );
    }

    Mutex::~Mutex()
    {
        pthread_mutex_destroy( &mutex );
    }

    void Mutex::Lock()
    {
        int c = pthread_mutex_lock( &mutex );
        if( c )
        {
            throw c;
        }
    }

    void Mutex::Unlock()
    {
        int c = pthread_mutex_unlock( &mutex );
        if( c )
        {
            throw c;
        }
    }

    int Mutex::TryLock()
    {
        int c = pthread_mutex_trylock( &mutex );
        return c;
    }
}
