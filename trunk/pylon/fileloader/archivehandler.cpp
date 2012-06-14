#include "archivehandler.h"

namespace FileLoader
{
    namespace ArchiveHandler
    {
        ClassList<archiveLink*> archiveList;
        ClassList<fileLink*> fileList;

        ClassList<std::string> codeFiles;

        archiveLink::archiveLink(std::string n, std::string f)
        {
            name = n;
            file = f;
        }

        archiveLink::~archiveLink()
        {

        }

        std::string archiveLink::getArchiveName()
        {
            return name;
        }

        std::string archiveLink::getFileName()
        {
            return file;
        }

        void archiveLink::setArchiveName(std::string a)
        {
            name = a;
        }

        void archiveLink::setFileName(std::string f)
        {
            file = f;
        }

        // *********

        int _sortFileLinksByFile(fileLink** a, fileLink** b)
        {
            return (*a)->getFileName().compare((*b)->getFileName());
        }

        int _sortFileLinksByLink(fileLink** a, fileLink** b)
        {
            return (*a)->getArchiveName().compare((*b)->getArchiveName());
        }

        void sortFileLinksByFile()
        {
            fileList.sort(_sortFileLinksByFile);
        }

        void sortFileLinksByLink()
        {
            fileList.sort(_sortFileLinksByLink);
        }

        void addArchiveLink(std::string archiveAlias, std::string archiveFileName)
        {

            for( unsigned int i = 0; i < archiveFileName.length(); ++i )
            {
                if( archiveFileName[ i ] == '\\' )
                {
                    archiveFileName[ i ] = '/';
                }
            }

            archiveList += new archiveLink(archiveAlias, archiveFileName);

            ClassList<std::string> * filesInArchive = FileLoader::filesList(archiveFileName);
            if(filesInArchive == NULL)
            {
                return;
            }
            if(!filesInArchive->length())
            {
                delete filesInArchive;
                return;
            }

            std::string location = "";
            if( archiveFileName.rfind('/') != std::string::npos )
            {
                location = archiveFileName.substr( 0, archiveFileName.rfind('/') );
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

            for(unsigned int i = 0; i < filesInArchive->length(); i++)
            {
                // set the direct file name
                std::string flnm = location+filesInArchive->get(i);

                // make a file link to the archive
                addFileLink( flnm, archiveFileName );
                //addFileLink( filesInArchive->get(i), archiveFileName );

                // is the curent file a pylon arhive
                unsigned int pos = flnm.rfind(".pylon");
                if( pos >= flnm.length() )
                {
                    continue;
                }
                std::string fExtension = flnm.substr(pos);
                if( fExtension.compare(".pylon") == 0 )
                {
                    // if it is a pylon archive
                    // see if it exists
                    if( !FileLoader::checkfile(flnm) )
                    {
                        // if not
                        // sort file list to search
                        sortFileLinksByFile();
                        // extract the archive file
                        FileLoader::ArchiveHandler::extractKnownFile(flnm);
                    }
                    // add the file as an archive and add its contents to the file cache
                    addArchiveLink( flnm, flnm );
                }
            }

            // sort the file list
            sortFileLinksByFile();

            // clean up
            delete filesInArchive;
        }

        void addFileLink(std::string fileName, std::string archiveFileName)
        {
            fileList += new fileLink(archiveFileName, fileName);
            //cout << fileName << endl;
        }

        bool isKnownFile( std::string filename )
        {
            if(FileLoader::noarchive)
                return true;

            for( unsigned int c = 0; c < filename.length(); ++c )
            {
                if( filename[ c ] == '\\' )
                {
                    filename[ c ] == '/';
                }
            }

            if( filename[ 0 ] == '.' )
            {
                filename = filename.substr( 1 );
            }

            if( filename[ 0 ] == '/' )
            {
                filename = filename.substr( 1 );
            }

            for( unsigned int i = 0; i < fileList.length(); ++i )
            {
                std::string tmpfilename = fileList[ i ]->getFileName();
                for( unsigned int c = 0; c < tmpfilename.length(); ++c )
                {
                    if( tmpfilename[ c ] == '\\' )
                    {
                        tmpfilename[ c ] == '/';
                    }
                }

                if( tmpfilename[ 0 ] == '.' )
                {
                    tmpfilename = tmpfilename.substr( 1 );
                }

                if( tmpfilename[ 0 ] == '/' )
                {
                    tmpfilename = tmpfilename.substr( 1 );
                }

                if( tmpfilename.compare(filename) == 0 )
                {
                    return true;
                }
            }
            return false;
        }

        int extractKnownFile(std::string fn)
        {
            // if not using an archive
            if(FileLoader::noarchive)
            {
                // return simple code
                return -1234;
            }

            // find the file link object
            FileLoader::ArchiveHandler::fileLink ** fLink = NULL;
            FileLoader::ArchiveHandler::fileLink * frLink = new FileLoader::ArchiveHandler::fileLink("",fn);
            fLink = FileLoader::ArchiveHandler::fileList.search( frLink );
            if(  fLink  == NULL) return -1; // not found
            if((*fLink) == NULL) return -2; // found but corrupted
            delete frLink;

            // extract the file from its archive
            int ret = FileLoader::extractfile( (*fLink)->getArchiveName(), fn);

            // check for failure
            if( ret && ret != -1234 )
            {
                // get the location of the requested files' archive
                std::string location = "";
                if( (*fLink)->getArchiveName().rfind('/') != std::string::npos )
                {
                    location = (*fLink)->getArchiveName().substr( 0, (*fLink)->getArchiveName().rfind('/') );
                }
                if( location.length() && location[ location.length()-1 ] != '/' )
                {
                    location = location + "/";
                }
                //cout << (*fLink)->getArchiveName() << " " << fn.substr(location.length()) << endl;

                // extract the file as it apears in the archive to the sabe directory as the containing archive
                ret = FileLoader::extractfileto( (*fLink)->getArchiveName(), fn.substr(location.length()), location );

                // see if that workd
                if( ret && ret != -1234 )
                {
                    // if not check to see if the archive that the file resides in exists
                    if( !FileLoader::checkfile( (*fLink)->getArchiveName() ) )
                    {
                        // if not try to extract the archive file
                        ret = extractKnownFile( (*fLink)->getArchiveName() );

                        // check to see if that worked
                        if( ret && ret != -1234 )
                        {
                            // if not see if we dont even hav the archive listed
                            if( isKnownFile( (*fLink)->getArchiveName() ) )
                            {
                                // if we do know about it, there is a problem
                                cout << "ERROR: could not retreive archive \"" << (*fLink)->getArchiveName() << "\" for file \"" << fn << "\"" << endl;
                                return -3;
                            }
                            else
                            {
                                // if not give up
                                return -4;
                            }
                        }
                    }
                    // try with the extraction to directory again
                    ret = FileLoader::extractfileto( (*fLink)->getArchiveName(), fn.substr(location.length()), location );
                }
            }
            return ret;
        }

        int extractKnownFiles(ClassList<std::string> list)
        {
            if(FileLoader::noarchive)
            {
                return -1234;
            }
            for( unsigned int i = 0; i < list.length(); ++i )
            {
                int ret = extractKnownFile( list[ i ] );
                if( ret && ret != -1234 )
                {
                    throw int(ret);
                    //return ret;
                }
            }
            return 0;
        }

        ClassList<std::string> * getAllFilesOfType(std::string ft)
        {
            if( FileLoader::noarchive )
                return new ClassList<std::string>(); // empty list
            if( ft.length() == 0 )
                return NULL; // null for when the file extension is empty
            if( ft[0] != '.' )
                ft =  "." + ft;
            ClassList<std::string> * fList = new ClassList<std::string>();
            FileLoader::ArchiveHandler::fileLink * pfLink = NULL;
            unsigned int length = FileLoader::ArchiveHandler::fileList.length();
            for(unsigned int i = 0; i < length; i++)
            {
                pfLink = FileLoader::ArchiveHandler::fileList[i];
                std::string fName = pfLink->getFileName();
                unsigned int pos = fName.rfind(ft);
                if( pos >= fName.length() )
                    continue;
                std::string fExtension = fName.substr(pos);
                if( fExtension.compare(ft) == 0 )
                    fList->add(std::string(fName));
            }
            return fList;
        }

        ClassList<std::string> * getAllFilesInDir(std::string dir)
        {
            if( FileLoader::noarchive )
                return new ClassList<std::string>(); // empty list
            if( dir.length() == 0 )
                return NULL; // null for when the dir name is empty
            ClassList<std::string> * fList = new ClassList<std::string>();
            FileLoader::ArchiveHandler::fileLink * pfLink = NULL;
            unsigned int length = FileLoader::ArchiveHandler::fileList.length();
            for(unsigned int i = 0; i < length; i++)
            {
                pfLink = FileLoader::ArchiveHandler::fileList[i];
                std::string fName = pfLink->getFileName();
                if( fName.compare(0, dir.length(), dir) == 0 )
                    fList->add(std::string(fName));
            }
            return fList;
        }

        ClassList<std::string> * getFilesOfType(std::string ft, ClassList<std::string> * list)
        {
             if( FileLoader::noarchive || list->length() == 0 )
                return new ClassList<std::string>(); // empty list
            if( ft.length() == 0 )
                return NULL; // null for when the file extension is empty
            if( ft[0] != '.' )
                ft =  "." + ft;
            ClassList<std::string> * fList = new ClassList<std::string>();
            unsigned int length = list->length();
            for(unsigned int i = 0; i < length; i++)
            {
                std::string fName = list->get(i);
                unsigned int pos = fName.rfind(ft);
                if( pos >= fName.length() )
                    continue;
                std::string fExtension = fName.substr(pos);
                if( fExtension.compare(ft) == 0 )
                    fList->add(std::string(fName));
            }
            return fList;
        }

        ClassList<std::string> * getFilesInDir(std::string dir, ClassList<std::string> * list)
        {
            if( FileLoader::noarchive || list->length() == 0 )
                return new ClassList<std::string>(); // empty list
            if( dir.length() == 0 )
                return NULL; // null for when the dir name is empty
            ClassList<std::string> * fList = new ClassList<std::string>();
            unsigned int length = list->length();
            for(unsigned int i = 0; i < length; i++)
            {
                std::string fName = list->get(i);
                if( fName.compare(0, dir.length(), dir) == 0 )
                    fList->add(std::string(fName));
            }
            return fList;
        }


    }
}
