#ifndef INI_H_INCLUDED
#define INI_H_INCLUDED

#ifndef FILELOADER_H_INCLUDED
#include "fileloader.h"
#endif // FILELOADER_H_INCLUDED

#ifndef INCLUDED_SimpleIni_h
#define SI_SUPPORT_IOSTREAMS
#include "simpleini/SimpleIni.h"
#endif

namespace FileLoader
{
    class Ini
    {
        private:
            std::string filename;
            CSimpleIniA ini;
        public:
            Ini(std::string);
            Ini(const Ini&);
            virtual ~Ini();

            std::string getvalue(std::string,std::string);
            bool hasSection(std::string);
            ClassList<std::string> * keysinsection(std::string);
    };
}

#endif // INI_H_INCLUDED
