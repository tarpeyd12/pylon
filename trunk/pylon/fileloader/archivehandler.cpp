#include "archivehandler.h"

namespace FileLoader
{
    namespace ArchiveHandler
    {
        CLASSLIST<archiveLink*> archiveList;
        CLASSLIST<fileLink*> fileList;

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

            CLASSLIST<std::string> * filesInArchive = FileLoader::filesList(archiveFileName);
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
            FileLoader::ArchiveHandler::fileLink ** fLink = NULL;
            FileLoader::ArchiveHandler::fileLink * frLink = new FileLoader::ArchiveHandler::fileLink("",fn);
            fLink = FileLoader::ArchiveHandler::fileList.search( frLink );
            if(  fLink  == NULL) return -1; // not found
            if((*fLink) == NULL) return -2; // found but corrupted
            delete frLink;
            return FileLoader::extractfile( (*fLink)->getArchiveName(), fn);
        }
    }
}
