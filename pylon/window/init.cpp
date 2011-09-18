#include "main.h"

namespace Main
{
    void Init()
    {
        int exret = -1, i = -1;
        std::string ininames[] = {
            "conf.ini",
            ".conf",
            ".config",
            "config.ini",
            "conf.txt",
            "config.txt"
        };
        std::string ininame = "conf.ini";
        // i starts as -1 so this while loop is ok
        while(++i < 6 && exret != 0)
        {
            exret = FileLoader::extractfile(pylon_archive,ininames[i],true,false,"",false,"");
            if(exret == 0)
            {
                ininame = ininames[i];
                break;
            }
            else if(exret < 0)
            {
                if(FileLoader::checkfile(ininames[i]))
                {
                    ininame = ininames[i];
                    break;
                }
            }
        }
        FileLoader::Ini ini(ininame);
        if(!Main::dontremove)
            FileLoader::System::Files::remove(ininame);

        Main::main_py = ini.getvalue("pylon","main");
        Main::init_py = ini.getvalue("pylon","init");
        Main::ext_dir = ini.getvalue("pylon","extractiondir");

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

        if(ini.hasSection("archives"))
        {
            CLASSLIST<std::string> * keynames = ini.keysinsection("archives");
            if(keynames && keynames->length())
            {
                for(unsigned int i = 0; i < keynames->length(); i++)
                {
                    std::string key = keynames->get(i);
                    std::string alias = "{" + key + "}";
                    FileLoader::ArchiveHandler::addArchiveLink(alias, ini.getvalue("archives",key));
                }
            }
            if(keynames)
                delete keynames;
        }

        FileLoader::ArchiveHandler::addArchiveLink("{main}",pylon_archive);
    }
}
