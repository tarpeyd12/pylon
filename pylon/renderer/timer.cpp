#include "timer.h"

namespace Renderer
{
    namespace Timing
    {

        bool noTiming = false;

        Timer::Timer()
        {
            lastDuration = curentDuration = POGEL::GetTimePassed();
            FPS = 1;
            timerName = "TimerWithFPSof1";
        }

        Timer::Timer(unsigned int fps)
        {
            lastDuration = curentDuration = POGEL::GetTimePassed();
            FPS = fps;
            char* tmp = POGEL::string("%d",fps);
            timerName = std::string(tmp);
            delete tmp;
        }

        Timer::Timer(unsigned int fps, std::string name)
        {
            lastDuration = curentDuration = POGEL::GetTimePassed();
            FPS = fps;
            timerName = name;
        }

        Timer::~Timer()
        {

        }

        void Timer::sleep()
        {
            curentDuration = POGEL::GetTimePassed();
            if(!Renderer::Timing::noTiming)
            {
                double durationDifference = curentDuration - lastDuration;
                double invDurDiff = 1.0f / durationDifference;
                unsigned int waitTime = 1000000 / FPS;
                if( invDurDiff >= double(FPS) )
                {
                    usleep( waitTime - (unsigned int)(durationDifference) );
                }
                else if(curentDuration <= lastDuration)
                {
                    usleep( waitTime );
                }
                else if( (unsigned int)invDurDiff+1 < FPS )
                {
                    cout << "Warning: cyclerate to slow for timer: \"";
                    cout <<  timerName;
                    cout << "\" @ \t" << FPS << " : ";
                    char* tmp = POGEL::string("%0.1lf", invDurDiff);
                    cout << std::string(tmp) << endl;
                    delete[] tmp;
                }
            }
            lastDuration = POGEL::GetTimePassed();
        }

        void Timer::step()
        {
            this->sleep();
        }
    }
}
