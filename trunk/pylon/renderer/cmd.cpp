#include "cmd.h"

namespace Renderer
{
    namespace CMD
    {

        int argumentCount;
        char **argumentList;

        void get(int argc, char *argv[])
        {
            Renderer::CMD::argumentCount = argc;
            Renderer::CMD::argumentList = argv;

            glutInit(&Renderer::CMD::argumentCount, Renderer::CMD::argumentList);

            POGEL::getcmd(Renderer::CMD::argumentCount, Renderer::CMD::argumentList);
        }
    }
}
