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

void printHelp()
{
    cout << "Ussage:" << endl;
    std::string cmds = "[args]";
    #if defined(WINDOWS) || defined(_WIN32)
    cout << "  pylon.exe " + cmds << endl;
    #else
    cout << "  ./pylon " + cmds << endl;
    #endif
    cout << "  args:" << endl;
    cout << "    -f [filename]            forces the archive to filename" << endl;
    cout << "    -dir [directory]         forces the search directory" << endl;
    #if defined(PYLON_DEBUG_VERSION) || defined(PYLON_DEV_VERSION)
    cout << "    -usedirdata              uses the data in the directory specified by -dir instead of the pylon archive file" << endl;
    cout << "    -dnrm                    forces no-removal of data temporaries" << endl;
    cout << "    -usedir [directory]      sets -dir with directory, -dnrm and -usedirdata" << endl;
    #endif
    cout << "    -version                 prints the versions" << endl;
    cout << "    ?                        this help menu" << endl;
    cout << endl;
}

bool calcLock = false;

Thread *calcThread;
Thread *scriptThread;

int main(int argc, char *argv[])
{
    #if defined(PYLON_DEBUG_VERSION)
    VersionString += "_debug";
    #endif
    #if defined(PYLON_DEV_VERSION)
    VersionString += "_dev";
    #endif

    Renderer::CMD::get(argc, argv);

    pylon_archive = "rc.pylon";

    for(int i = 0; i < argc; i++)
    {
        std::string curarg(argv[i]);
        if(curarg.compare("-f") == 0)
        {
            i++;
            pylon_archive = std::string(argv[i]);
            continue;
        }
        #if defined(PYLON_DEBUG_VERSION) || defined(PYLON_DEV_VERSION)
        else
        if(curarg.compare("-dnrm") == 0)
        {
            dontremove = true;
            continue;
        }
        #endif
        else
        if(curarg.compare("-forcedir") == 0 || curarg.compare("-dir") == 0)
        {
            forcedir = true;
            forced_dir = std::string(argv[++i]);
            continue;
        }
        #if defined(PYLON_DEBUG_VERSION) || defined(PYLON_DEV_VERSION)
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
        #endif
        else
        if(
            curarg.compare("-version") == 0 ||
            curarg.compare("?") == 0 ||
            curarg.compare("help") == 0 ||
            curarg.compare("-help") == 0 ||
            curarg.compare("-about") == 0
        )
        {
            printVersion();
            cout << endl;
            if(curarg.compare("?") == 0 || curarg.compare("help") == 0 || curarg.compare("-help") == 0)
                printHelp();
            exit(0);
        }
        else { }
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

    //std::string ojdat = ObjectLoader::getobjectformfile("Platonic 0","C3dObjectPlatonic","Data/Default.wld");
    //std::string bob = ScriptEngine::Parse::getLabeledSection(ojdat,"CAnimKeyFrame","{<",">}");
    //ObjectLoader::AnimKeyFrame key(bob);

    //std::cout << key.toString() << std::endl;

    //cout << key.toString() << endl;

    int exret = -1, i = -1;
    std::string ininames[] = {
        ".conf",
        "conf.ini",
        ".config",
        "config.ini",
        "conf.txt",
        "config.txt"
    };
    std::string ininame = "conf.ini";
    while(i++ < 6 && exret != 0)
    {
        exret = FileLoader::extractfile(pylon_archive,ininames[i],true,false,"",false,"");
        if(exret == 0)
            ininame = ininames[i];
        else if(exret == -1234)
        {
            ininame = ininames[0];
            break;
        }
    }
    FileLoader::Ini ini(ininame);
    if(!dontremove)
    #ifdef _WIN32
        system((std::string("del /Q ") + ininame).c_str());
    #else
        { int ret = system((std::string("rm ") + ininame).c_str()); ret = 0; }
    #endif

    main_py = ini.getvalue("pylon","main");
    init_py = ini.getvalue("pylon","init");
    ext_dir = ini.getvalue("pylon","extractiondir");

    FileLoader::extractfile(pylon_archive,main_py,true,false,ext_dir,false,"");
    FileLoader::extractfile(pylon_archive,init_py,true,false,ext_dir,false,"");

    std::string winname = ini.getvalue("window","name");
    if(winname.length())
    {
        std::string n = winname;
        if(POGEL::hasproperty(POGEL_DEBUG))
            n = "Pylon_"+VersionString+": '"+winname+"' in "+(!forcedir?"archive: '"+pylon_archive:"folder: '"+forced_dir)+"'";
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
