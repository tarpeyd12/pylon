#include "mutex.h"

namespace Threads
{
    unsigned int Mutex::numBlocks = 0;;
    unsigned int Mutex::numMutexes = 0;

    Mutex::Mutex()
    {
        mutexIDnum = numMutexes++;
        pthread_mutex_init( &mutex, NULL );
        locked = false;
    }

    Mutex::~Mutex()
    {
        --numMutexes;
        pthread_mutex_destroy( &mutex );
        locked = false;
    }

    void Mutex::Lock()
    {
        if( locked )
        {
            ++numBlocks;
            //std::cout << "Mutex(" << mutexIDnum << ") is already locked!" << std::endl;
        }
        int c = pthread_mutex_lock( &mutex );
        if( c )
        {
            throw c;
        }
        locked = true;
    }

    void Mutex::Unlock()
    {
        if( !locked )
        {
            ++numBlocks;
            //std::cout << "Mutex(" << mutexIDnum << ") already unlocked!" << std::endl;
        }
        int c = pthread_mutex_unlock( &mutex );
        if( c )
        {
            throw c;
        }
        locked = false;
    }

    int Mutex::TryLock()
    {
        if( locked )
        {
            ++numBlocks;
            //std::cout << "Mutex(" << mutexIDnum << ") is already locked!" << std::endl;
        }
        int c = pthread_mutex_trylock( &mutex );
        locked = !c;
        return c;
    }

    bool Mutex::isLocked() const
    {
        return locked;
    }
}
