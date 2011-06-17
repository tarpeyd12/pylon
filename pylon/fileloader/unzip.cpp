#include "unzip_backend.h"

namespace FileLoader
{
    bool noremoval;
    bool noarchive;
    bool forcedir;
    std::string forced_dir;

    void __ar_extract_init(bool noar, bool nrm, bool fdir, std::string dir)
    {
        noarchive = noar;
        forced_dir = dir;
        noremoval = nrm;
        forcedir = fdir;
    }

    unzFile __openArchive(std::string ar)
    {
        #ifdef USEWIN32IOAPI
        zlib_filefunc64_def ffunc;
        fill_win32_filefunc64A(&ffunc);
        return unzOpen2_64((const char*)ar.c_str(),&ffunc);
        #else
        return unzOpen64((const char*)ar.c_str());
        #endif
    }

    unzFile __initArchive(std::string ar)
    {
        unzFile uf = NULL;
        if (ar.length())
        {
            uf = __openArchive(ar);

            if (uf == NULL)
            {
                uf = __openArchive(ar+".zip");
            }

            if (uf == NULL)
            {
                uf = __openArchive(ar+".pylon");
            }

            if (uf == NULL)
            {
                uf = __openArchive(ar+".pylon.zip");
            }
        }

        if (uf == NULL)
        {
            cout << "Unable to open " + ar + ", " + ar + ".zip, " + ar + ".pylon, nor " + ar + ".pylon.zip" << endl;
            __closeArchive(uf);
            //return NULL;
        }

        return uf;
    }

    void __closeArchive(unzFile uf)
    {
        unzClose(uf);
    }

    int extractfile(std::string ar, std::string fn)
    {
        return extractfile(ar,fn,true,false,"",false,"");
    }

    int extractfile(std::string ar, std::string fn, bool overite, bool bdirto, std::string dirto, bool bpw, std::string pw)
    {
        if(noarchive)
            return -1234;
        int ret_value = 0;
        unzFile uf = NULL;

        uf = __initArchive(ar);
        if(uf == NULL)
        {
            return 1;
        }

        #ifdef _WIN32
        char *curdur = _getcwd(NULL,2048);
        if (bdirto && _chdir((const char*)(dirto).c_str()))
        #else
        char *curdur = get_current_dir_name();
        if (bdirto && chdir((const char*)(dirto).c_str()))
        #endif
        {
            printf("Error changing into %s, aborting\n", (const char*)(dirto).c_str());
            exit(-1);
        }

        if (!fn.length())
            ret_value = do_extract(uf, 0, (int)overite, (bpw?(const char*)pw.c_str():NULL));
        else
            ret_value = do_extract_onefile(uf, (const char*)fn.c_str(), 0, (int)overite, (bpw?(const char*)pw.c_str():NULL));

        #ifdef _WIN32
        _chdir(curdur);
        free(curdur);
        #else
        int ret = chdir(curdur); ret = 0;
        free(curdur);
        #endif

        return ret_value;
    }

    CLASSLIST<std::string>* filesList(std::string ar)
    {
        //if(noarchive)
            //return NULL;

        unzFile uf = __initArchive(ar);
        if(uf == NULL)
            return NULL;

        uLong i;
        unz_global_info64 gi;
        int err;

        err = unzGetGlobalInfo64(uf,&gi);
        if (err!=UNZ_OK)
        {
            printf("error %d with zipfile in unzGetGlobalInfo \n",err);
        }

        CLASSLIST<std::string> * ret = new CLASSLIST<std::string>();

        for (i=0; i<gi.number_entry; i++)
        {
            char filename_inzip[256];
            unz_file_info64 file_info;
            err = unzGetCurrentFileInfo64(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
            if (err!=UNZ_OK)
            {
                printf("error %d with zipfile in unzGetCurrentFileInfo\n",err);
                break;
            }

            if ((i+1)<gi.number_entry)
            {
                err = unzGoToNextFile(uf);
                if (err!=UNZ_OK)
                {
                    printf("error %d with zipfile in unzGoToNextFile\n",err);
                    break;
                }
            }

            ret->add(std::string(filename_inzip));
        }
        __closeArchive(uf);
        return ret;
    }
}
