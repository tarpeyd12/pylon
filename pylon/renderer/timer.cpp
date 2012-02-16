#include "timer.h"

namespace Renderer
{
    namespace Timing
    {

        bool noTiming = false;

        Timer::Timer()
        {
            lastDuration = curentDuration = POGEL::GetTimePassed();
            lastStepTime = 0.0f;
            FPS = 1;
            timerName = "TimerWithFPSof1";
            totalTime = 0.0f;
            steps = 0;
        }

        Timer::Timer(unsigned int fps)
        {
            lastDuration = curentDuration = POGEL::GetTimePassed();
            FPS = fps;
            lastStepTime = 0.0f;
            char* tmp = POGEL::string("%d",fps);
            timerName = std::string(tmp);
            delete tmp;
            totalTime = 0.0f;
            steps = 0;
        }

        Timer::Timer(unsigned int fps, std::string name)
        {
            lastDuration = curentDuration = POGEL::GetTimePassed();
            FPS = fps;
            lastStepTime = 0.0f;
            timerName = name;
            totalTime = 0.0f;
            steps = 0;
        }

        Timer::~Timer()
        {

        }

        float Timer::getLastStepTime()
        {
            return lastStepTime;
        }

        unsigned int Timer::getFPS()
        {
            return FPS;
        }

        void Timer::sleep()
        {
            curentDuration = POGEL::GetTimePassed();
            if(!Renderer::Timing::noTiming)
            {
                float durationDifference = curentDuration - lastDuration;
                float invDurDiff = 1.0f / durationDifference;
                if(steps%10 == 0)
                {
                    totalTime = 0.0f;
                    steps = 0;
                }
                totalTime += durationDifference;
                lastStepTime = totalTime/float(++steps);
                float waitTime = 1000000.0f / float(FPS);
                if ( invDurDiff >= float(FPS) )
                {
                    usleep( (unsigned int)( waitTime - durationDifference*1000000.0f ) );
                }
                else
                if ( curentDuration <= lastDuration )
                {
                    usleep( (unsigned int)waitTime );
                }
                //else
                if ( isfinite(invDurDiff) && invDurDiff > 0.0f && (unsigned int)(invDurDiff) < FPS-1 )
                {
                    cout << "Warning: cyclerate to slow for timer: \"";
                    cout <<  timerName;
                    cout << "\" @ \t" << FPS << " : ";
                    char* tmp = POGEL::string("%0.1f", invDurDiff);
                    cout << std::string(tmp) << endl;
                    delete[] tmp;
                }
            }
            lastDuration = curentDuration;
        }

        void Timer::step()
        {
            this->sleep();
        }
    }
}
