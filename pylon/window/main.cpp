#include "main.h"

/* Program entry point */

std::string pylon_archive;

std::string config_data;
std::string init_py;
std::string main_py;
std::string ext_dir;
bool dontremove = false;
bool forcedir = false;
bool noarchiving = false;
std::string forced_dir = "";


bool calcLock = false;

Thread *calcThread;
Thread *scriptThread;

int main(int argc, char *argv[])
{
    pylon_archive = "resources.pylon";

    for(int i = 0; i < argc; i++)
    {
        std::string curarg(argv[i]);
        if(curarg.compare("-f") == 0)
        {
            i++;
            pylon_archive = std::string(argv[i]);
            continue;
        }
        else
        if(curarg.compare("-dnrm") == 0)
        {
            dontremove = true;
            continue;
        }
        else
        if(curarg.compare("-forcedir") == 0 || curarg.compare("-dir") == 0)
        {
            forcedir = true;
            forced_dir = std::string(argv[++i]);
            continue;
        }
        else
        if(curarg.compare("-usedirdata") == 0)
        {
            noarchiving = true;
            dontremove = true;
            continue;
        }
        else
        if(curarg.compare("-usedir") == 0)
        {
            forced_dir = std::string(argv[++i]);
            forcedir = true;
            noarchiving = true;
            dontremove = true;
            continue;
        }
    }

    FileLoader::__ar_extract_init(noarchiving,dontremove,forcedir,forced_dir);

    if(forcedir)
    #ifdef _WIN32
        _chdir(forced_dir.c_str());
    #else
        chdir(forced_dir.c_str());
    #endif

    std::string ojdat = ObjectLoader::getobjectformfile("Platonic 0","C3dObjectPlatonic","Data/Default.wld");
    std::string bob = ScriptEngine::Parse::getLabeledSection(ojdat,"CKeyFrame","{<",">}");
    ObjectLoader::KeyFrame key(bob);

    FileLoader::extractfile(pylon_archive,".conf",true,false,"",false,"");
    FileLoader::Ini ini(".conf");
    if(!dontremove)
    #ifdef _WIN32
        system("del /Q .conf");
    #else
        system("rm .conf");
    #endif

    main_py = ini.getvalue("pylon","main");
    init_py = ini.getvalue("pylon","init");
    ext_dir = ini.getvalue("pylon","extractiondir");

    FileLoader::extractfile(pylon_archive,main_py,true,false,ext_dir,false,"");
    FileLoader::extractfile(pylon_archive,init_py,true,false,ext_dir,false,"");

    Renderer::CMD::get(argc, argv);
    std::string winname = ini.getvalue("window","name");
    if(winname.length())
        Renderer::Window::Create(winname);
    else
        Renderer::Window::Create();
    Renderer::Init();

    scriptThread = new Thread(Scripts);
    scriptThread->setData((void*)true);
    scriptThread->startThread();
    scriptThread->joinThread();

    scriptThread->setData((void*)false);
    scriptThread->startThread();

    calcThread = new Thread(Calculations);
    calcThread->startThread();

    glutMainLoop();

    return EXIT_SUCCESS;
}
