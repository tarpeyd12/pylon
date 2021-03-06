#include "timer.h"

#define TIMER_OVERRIDE 25

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

        inline void wait_f( double waittime )
        {
            if( waittime < 0.0 )
            {
                return;
            }
            if( waittime >= 1.0 )
            {
                #if defined(WINDOWS) || defined(_WIN32)
                Sleep( (unsigned int)( waittime ) );
                #else
                if( sleep( (unsigned int)( waittime ) ) )
                {
                    cout << "sleep() error" << endl;
                }
                #endif
                waittime -= double( (unsigned int)( waittime ) );
            }
            if( waittime <= 0.0 )
            {
                return;
            }
            if( usleep( (unsigned int)( waittime * 1000000.0 ) ) )
            {
                cout << "usleep() error" << endl;
            }
        }

        void Timer::Sleep()
        {
            curentDuration = POGEL::GetTimePassed();

            if( Renderer::Timing::noTiming )
            {
                lastDuration = curentDuration;
                return;
            }

            double durationDifference = curentDuration - lastDuration;
            //double invDurDiff = 1.0 / durationDifference;
            lastStepTime = durationDifference;


            double invfps = 1.0 / FPS;
            double wt = invfps - durationDifference;
            wait_f( wt );

            /*double waitTime = 1000000.0 / FPS;
            if ( invDurDiff >= FPS )
            {
                double diffTime = waitTime - durationDifference * 1000000.0;
                unsigned int sltime = (unsigned int)( diffTime );
                double timeerr = diffTime - double(sltime);
                overflow += timeerr;
                int sleeptime = sltime + int(overflow) - 100;
                if( usleep( (unsigned int)( sleeptime > 0 ? sleeptime : 0 ) ) )
                {
                    cout << "usleep() error" << endl;
                }
                overflow -= double( int( overflow ) );
                if( overflow > waitTime || overflow < 0.0 )
                {
                    overflow = 0.0;
                }
            }
            else
            if ( curentDuration <= lastDuration )
            {
                int sleeptime = int(waitTime) - 100;
                if( usleep( (unsigned int)( sleeptime > 0 ? sleeptime : 0 ) ) )
                {
                    cout << "usleep() error" << endl;
                }
            }*/
            //double prevdur = lastDuration;
            lastDuration = POGEL::GetTimePassed();

            //cout << flush << timerName << ": " << 1.0 / (lastDuration - prevdur) << endl;
        }

        void Timer::step()
        {
            this->Sleep();
        }
    }
}
