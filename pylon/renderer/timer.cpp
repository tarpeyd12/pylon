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
                double durationDifference = (curentDuration - lastDuration);
                if( (1.0 / durationDifference) >= double(FPS) )
                    usleep( (1000000/FPS) - (unsigned int)(durationDifference) );
                else if(curentDuration <= lastDuration)
                    usleep(1000000/FPS);
                else
                {
                    cout << "Warning: cyclerate to slow for timer: \"";
                    cout <<  timerName;
                    cout << "\" @ \t" << FPS << " : ";
                    char* tmp = POGEL::string("%0.1lf",double(1.0/durationDifference));
                    cout << std::string(tmp) << endl;
                    delete tmp;
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
