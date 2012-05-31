#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

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
                double lastDuration;
                double curentDuration;
                double lastStepTime;
                double totalTime;
                double overflow;
                unsigned int steps;
                double FPS;
            public:
                Timer();
                Timer(double fps);
                Timer(double fps, std::string name);
                ~Timer();

                double getLastStepTime();
                double getFPS();

                void Sleep();
                void step();
        };
    }
}

#endif // TIMER_H_INCLUDED
