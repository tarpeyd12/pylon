#include "main.h"

void* Calculations(void* arg)
{
    float lastdur = POGEL::GetTimePassed();
    while(!calcLock)
    {
        //POGEL::IncrementFps();
        //POGEL::PrintFps();
        //usleep(1000);
        Renderer::Incriment();

        float curdur = POGEL::GetTimePassed();
        if(1/(curdur-lastdur) > 15)
            usleep(1000000/15-(curdur - lastdur));
        else if(curdur == lastdur)
            usleep(1000000/15);
        //cout << 1/(curdur-lastdur) << endl;
        lastdur = POGEL::GetTimePassed();

    }
    pthread_exit(NULL);
    return NULL;
};
