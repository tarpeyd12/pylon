#include "timer.h"

//#define TIMER_OVERRIDE 12

namespace Renderer
{
    namespace Timing
    {

        bool noTiming = false;

        Timer::Timer()
        {
            lastDuration = curentDuration = POGEL::GetTimePassed();
            lastStepTime = 0.0f;
            #ifdef TIMER_OVERRIDE
            FPS = TIMER_OVERRIDE;
            #else
            FPS = 1;
            #endif
            timerName = "TimerWithFPSof1";
            totalTime = 0.0f;
            steps = 0;
            overflow = 0.0;
        }

        Timer::Timer(double fps)
        {
            lastDuration = curentDuration = POGEL::GetTimePassed();
            #ifdef TIMER_OVERRIDE
            FPS = TIMER_OVERRIDE;
            #else
            FPS = fps;
            #endif
            lastStepTime = 0.0f;
            char * tmp = POGEL::string("%d",fps);
            timerName = std::string(tmp);
            delete [] tmp;
            totalTime = 0.0f;
            steps = 0;
            overflow = 0.0;
        }

        Timer::Timer(double fps, std::string name)
        {
            lastDuration = curentDuration = POGEL::GetTimePassed();
            #ifdef TIMER_OVERRIDE
            FPS = TIMER_OVERRIDE;
            #else
            FPS = fps;
            #endif
            lastStepTime = 0.0f;
            timerName = name;
            totalTime = 0.0f;
            steps = 0;
            overflow = 0.0;
        }

        Timer::~Timer()
        {

        }

        double Timer::getLastStepTime()
        {
            return lastStepTime;
        }

        double Timer::getFPS()
        {
            return FPS;
        }

        void Timer::Sleep()
        {
            curentDuration = POGEL::GetTimePassed();
            if(!Renderer::Timing::noTiming)
            {
                double durationDifference = curentDuration - lastDuration;
                double invDurDiff = 1.0 / durationDifference;
                /*if(steps%10 == 0)
                {
                    totalTime = 0.0f;
                    steps = 0;
                }*/
                //totalTime += durationDifference;
                lastStepTime = durationDifference;
                double waitTime = 1000000.0 / FPS;
                if ( invDurDiff >= FPS )
                {
                    double diffTime = waitTime - durationDifference*1000000.0;
                    unsigned int sltime = (unsigned int)( diffTime );
                    double timeerr = diffTime - double(sltime);
                    overflow += timeerr;
                    //cout << overflow << endl;
                    if( usleep( sltime + (unsigned int)overflow ) )
                    {
                        cout << "usleep() error" << endl;
                    }
                    overflow -= double((unsigned int)(overflow));
                    if( overflow < 0.0 )
                    {
                        overflow = 0.0;
                    }
                }
                else
                if ( curentDuration <= lastDuration )
                {
                    usleep( (unsigned int)waitTime );
                }
                /*else
                if ( steps == 9 && isfinite(invDurDiff) && invDurDiff > 0.0f && (unsigned int)(invDurDiff) < FPS-1 )
                {
                    cout << "Warning: cyclerate to slow for timer: \"";
                    cout <<  timerName;
                    cout << "\" @ \t" << FPS << " : ";
                    char* tmp = POGEL::string("%0.1f", invDurDiff);
                    cout << tmp << endl;
                    delete[] tmp;
                }*/
                lastDuration = POGEL::GetTimePassed();
            }
            else
            {
                lastDuration = curentDuration;
            }
        }

        void Timer::step()
        {
            this->Sleep();
        }
    }
}
