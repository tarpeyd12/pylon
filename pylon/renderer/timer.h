#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

//#ifndef RENDERER_H_INCLUDED
//#include "renderer.h"
//#endif // RENDERER_H_INCLUDED

#include <stdlib.h>
#include <unistd.h>

#include "../pogel/pogel.h"

namespace Renderer
{
    namespace Timing
    {
        extern bool noTiming;

        class Timer
        {
            private:
                std::string timerName;
                float lastDuration;
                float curentDuration;
                unsigned int FPS;
            public:
                Timer();
                Timer(unsigned int fps);
                Timer(unsigned int fps, std::string name);
                ~Timer();

                void sleep();
                void step();
        };
    }
}

#endif // TIMER_H_INCLUDED
