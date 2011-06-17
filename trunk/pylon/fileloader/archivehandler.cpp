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

        void addArchiveLink(std::string archiveAlias, std::string archiveFileName)
        {
            archiveList += new archiveLink(archiveAlias, archiveFileName);
            //archiveList += new archiveLink(archiveFileName, archiveFileName);

            CLASSLIST<std::string> * filesinar = FileLoader::filesList(archiveFileName);
            if(filesinar == NULL)
            {
                return;
            }
            if(!filesinar->length())
            {
                delete filesinar;
                return;
            }

            for(unsigned int i = 0; i < filesinar->length(); i++)
                addFileLink(filesinar->get(i), archiveFileName);

            delete filesinar;
        }

        void addFileLink(std::string fileName, std::string archiveFileName)
        {
            fileList += new fileLink(archiveFileName, fileName);
        }
    }
}
