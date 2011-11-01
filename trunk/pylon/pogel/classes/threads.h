#ifndef _THREADS_H
#define _THREADS_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define		THREADTYPE		void*
#define		THREADARGS		void*

#include "../../threads/threads.h"

namespace POGEL {
    class THREAD : public Threads::Thread
    {

    };
}

#endif /* _THREADS_H */

