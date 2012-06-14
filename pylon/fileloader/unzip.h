#ifndef UNZIP_H_INCLUDED
#define UNZIP_H_INCLUDED

#ifndef FILELOADER_H_INCLUDED
#include "fileloader.h"
#endif // FILELOADER_H_INCLUDED

#include "minizip/unzip.h"

namespace FileLoader
{
    extern bool noremoval;
    extern bool noarchive;
    extern bool forcedir;
    extern std::string forced_dir;

    void __ar_extract_init(bool noar, bool nrm, bool fdir, std::string dir);

    unzFile __openArchive(std::string ar);
    unzFile __initArchive(std::string);
    void __closeArchive(unzFile);

    int extractfile(std::string ar, std::string fn);
    int extractfileto(std::string ar, std::string fn, std::string dst);
    int extractfile(std::string ar, std::string fn, bool o, bool bdirto, std::string dirto, bool bpw, std::string pw);

    ClassList<std::string>* filesList(std::string ar);
}

#endif // UNZIP_H_INCLUDED
