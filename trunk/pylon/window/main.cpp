#include "main.h"

#include "version.h"

#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../pogel/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../fileloader/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../scriptengine/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../renderer/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../threads/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../pogelscriptinterface/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING
#include "../objectloader/version.h"
#undef RC_FILEVERSION
#undef RC_FILEVERSION_STRING

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

std::string VersionStringNoOS = std::string(AutoVersion::_FULLVERSION_STRING) + std::string(AutoVersion::_STATUS_SHORT);

#if defined(WINDOWS) || defined(_WIN32)
    #if defined(_WIN64)
        std::string VersionString = VersionStringNoOS + "_win64";
    #else
        std::string VersionString = VersionStringNoOS + "_win32";
    #endif
#elif defined(APPLE) || defined(_APPLE)
std::string VersionString = VersionStringNoOS + "_mac";
#elif defined(LINUX) || defined(_LINUX) || defined(linux)
std::string VersionString = VersionStringNoOS + "_linux";
#elif defined(UNIX) || defined(_UNIX) || defined(unix)
std::string VersionString = VersionStringNoOS + "_unix";
#else
std::string VersionString = VersionStringNoOS + "_other";
#endif

void printVersion()
{
    cout << "Pylon_" << VersionString << endl;
    cout << "  Pogel_" << std::string(PogelAutoVersion::FULLVERSION_STRING) + " " + std::string(PogelAutoVersion::STATUS) << endl;
    cout << "  FileLoader_" << std::string(FileLoaderAutoVersion::FULLVERSION_STRING) + " " + std::string(FileLoaderAutoVersion::STATUS) << endl;
    cout << "  ScriptEngine_" << std::string(ScriptEngineAutoVersion::FULLVERSION_STRING) + " " + std::string(ScriptEngineAutoVersion::STATUS) << endl;
    cout << "  Renderer_" << std::string(RendererAutoVersion::FULLVERSION_STRING) + " " + std::string(RendererAutoVersion::STATUS) << endl;
    cout << "  Threads_" << std::string(ThreadsAutoVersion::FULLVERSION_STRING) + " " + std::string(ThreadsAutoVersion::STATUS) << endl;
    cout << "  pogelInterface_" << std::string(pogelInterfaceAutoVersion::FULLVERSION_STRING) + " " + std::string(pogelInterfaceAutoVersion::STATUS) << endl;
    cout << "  ObjectLoader_" << std::string(ObjectLoaderAutoVersion::FULLVERSION_STRING) + " " + std::string(ObjectLoaderAutoVersion::STATUS) << endl;
    cout << "Created by: Dean Tarpey" << endl;
    cout << "http://pylon.googlecode.com/" << endl;
}

bool calcLock = false;

Thread *calcThread;
Thread *scriptThread;

int main(int argc, char *argv[])
{
    #ifdef PYLON_DEBUG_VERSION
    VersionString += "_debug";
    #endif

    Renderer::CMD::get(argc, argv);

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
        else
        if(curarg.compare("-version") == 0)
        {
            printVersion();
            exit(0);
        }
    }

    FileLoader::__ar_extract_init(noarchiving,dontremove,forcedir,forced_dir);

    if(forcedir)
    #ifdef _WIN32
        _chdir(forced_dir.c_str());
    #else
        { int ret = chdir(forced_dir.c_str()); ret = 0; }
    #endif

    if(POGEL::hasproperty(POGEL_DEBUG))
        printVersion();

    std::string ojdat = ObjectLoader::getobjectformfile("Platonic 0","C3dObjectPlatonic","Data/Default.wld");
    std::string bob = ScriptEngine::Parse::getLabeledSection(ojdat,"CAnimKeyFrame","{<",">}");
    ObjectLoader::AnimKeyFrame key(bob);

    //std::cout << key.toString() << std::endl;

    //cout << key.toString() << endl;

    FileLoader::extractfile(pylon_archive,".conf",true,false,"",false,"");
    FileLoader::Ini ini(".conf");
    if(!dontremove)
    #ifdef _WIN32
        system("del /Q .conf");
    #else
        { int ret = system("rm .conf"); ret = 0; }
    #endif

    main_py = ini.getvalue("pylon","main");
    init_py = ini.getvalue("pylon","init");
    ext_dir = ini.getvalue("pylon","extractiondir");

    FileLoader::extractfile(pylon_archive,main_py,true,false,ext_dir,false,"");
    FileLoader::extractfile(pylon_archive,init_py,true,false,ext_dir,false,"");

    std::string winname = ini.getvalue("window","name");
    if(winname.length())
    {
        std::string n = "";
        if(POGEL::hasproperty(POGEL_DEBUG))
            n = "Pylon_" + VersionString + ": '"+winname+"' in " + (!forcedir?"archive: '" + pylon_archive:"folder: '" + forced_dir) + "'";
        else
            n = winname;
        Renderer::Window::Create(n);
    }
    else
        Renderer::Window::Create("Pylon_" + VersionString);
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
