#include "main.h"

#include "calcthread.h"

CalcThread::CalcThread()
{
    this->startThread();
}

CalcThread::~CalcThread()
{

}

void CalcThread::run()
{
    float lastdur = POGEL::GetTimePassed();
    while(!Main::calcLock)
    {
        Renderer::Incriment();

        float curdur = POGEL::GetTimePassed();
        if(1/(curdur-lastdur) > 15)
            usleep(1000000/15-(curdur - lastdur));
        else if(curdur == lastdur)
            usleep(1000000/15);
        lastdur = POGEL::GetTimePassed();

    }
}
