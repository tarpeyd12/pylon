#include "main.h"

#include "calcthread.h"

CalcThread::CalcThread()
{
    this->startThread();
    //this->setAffinity(0);
}

CalcThread::~CalcThread()
{
    Main::calcLock = true;
    Renderer::Physics::StopIncrimentation();
    this->joinThread();
    Main::calcLock = false;
}

void CalcThread::run()
{
    Renderer::Timing::Timer *timer = new Renderer::Timing::Timer(25, "Physics");
    while(!Main::calcLock)
    {
        timer->sleep();
        Renderer::Physics::Incriment();
    }
    delete timer;
}
