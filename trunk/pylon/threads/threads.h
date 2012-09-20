#ifndef THREADS_H_INCLUDED
#define THREADS_H_INCLUDED

#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include "thread.h"
#include "exthread.h"
#include "mutex.h"

namespace Threads
{
    int getNumCores();
}

#endif // THREADS_H_INCLUDED
