// original header:

/*
   miniunz.c
   Version 1.1, February 14h, 2010
   sample part of the MiniZip project - ( http://www.winimage.com/zLibDll/minizip.html )

         Copyright (C) 1998-2010 Gilles Vollant (minizip) ( http://www.winimage.com/zLibDll/minizip.html )

         Modifications of Unzip for Zip64
         Copyright (C) 2007-2008 Even Rouault

         Modifications for Zip64 support on both zip and unzip
         Copyright (C) 2009-2010 Mathias Svensson ( http://result42.com )
*/

// modified by Dean Tarpey

#include "unzip.h"

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif



#ifndef _WIN32
#ifndef __USE_FILE_OFFSET64
#define __USE_FILE_OFFSET64
#endif
#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64
#endif
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#ifndef _FILE_OFFSET_BIT
#define _FILE_OFFSET_BIT 64
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#ifdef unix
# include <unistd.h>
# include <utime.h>
# include <sys/stat.h>
#else
# include <direct.h>
# include <io.h>
#endif

#include "minizip/unzip.h"

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)
#define MAXFILENAME (256)

#ifdef _WIN32
#define USEWIN32IOAPI
#include "minizip/iowin32.h"
#endif
/*
  mini unzip, demo of unzip package

  usage :
  Usage : miniunz [-exvlo] file.zip [file_to_extract] [-d extractdir]

  list the file in the zipfile, and print the content of FILE_ID.ZIP or README.TXT
    if it exists
*/


/* change_file_date : change the date/time of a file
    filename : the filename of the file where date/time must be modified
    dosdate : the new date at the MSDos format (4 bytes)
    tmu_date : the SAME new date at the tm_unz format */
void change_file_date(const char *filename, uLong dosdate, tm_unz tmu_date)
{
#ifdef _WIN32
    HANDLE hFile;
    FILETIME ftm,ftLocal,ftCreate,ftLastAcc,ftLastWrite;

    hFile = CreateFileA(filename,GENERIC_READ | GENERIC_WRITE,
                        0,NULL,OPEN_EXISTING,0,NULL);
    GetFileTime(hFile,&ftCreate,&ftLastAcc,&ftLastWrite);
    DosDateTimeToFileTime((WORD)(dosdate>>16),(WORD)dosdate,&ftLocal);
    LocalFileTimeToFileTime(&ftLocal,&ftm);
    SetFileTime(hFile,&ftm,&ftLastAcc,&ftm);
    CloseHandle(hFile);
#else
#ifdef unix
    struct utimbuf ut;
    struct tm newdate;
    newdate.tm_sec = tmu_date.tm_sec;
    newdate.tm_min=tmu_date.tm_min;
    newdate.tm_hour=tmu_date.tm_hour;
    newdate.tm_mday=tmu_date.tm_mday;
    newdate.tm_mon=tmu_date.tm_mon;
    if (tmu_date.tm_year > 1900)
        newdate.tm_year=tmu_date.tm_year - 1900;
    else
        newdate.tm_year=tmu_date.tm_year ;
    newdate.tm_isdst=-1;

    ut.actime=ut.modtime=mktime(&newdate);
    utime(filename,&ut);
#endif
#endif
}


/* mymkdir and change_file_date are not 100 % portable
   As I don't know well Unix, I wait feedback for the unix portion */

int mymkdir(const char* dirname)
{
    int ret=0;
#ifdef _WIN32
    ret = _mkdir(dirname);
#else
#ifdef unix
    ret = mkdir (dirname,0775);
#endif
#endif
    return ret;
}

int makedir (char *newdir)
{
    char *buffer ;
    char *p;
    int  len = (int)strlen(newdir);

    if (len <= 0)
        return 0;

    buffer = (char*)malloc(len+1);
    if (buffer==NULL)
    {
        printf("Error allocating memory\n");
        return UNZ_INTERNALERROR;
    }
    strcpy(buffer,newdir);

    if (buffer[len-1] == '/')
    {
        buffer[len-1] = '\0';
    }
    if (mymkdir(buffer) == 0)
    {
        free(buffer);
        return 1;
    }

    p = buffer+1;
    while (1)
    {
        char hold;

        while(*p && *p != '\\' && *p != '/')
            p++;
        hold = *p;
        *p = 0;
        if ((mymkdir(buffer) == -1) && (errno == ENOENT))
        {
            printf("couldn't create directory %s\n",buffer);
            free(buffer);
            return 0;
        }
        if (hold == 0)
            break;
        *p++ = hold;
    }
    free(buffer);
    return 1;
}

void Display64BitsSize(ZPOS64_T n, int size_char)
{
    /* to avoid compatibility problem , we do here the conversion */
    char number[21];
    int offset=19;
    int pos_string = 19;
    number[20]=0;
    for (;;)
    {
        number[offset]=(char)((n%10)+'0');
        if (number[offset] != '0')
            pos_string=offset;
        n/=10;
        if (offset==0)
            break;
        offset--;
    }
    {
        int size_display_string = 19-pos_string;
        while (size_char > size_display_string)
        {
            size_char--;
            printf(" ");
        }
    }

    printf("%s",&number[pos_string]);
}

int do_list(unzFile uf)
{
    uLong i;
    unz_global_info64 gi;
    int err;

    err = unzGetGlobalInfo64(uf,&gi);
    if (err!=UNZ_OK)
        printf("error %d with zipfile in unzGetGlobalInfo \n",err);
    printf("  Length  Method     Size Ratio   Date    Time   CRC-32     Name\n");
    printf("  ------  ------     ---- -----   ----    ----   ------     ----\n");
    for (i=0; i<gi.number_entry; i++)
    {
        char filename_inzip[256];
        unz_file_info64 file_info;
        uLong ratio=0;
        const char *string_method;
        char charCrypt=' ';
        err = unzGetCurrentFileInfo64(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
        if (err!=UNZ_OK)
        {
            printf("error %d with zipfile in unzGetCurrentFileInfo\n",err);
            break;
        }
        if (file_info.uncompressed_size>0)
            ratio = (uLong)((file_info.compressed_size*100)/file_info.uncompressed_size);

        /* display a '*' if the file is crypted */
        if ((file_info.flag & 1) != 0)
            charCrypt='*';

        if (file_info.compression_method==0)
            string_method="Stored";
        else if (file_info.compression_method==Z_DEFLATED)
        {
            uInt iLevel=(uInt)((file_info.flag & 0x6)/2);
            if (iLevel==0)
                string_method="Defl:N";
            else if (iLevel==1)
                string_method="Defl:X";
            else if ((iLevel==2) || (iLevel==3))
                string_method="Defl:F"; /* 2:fast , 3 : extra fast*/
        }
        else if (file_info.compression_method==Z_BZIP2ED)
        {
            string_method="BZip2 ";
        }
        else
            string_method="Unkn. ";

        Display64BitsSize(file_info.uncompressed_size,7);
        printf("  %6s%c",string_method,charCrypt);
        Display64BitsSize(file_info.compressed_size,7);
        printf(" %3lu%%  %2.2lu-%2.2lu-%2.2lu  %2.2lu:%2.2lu  %8.8lx   %s\n",
               ratio,
               (uLong)file_info.tmu_date.tm_mon + 1,
               (uLong)file_info.tmu_date.tm_mday,
               (uLong)file_info.tmu_date.tm_year % 100,
               (uLong)file_info.tmu_date.tm_hour,(uLong)file_info.tmu_date.tm_min,
               (uLong)file_info.crc,filename_inzip);
        if ((i+1)<gi.number_entry)
        {
            err = unzGoToNextFile(uf);
            if (err!=UNZ_OK)
            {
                printf("error %d with zipfile in unzGoToNextFile\n",err);
                break;
            }
        }
    }

    return 0;
}


int do_extract_currentfile(unzFile uf,  const int* popt_extract_without_path, int* popt_overwrite, const char* password)
{
    char filename_inzip[256];
    char* filename_withoutpath;
    char* p;
    int err=UNZ_OK;
    FILE *fout=NULL;
    void* buf;
    uInt size_buf;

    unz_file_info64 file_info;
    //uLong ratio=0;
    err = unzGetCurrentFileInfo64(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);

    if (err!=UNZ_OK)
    {
        printf("error %d with zipfile in unzGetCurrentFileInfo\n",err);
        return err;
    }

    size_buf = WRITEBUFFERSIZE;
    buf = (void*)malloc(size_buf);
    if (buf==NULL)
    {
        printf("Error allocating memory\n");
        return UNZ_INTERNALERROR;
    }

    p = filename_withoutpath = filename_inzip;
    while ((*p) != '\0')
    {
        if (((*p)=='/') || ((*p)=='\\'))
            filename_withoutpath = p+1;
        p++;
    }

    if ((*filename_withoutpath)=='\0')
    {
        if ((*popt_extract_without_path)==0)
        {
            //printf("creating directory: %s\n",filename_inzip);
            mymkdir(filename_inzip);
        }
    }
    else
    {
        const char* write_filename;
        int skip=0;

        if ((*popt_extract_without_path)==0)
            write_filename = filename_inzip;
        else
            write_filename = filename_withoutpath;

        err = unzOpenCurrentFilePassword(uf,password);
        if (err!=UNZ_OK)
        {
            printf("error %d with zipfile in unzOpenCurrentFilePassword\n",err);
        }

        if (((*popt_overwrite)==0) && (err==UNZ_OK))
        {
            char rep=0;
            FILE* ftestexist = NULL;
            ftestexist = fopen64(write_filename,"rb");
            if (ftestexist!=NULL)
            {
                fclose(ftestexist);
                do
                {
                    char answer[128];
                    int ret;

                    printf("The file %s exists. Overwrite ? [y]es, [n]o, [A]ll: ",write_filename);
                    ret = scanf("%1s",answer);
                    if (ret != 1)
                    {
                        exit(EXIT_FAILURE);
                    }
                    rep = answer[0] ;
                    if ((rep>='a') && (rep<='z'))
                        rep -= 0x20;
                }
                while ((rep!='Y') && (rep!='N') && (rep!='A'));
            }

            if (rep == 'N')
                skip = 1;

            if (rep == 'A')
                *popt_overwrite=1;
        }

        if ((skip==0) && (err==UNZ_OK))
        {
            fout=fopen64(write_filename,"wb");

            /* some zipfile don't contain directory alone before file */
            if ((fout==NULL) && ((*popt_extract_without_path)==0) &&
                    (filename_withoutpath!=(char*)filename_inzip))
            {
                char c=*(filename_withoutpath-1);
                *(filename_withoutpath-1)='\0';
                makedir((char*)write_filename);
                *(filename_withoutpath-1)=c;
                fout=fopen64(write_filename,"wb");
            }

            if (fout==NULL)
            {
                printf("error opening %s\n",write_filename);
            }
        }

        if (fout!=NULL)
        {
            //printf(" extracting: %s\n",write_filename);

            do
            {
                err = unzReadCurrentFile(uf,buf,size_buf);
                if (err<0)
                {
                    printf("error %d with zipfile in unzReadCurrentFile\n",err);
                    break;
                }
                if (err>0)
                    if (fwrite(buf,err,1,fout)!=1)
                    {
                        printf("error in writing extracted file\n");
                        err=UNZ_ERRNO;
                        break;
                    }
            }
            while (err>0);
            if (fout)
                fclose(fout);

            if (err==0)
                change_file_date(write_filename,file_info.dosDate,
                                 file_info.tmu_date);
        }

        if (err==UNZ_OK)
        {
            err = unzCloseCurrentFile (uf);
            if (err!=UNZ_OK)
            {
                printf("error %d with zipfile in unzCloseCurrentFile\n",err);
            }
        }
        else
            unzCloseCurrentFile(uf); /* don't lose the error */
    }

    free(buf);
    return err;
}


int do_extract(unzFile uf, int opt_extract_without_path, int opt_overwrite, const char* password)
{
    uLong i;
    unz_global_info64 gi;
    int err;
//    FILE* fout=NULL;

    err = unzGetGlobalInfo64(uf,&gi);
    if (err!=UNZ_OK)
        printf("error %d with zipfile in unzGetGlobalInfo \n",err);

    for (i=0; i<gi.number_entry; i++)
    {
        if (do_extract_currentfile(uf,&opt_extract_without_path,
                                   &opt_overwrite,
                                   password) != UNZ_OK)
            break;

        if ((i+1)<gi.number_entry)
        {
            err = unzGoToNextFile(uf);
            if (err!=UNZ_OK)
            {
                printf("error %d with zipfile in unzGoToNextFile\n",err);
                break;
            }
        }
    }

    return 0;
}

int do_extract_onefile(unzFile uf, const char* filename, int opt_extract_without_path, int opt_overwrite, const char* password)
{
//    int err = UNZ_OK;
    if (unzLocateFile(uf,filename,CASESENSITIVITY)!=UNZ_OK)
    {
        printf("file %s not found in the zipfile\n",filename);
        return 2;
    }

    if (do_extract_currentfile(uf,&opt_extract_without_path,
                               &opt_overwrite,
                               password) == UNZ_OK)
        return 0;
    else
        return 1;
}

#ifdef __cplusplus
}
#endif

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

    int extractfile(std::string ar, std::string fn)
    {
        return extractfile(ar,fn,true,false,"",false,"");
    }

    int extractfile(std::string ar, std::string fn, bool o, bool bdirto, std::string dirto, bool bpw, std::string pw)
    {
        if(noarchive)
            return -1234;
        const char *zipfilename=NULL;
        const char *filename_to_extract=NULL;
        const char *password=NULL;
        if(bpw)
            password = (const char*)pw.c_str();
        char filename_try[MAXFILENAME+16] = "";
//        int i;
        int ret_value = 0;
        int opt_do_list = 0;
        int opt_do_extract = 1;
        int opt_do_extract_withoutpath = 0;
        int opt_overwrite = (int)o;
        int opt_extractdir = (int)bdirto;
        const char *dirname = NULL;
        if(bdirto)
        {
            dirname = (const char*)(dirto).c_str();
        }
        unzFile uf = NULL;

        zipfilename = (const char*)ar.c_str();
        if(fn.length())
            filename_to_extract = (const char*)fn.c_str();
        else
            filename_to_extract = NULL;

        if (zipfilename != NULL)
        {

    #ifdef USEWIN32IOAPI
            zlib_filefunc64_def ffunc;
    #endif

            strncpy(filename_try, zipfilename,MAXFILENAME-1);
            /* strncpy doesnt append the trailing NULL, of the string is too long. */
            filename_try[ MAXFILENAME ] = '\0';
            std::string filenametry = std::string(filename_try);

    #ifdef USEWIN32IOAPI
            fill_win32_filefunc64A(&ffunc);
            uf = unzOpen2_64(zipfilename,&ffunc);
    #else
            uf = unzOpen64(zipfilename);
    #endif
            if (uf == NULL)
            {
    #ifdef USEWIN32IOAPI
                uf = unzOpen2_64((filenametry+".zip").c_str(),&ffunc);
    #else
                uf = unzOpen64((filenametry+".zip").c_str());
    #endif
            }

            if (uf == NULL)
            {
    #ifdef USEWIN32IOAPI
                uf = unzOpen2_64((filenametry+".pylon").c_str(),&ffunc);
    #else
                uf = unzOpen64((filenametry+".pylon").c_str());
    #endif
            }

            if (uf == NULL)
            {
    #ifdef USEWIN32IOAPI
                uf = unzOpen2_64((filenametry+".pylon.zip").c_str(),&ffunc);
    #else
                uf = unzOpen64((filenametry+".pylon.zip").c_str());
    #endif
            }
        }

        if (uf==NULL)
        {
            printf("Cannot open %s, %s.zip, %s.pylon nor %s.pylon.zip\n",zipfilename,zipfilename,zipfilename,zipfilename);
            unzClose(uf);
            return 1;
        }
        //printf("%s opened\n",filename_try);

        if (opt_do_list==1)
            ret_value = do_list(uf);
        else if (opt_do_extract==1)
        {
    #ifdef _WIN32
            char *curdur = _getcwd(NULL,2048);
            if (opt_extractdir && _chdir(dirname))
    #else
            char *curdur = get_current_dir_name();
            if (opt_extractdir && chdir(dirname))
    #endif
            {
                printf("Error changing into %s, aborting\n", dirname);
                exit(-1);
            }

            if (filename_to_extract == NULL)
                ret_value = do_extract(uf, opt_do_extract_withoutpath, opt_overwrite, password);
            else
                ret_value = do_extract_onefile(uf, filename_to_extract, opt_do_extract_withoutpath, opt_overwrite, password);

    #ifdef _WIN32
            _chdir(curdur);
            free(curdur);
    #else
            int ret = chdir(curdur); ret = 0;
            free(curdur);
    #endif
        }

        return ret_value;
    }
}