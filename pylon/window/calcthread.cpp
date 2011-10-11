#include "main.h"

#include "calcthread.h"

CalcThread::CalcThread()
{
    this->startThread();
}

CalcThread::~CalcThread()
{
    this->joinThread();
}

void CalcThread::run()
{
    Renderer::Timing::Timer *timer15 = new Renderer::Timing::Timer(25, "Physics"); // 15 cycles per second
    while(!Main::calcLock)
    {
        Renderer::Incriment();
        timer15->sleep();
    }
    delete timer15;
}
