#include "main.h"

#include "calcthread.h"

CalcThread::CalcThread()
{
    this->startThread();
}

CalcThread::~CalcThread()
{
    Main::calcLock = true;
    this->joinThread();
    Main::calcLock = false;
}

void CalcThread::run()
{
    Renderer::Timing::Timer *timer = new Renderer::Timing::Timer(25, "Physics");
    while(!Main::calcLock)
    {
        timer->sleep();
        Renderer::Incriment();
    }
    delete timer;
}
