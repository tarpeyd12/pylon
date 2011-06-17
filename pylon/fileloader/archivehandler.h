#ifndef ARCHIVEHANDLER_H_INCLUDED
#define ARCHIVEHANDLER_H_INCLUDED

#ifndef FILELOADER_H_INCLUDED
#include "fileloader.h"
#endif // FILELOADER_H_INCLUDED

namespace FileLoader
{
    namespace ArchiveHandler
    {
        class archiveLink
        {
            private:
                std::string name;
                std::string file;
            public:
                archiveLink(std::string arName, std::string f);
                virtual ~archiveLink();

                std::string getArchiveName();
                std::string getFileName();
                void setArchiveName(std::string);
                void setFileName(std::string);
        };

        typedef archiveLink fileLink;

        extern CLASSLIST<archiveLink*> archiveList;
        extern CLASSLIST<fileLink*> fileList;

        void addArchiveLink(std::string,std::string);
        void addFileLink(std::string,std::string);
        int extractKnownFile(std::string);
    }
}

#endif // ARCHIVEHANDLER_H_INCLUDED
