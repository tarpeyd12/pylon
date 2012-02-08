#ifndef ARCHIVEHANDLER_H_INCLUDED
#define ARCHIVEHANDLER_H_INCLUDED

#ifndef FILELOADER_H_INCLUDED
#include "fileloader.h"
#endif // FILELOADER_H_INCLUDED

namespace FileLoader
{
    namespace ArchiveHandler
    {
        /// \class archiveLink
        /// \brief aliases for pylon archive files
        ///
        /// is ment to make accessing archive files in the python scripts faster.
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

        extern ClassList<archiveLink*> archiveList;
        extern ClassList<fileLink*> fileList;

        extern ClassList<std::string> codeFiles;

        void addArchiveLink(std::string,std::string);
        void addFileLink(std::string,std::string);

        void sortFileLinksByFile();
        void sortFileLinksByLink();

        int extractKnownFile(std::string);
        int extractKnownFiles(ClassList<std::string>);

        ClassList<std::string> * getAllFilesOfType(std::string);
        ClassList<std::string> * getAllFilesInDir(std::string);

        ClassList<std::string> * getFilesOfType(std::string, ClassList<std::string>*);
        ClassList<std::string> * getFilesInDir(std::string, ClassList<std::string>);
    }
}

#endif // ARCHIVEHANDLER_H_INCLUDED
