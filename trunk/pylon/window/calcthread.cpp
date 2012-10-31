#include "main.h"

#include "calcthread.h"

CalcThread::CalcThread()
{
    this->startThread();
    //if(Threads::getNumCores() > 1) this->setAffinity(0);
}

CalcThread::~CalcThread()
{
    Renderer::calcLockMutex.Lock();
    Main::calcLock = true;
    Renderer::HaltPhysics = true;
    Renderer::Physics::StopIncrimentation();
    usleep(1000);
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
    Renderer::calcLockMutex.Unlock();
}

void CalcThread::run()
{
    Renderer::Timing::Timer *timer = new Renderer::Timing::Timer(25, "Physics");
    while(!Main::calcLock)
    {
        if( !Renderer::HaltPhysics )
        {
            Renderer::Physics::Incriment(2);
        }
        timer->Sleep();
        POGEL::SetFramerateThrotle((timer->getLastStepTime()+1.0f/float(timer->getFPS()))/2.0f);
    }
    delete timer;
}
