#include "timer.h"

namespace Renderer
{
    Timer::Timer()
    {
        lastDuration = curentDuration = POGEL::GetTimePassed();
        FPS = 1;
    }

    Timer::Timer(unsigned int fps)
    {
        lastDuration = curentDuration = POGEL::GetTimePassed();
        FPS = fps;
    }

    Timer::~Timer()
    {

    }

    void Timer::sleep()
    {
        curentDuration = POGEL::GetTimePassed();
        if(1.0 / double(curentDuration - lastDuration) > double(FPS))
            usleep( (1000000/FPS) - (curentDuration - lastDuration) );
        else if(curentDuration == lastDuration)
            usleep(1000000/FPS);
        //else cout << "Warning: cyclerate to slow." << endl;
        lastDuration = POGEL::GetTimePassed();
    }

    void Timer::step()
    {
        this->sleep();
    }
}
