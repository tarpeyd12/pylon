#include "system.h"

namespace FileLoader
{
    namespace System
    {
        namespace Dir
        {

            int changeDir( std::string dir )
            {
                if( !dir.length() )
                {
                    return -1;
                }

                int ret = 0;
                #if defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)

                    for( unsigned int i = 0; i < dir.length(); ++i )
                    {
                        if( dir[ i ] == '/' )
                        {
                            dir[ i ] = '\\';
                        }
                    }

                    ret = _chdir( dir.c_str() );
                #else
                    ret = chdir( dir.c_str() );
                #endif
                return ret;
            }

            int makeDir( std::string dir )
            {
                return 0;
            }

            int removeDir( std::string dir )
            {
                return 0;
            }

            int clearDir( std::string dir )
            {
                if( !dir.length() )
                {
                    std::cout << "Cannot remove files from directory: \"\"" << std::endl;
                    return -1;
                }

                int ret = 0;
                #if defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)

                    for( unsigned int i = 0; i < dir.length(); ++i )
                    {
                        if( dir[ i ] == '/' )
                        {
                            dir[ i ] = '\\';
                        }
                    }

                    std::cout << "Clearing all contentents of the directory \"" << dir << "\" ..." << std::endl;

                    ret = system( ("del /S /Q " + dir + "\\*.*").c_str() );
                #else

                    std::cout << "Clearing all contentents of the directory \"" << dir << "\" ..." << std::endl;

                    // this is unsafe, it cd's to the dir but only cd's up one dir instead of back to working dir.
                    //ret = system(("cd " + dir + " && rm --recursive * && cd ..").c_str());
                    // this one is safe ...
                    ret = system( ("rm --recursive "+dir+"/*").c_str() );
                #endif

                return ret;
            }

        }

        namespace Files
        {

            int remove(std::string fileName)
            {
                if( !fileName.length() )
                {
                    return -1;
                }

                int ret = 0;
                #if defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)

                    for( unsigned int i = 0; i < fileName.length(); ++i )
                    {
                        if( fileName[ i ] == '/' )
                        {
                            fileName[ i ] = '\\';
                        }
                    }

                    ret = system( ("del /Q " + fileName).c_str() );

                #else
                    ret = system( ("rm " + fileName).c_str() );
                #endif
                return ret;
            }

        }
    }
}
