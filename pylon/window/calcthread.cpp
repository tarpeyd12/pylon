#include "main.h"

#include "calcthread.h"

CalcThread::CalcThread()
{
    this->startThread();
    //if(Threads::getNumCores() > 1) this->setAffinity(0);
}

CalcThread::~CalcThread()
{
    Main::calcLock = true;
    //Renderer::Physics::StopIncrimentation();
    try
    {
        this->cancelThread();
    }
    catch(int e)
    {
        cout << "Unable to Cancel the Physics Thread. err:" << e << endl;
    }

    try
    {
        this->joinThread();
    }
    catch(int e)
    {
        cout << "Unable to Join the Physics Thread. err:" << e << endl;
    }

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
