#include "../scriptengine/scriptengine.h"

#include "objectloader.h"

namespace ObjectLoader
{
    namespace pylon
    {

        std::string VersionStringRaw;

        POGEL::OBJECT *
        newFromPylonZipFile( const char * cfilename, const char * objname, POGEL::OBJECT * object, const std::string& simname )
        {
            std::string filename(cfilename);
            for( unsigned int i = 0; i < filename.length(); ++i )
            {
                if( filename[ i ] == '\\' )
                {
                    filename[ i ] = '/';
                }
            }

            std::string location = "";
            if( filename.rfind('/') != std::string::npos )
            {
                location = filename.substr( 0, filename.rfind('/') );
            }

            if( location[ 0 ] == '.' )
            {
                location = location.substr( 1 );
            }

            if( location[ 0 ] == '/' )
            {
                location = location.substr( 1 );
            }

            if( location.length() && location[ location.length()-1 ] != '/' )
            {
                location = location + "/";
            }

            int r = FileLoader::ArchiveHandler::extractKnownFile( filename );

            if( r && r != -1234 )
            {
                cout << "nofile" << endl;
                return NULL;
            }

            ClassList<std::string> * filesinzip = FileLoader::filesList( filename );

            std::string ininames[] = {
                "conf.ini",
                ".conf",
                ".config",
                "config.ini",
                "conf.txt",
                "config.txt"
            };

            std::string ininame = "";

            for( unsigned int i = 0; i < 6; ++i )
            {
                for( unsigned int p = 0; p < filesinzip->length(); ++p )
                {
                    if( ininames[ i ].compare( filesinzip->get(p) ) == 0 )
                    {
                        ininame = ininames[ i ];
                        break;
                    }
                }
            }

            if( !ininame.length() )
            {
                delete filesinzip;
                cout << "noinilen" << endl;
                return NULL;
            }

            r = FileLoader::extractfileto( filename, ininame, location );

            if( r && r != -1234 )
            {
                delete filesinzip;
                cout << "noini" << endl;
                return NULL;
            }

            FileLoader::Ini ini(location+ininame);

            if( !FileLoader::noremoval )
            {
                FileLoader::System::Files::remove( location+ininame );
            }

            std::string pylon_type = ini.getvalue( "pylon", "type" );

            if( pylon_type.compare("object") != 0 )
            {
                delete filesinzip;
                cout << "wrongtype" << endl;
                return NULL;
            }

            std::string requiredVersion = ini.getvalue("pylon", "version");
            unsigned int ver1[4], ver2[4];
            sscanf(requiredVersion.c_str(), "%d.%d.%d.%d", &ver1[0], &ver1[1], &ver1[2], &ver1[3]);
            sscanf(VersionStringRaw.c_str(), "%d.%d.%d.%d", &ver2[0], &ver2[1], &ver2[2], &ver2[3]);
            for(unsigned int i = 0; i < 4; ++i)
            {
                if(ver1[i]>ver2[i])
                {
                    cout << "ERROR: cannot open pylon object archive." << endl;
                    cout << "Program version too low, you may need to update:" << endl;
                    cout << "\trequired version \"" << requiredVersion << "\"" << endl;
                    cout << "\tcurrent version \"" << VersionStringRaw << "\"" << endl;
                    return NULL;
                }
            }

            std::string main_py = ini.getvalue("pylon", "main");
            //std::string init_py = ini.getvalue("pylon", "init");
            std::string ext_dir = ini.getvalue("pylon", "extractiondir");

            std::string codeDir = "";

            if( ini.hasSection("code") )
            {
                ClassList<std::string> codetypes;
                if( ini.hasSection("codetypes") )
                {
                    ClassList<std::string> * keynames = ini.keysinsection("codetypes");
                    if( keynames && keynames->length() )
                    {
                        for( unsigned int i = 0; i < keynames->length(); ++i )
                        {
                            std::string key = keynames->get(i);
                            std::string value = ini.getvalue("codetypes", key);
                            if( !value.compare("true") || !value.compare("True") || !value.compare("TRUE") )
                            {
                                codetypes += key;
                            }
                        }
                    }
                    if( keynames )
                    {
                        delete keynames;
                    }
                }

                codeDir = ini.getvalue("code", "dir");
                std::string codeExtract = ini.getvalue("code", "extract");
                bool doCodeExtract = false;
                if( !codeExtract.compare("true") || !codeExtract.compare("True") || !codeExtract.compare("TRUE") )
                {
                    doCodeExtract = true;
                }
                //std::string codeExclude = ini.getvalue("code", "exclude");

                ClassList<std::string> * filesInCodeDir = FileLoader::ArchiveHandler::getFilesInDir(codeDir, filesinzip);

                ClassList<std::string> codeFiles;

                if( filesInCodeDir )
                {
                    if( codetypes.length() )
                    {
                        for(unsigned int i = 0; i < codetypes.length(); i++)
                        {
                            ClassList<std::string> * tfiles = FileLoader::ArchiveHandler::getFilesOfType(codetypes[i], filesInCodeDir);
                            if( tfiles && tfiles->length() )
                            {
                                codeFiles += tfiles;
                            }
                            if( tfiles )
                            {
                                delete tfiles;
                            }
                        }
                    }
                    else
                    {
                        codeFiles += filesInCodeDir;
                    }

                    /*for(unsigned int i = 0; i < codeFiles.length(); i++)
                    {
                        if( !FcodeFiles[i].compare(main_py) || !codeFiles[i].compare(init_py) )
                        {
                            codeFiles -= i--;
                        }
                    }*/

                    if( doCodeExtract )
                    {
                        for( unsigned int i = 0; i < codeFiles.length(); ++i )
                        {
                            r = FileLoader::extractfileto( filename, codeFiles[ i ], location );

                            if( r && r != -1234 )
                            {
                                cout << "badextract" << endl;
                                return NULL;
                            }
                            //FileLoader::ArchiveHandler::extractKnownFiles(codeFiles);
                        }
                    }

                    filesInCodeDir->safeclear();
                    delete filesInCodeDir;
                }
            }

            if( !object )
            {
                object = new POGEL::OBJECT( objname );
            }

            std::string objectnamespace = ini.getvalue("object", "namespace");

            ScriptEngine::Executor("sys.path.append('./" + location+codeDir + "')\n"/*"import " + objectnamespace + "\n"*/ ).Execute();

            std::string constructor = ini.getvalue("object", "constructor");

            std::string args[3] = { "str:"+simname, "str:"+std::string(objname), "str:"+location };
            ScriptEngine::FunctionCaller(objectnamespace,constructor,args,3).Execute();

            delete filesinzip;
            return object;
        }
    }
}
