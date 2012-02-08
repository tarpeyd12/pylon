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
            archiveList += new archiveLink(archiveAlias, archiveFileName);
            //archiveList += new archiveLink(archiveFileName, archiveFileName);

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

            for(unsigned int i = 0; i < filesInArchive->length(); i++)
            {
                addFileLink(filesInArchive->get(i), archiveFileName);
            }

            sortFileLinksByFile();

            delete filesInArchive;
        }

        void addFileLink(std::string fileName, std::string archiveFileName)
        {
            fileList += new fileLink(archiveFileName, fileName);
        }

        int extractKnownFile(std::string fn)
        {
            if(FileLoader::noarchive)
                return -1234;
            FileLoader::ArchiveHandler::fileLink ** fLink = NULL;
            FileLoader::ArchiveHandler::fileLink * frLink = new FileLoader::ArchiveHandler::fileLink("",fn);
            fLink = FileLoader::ArchiveHandler::fileList.search( frLink );
            if(  fLink  == NULL) return -1; // not found
            if((*fLink) == NULL) return -2; // found but corrupted
            delete frLink;
            return FileLoader::extractfile( (*fLink)->getArchiveName(), fn);
        }

        int extractKnownFiles(ClassList<std::string> list)
        {
            if(FileLoader::noarchive)
                return -1234;
            for(unsigned int i = 0; i < list.length(); i++)
                if( extractKnownFile(list[i]) )
                    throw int(i);
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
