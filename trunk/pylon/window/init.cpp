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
        while( ++i < 6 && exret != 0 )
        {
            exret = FileLoader::extractfile( pylon_archive, ininames[i], true, false, "", false, "" );
            if( exret == 0 )
            {
                ininame = ininames[i];
                break;
            }
            else if( exret < 0 )
            {
                if( FileLoader::checkfile(ininames[i]) )
                {
                    ininame = ininames[i];
                    break;
                }
            }
        }
        FileLoader::Ini ini(ininame);
        if( !Main::dontremove )
            FileLoader::System::Files::remove( ininame );

        Main::main_py = ini.getvalue("pylon", "main");
        Main::init_py = ini.getvalue("pylon", "init");
        Main::ext_dir = ini.getvalue("pylon", "extractiondir");

        FileLoader::extractfile(pylon_archive, main_py, true, false, ext_dir, false, "");
        FileLoader::extractfile(pylon_archive, init_py, true, false, ext_dir, false, "");

        std::string winname = ini.getvalue("window", "name");
        if( winname.length() )
        {
            std::string n = winname;
            if( POGEL::hasproperty(POGEL_DEBUG) )
                n = "Pylon."+VersionString+": '"+winname+"' in "+(!forcedir?"archive: '"+pylon_archive:"folder: '"+forced_dir)+"'";
            Renderer::Window::Create(n);
        }
        else
            Renderer::Window::Create("Pylon." + VersionString);


        // add the main archive to the archive linkage system
        FileLoader::ArchiveHandler::addArchiveLink("{main}", pylon_archive);

        // extract all the pylon files in the main archive
        ClassList<std::string> * tmpinternalarchivelist = FileLoader::ArchiveHandler::getAllFilesOfType(".pylon");
        if( tmpinternalarchivelist )
        {
            FileLoader::ArchiveHandler::extractKnownFiles(*tmpinternalarchivelist);
            delete tmpinternalarchivelist;
        }

        if( ini.hasSection("archives") )
        {
            ClassList<std::string> * keynames = ini.keysinsection("archives");
            if( keynames && keynames->length() )
            {
                for( unsigned int i = 0; i < keynames->length(); i++ )
                {
                    std::string key = keynames->get(i);
                    std::string alias = "{" + key + "}";
                    std::string value = ini.getvalue("archives", key);
                    FileLoader::ArchiveHandler::addArchiveLink(alias, value);
                }
            }
            if( keynames )
                delete keynames;
        }

        if( ini.hasSection("code") )
        {
            ClassList<std::string> codetypes;
            if( ini.hasSection("codetypes") )
            {
                ClassList<std::string> * keynames = ini.keysinsection("codetypes");
                if( keynames && keynames->length() )
                {
                    for( unsigned int i = 0; i < keynames->length(); i++ )
                    {
                        std::string key = keynames->get(i);
                        std::string value = ini.getvalue("codetypes", key);
                        if( !value.compare("true") || !value.compare("True") || !value.compare("TRUE") )
                            codetypes += key;
                    }
                }
                if( keynames )
                    delete keynames;
            }

            std::string codeDir = ini.getvalue("code", "dir");
            std::string codeExtract = ini.getvalue("code", "extract");
            bool doCodeExtract = false;
            if( !codeExtract.compare("true") || !codeExtract.compare("True") || !codeExtract.compare("TRUE") )
                doCodeExtract = true;
            //std::string codeExclude = ini.getvalue("code", "exclude");

            ClassList<std::string> * filesInCodeDir = FileLoader::ArchiveHandler::getAllFilesInDir(codeDir);

            if( filesInCodeDir )
            {
                if( codetypes.length() )
                {
                    for(unsigned int i = 0; i < codetypes.length(); i++)
                    {
                        ClassList<std::string> * tfiles = FileLoader::ArchiveHandler::getFilesOfType(codetypes[i], filesInCodeDir);
                        if( tfiles && tfiles->length() )
                            FileLoader::ArchiveHandler::codeFiles += tfiles;
                        if( tfiles )
                            delete tfiles;
                    }
                }
                else
                {
                    FileLoader::ArchiveHandler::codeFiles += filesInCodeDir;
                }

                for(unsigned int i = 0; i < FileLoader::ArchiveHandler::codeFiles.length(); i++)
                {
                    if( !FileLoader::ArchiveHandler::codeFiles[i].compare(Main::main_py) || !FileLoader::ArchiveHandler::codeFiles[i].compare(Main::init_py) )
                        FileLoader::ArchiveHandler::codeFiles -= i--;
                }

                if( doCodeExtract )
                    FileLoader::ArchiveHandler::extractKnownFiles(FileLoader::ArchiveHandler::codeFiles);

                filesInCodeDir->safeclear();
                delete filesInCodeDir;
            }
        }


    }


}
