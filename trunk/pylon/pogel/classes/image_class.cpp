#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include "image_class.h"

#ifdef OPENGL
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "../templates/templates.h"

#include "../../soil/SOIL.h"

CLASSLIST<POGEL::IMAGE*> imageList;

POGEL::IMAGE* NullImage = (POGEL::IMAGE*)NULL;

unsigned int POGEL::imglstlen()
{
    return imageList.length();
}

POGEL::IMAGE* POGEL::lstimg(unsigned int i)
{
    return imageList[i];
}

POGEL::IMAGE* POGEL::getNullImage()
{
    return NullImage;
}

void POGEL::setNullImage(std::string img)
{
    NullImage = POGEL::requestImage(img);
}

unsigned int POGEL::addImage(POGEL::IMAGE* img)
{
    imageList += img;
    return imageList.length()-1;
}

POGEL::IMAGE* POGEL::requestImage(std::string s)
{
    if(
        s.length() == 0 ||
        s.compare("{IMAGE_NULL}") == 0 ||
        s.compare("{image_null}") == 0 ||
        s.compare("{NULL}") == 0 ||
        s.compare("{null}") == 0
    )
    {
        return POGEL::getNullImage();
    }
    POGEL::IMAGE* tmp = new POGEL::IMAGE(s,false);
    for(unsigned int i = 0; i < imageList.length(); i++)
    {
        if(tmp->compare(imageList[i]))
        {
            delete tmp;
            return imageList[i];
        }
    }
    delete tmp;
    cout << "new Image: " << s << endl;
    imageList.add(new POGEL::IMAGE(s,true));
    return imageList.last();
}

POGEL::IMAGE::IMAGE()
{
    data=(char*)NULL;
    base=(unsigned int)NULL;
    tstr = fileid = "";
    sizeX = sizeY = 0;
    channels = 0;
    setfilter(IMAGE_LINEAR);
}

POGEL::IMAGE::IMAGE(const char *filename)
{
    loadandbuild(filename);
}

POGEL::IMAGE::IMAGE(const char *filename, int filter)
{
    setfilter(filter);
    loadandbuild(filename);
}

void get_things(std::string s, std::string *name, unsigned int *x, unsigned int *y, int* filter)
{
    /* acceptable formats:
     * "{filename}"
     * "{[filename]}"
     * "{[filename],[filternum]}"
     * "{[filename],[sizex],[sizey],[filternum]}"
     */
    if(POGEL::getOccurrencesInString(',',s) == 0)
    {
        if(POGEL::getOccurrencesInString('[',s) == 1 && POGEL::getOccurrencesInString(']',s) == 1)
            *name = POGEL::getStringSection('[',1,false,']',1,false, s);
        else if(POGEL::getOccurrencesInString('{',s) == 1 && POGEL::getOccurrencesInString('}',s) == 1)
        {
            *name = POGEL::getStringSection('{',1,false,'}',1,false, s);
            get_things(s,name,x,y,filter);
        }
        else
            *name = s;
    }
    else if(POGEL::getOccurrencesInString(',',s) == 1)
    {
        std::string filename = POGEL::getStringSection('[',1,false,']',1,false, s);
        sscanf(s.c_str(),std::string("{["+filename+"],[%d]}").c_str(), filter);
        *name = filename;
    }
    else
    {
        std::string filename = POGEL::getStringSection('[',1,false,']',1,false, s);
        sscanf(s.c_str(),std::string("{["+filename+"],[%u],[%u],[%d]}").c_str(), x, y, filter);
        *name = filename;
    }
}

POGEL::IMAGE::IMAGE(std::string s)
{
    tstr = s;
    fileid = POGEL::getStringSection('[',1,false,']',1,false, s);
    unsigned int x, y;
    int filter=0;
    std::string fileid="";
    get_things(s,&fileid,&x,&y,&filter);
    setfilter(filter);
    std::ifstream ifs ( fileid.c_str(), std::ifstream::in );
    bool ret = ifs.good();
    ifs.close();
    if(ret)
    {
        load(fileid.c_str());
    }
    else
    {
        data = NULL;
    }
    base = (unsigned int) NULL;
}

POGEL::IMAGE::IMAGE(std::string s,bool bob)
{
    tstr = s;
    fileid = POGEL::getStringSection('[',1,false,']',1,false, s);
    unsigned int x, y;
    int filter=0;
    std::string fileid="";
    get_things(s,&fileid,&x,&y,&filter);
    setfilter(filter);
    std::ifstream ifs ( fileid.c_str(), std::ifstream::in );
    bool ret = ifs.good();
    ifs.close();
    if(ret && bob)
    {
        load(fileid.c_str());
    }
    else
    {
        data = NULL;
    }
    base = (unsigned int) NULL;
}

POGEL::IMAGE::~IMAGE()
{
    if(data != NULL)
    {
        free(data);
        data = NULL;
    }
    base=(unsigned int)NULL;
}

int POGEL::IMAGE::load(const char *filename)
{
    int sizex, sizey, ch;
    data = (char*)SOIL_load_image(filename, &sizex, &sizey, &ch, SOIL_LOAD_AUTO);
    sizeX = (unsigned long)sizex;
    sizeY = (unsigned long)sizey;
    channels = (unsigned short int)ch;
    cout << "file: " << filename << " has " << ch << " color channels" << endl;
    fileid = std::string(filename);
    if(data)
    {
        return true;
    }
    cout << SOIL_last_result() << endl;
    return false;
}

unsigned int POGEL::IMAGE::build()
{
    #ifdef OPENGL
    switch(getfilter()) {
        default:
        case IMAGE_NEAREST:
            base = SOIL_create_OGL_texture((const unsigned char*)data, sizeX, sizeY, channels, base, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_POWER_OF_TWO );
        break;
        case IMAGE_LINEAR:
            base = SOIL_create_OGL_texture((const unsigned char*)data, sizeX, sizeY, channels, base, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_LINEAR );
        break;
        case IMAGE_MIPMAP:
            base = SOIL_create_OGL_texture((const unsigned char*)data, sizeX, sizeY, channels, base, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS );
        break;
    }
    #endif
    return base;
}

bool POGEL::IMAGE::isbuilt()
{
    return base != (unsigned int)NULL;
}

bool POGEL::IMAGE::isloaded()
{
    return data != NULL;
}

unsigned int POGEL::IMAGE::loadandbuild(const char *filename)
{
    load(filename);
    return build();
}

unsigned int POGEL::IMAGE::loadandbuild()
{
    if(data==NULL)
    {
        load(getFileID().c_str());
    }
    return build();
}

unsigned int POGEL::IMAGE::getbase()
{
    return base;
}

void POGEL::IMAGE::set()
{
    #ifdef OPENGL
        glBindTexture(GL_TEXTURE_2D, getbase());
    #endif
}

unsigned long POGEL::IMAGE::getheight()
{
    return sizeY;
}

unsigned long POGEL::IMAGE::getwidth()
{
    return sizeX;
}

void POGEL::IMAGE::setfilter(int t)
{
    filtertype = t;
}

int POGEL::IMAGE::getfilter()
{
    return filtertype;
}

unsigned int POGEL::IMAGE::numchannels()
{
    return (unsigned int)(channels);
}

std::string POGEL::IMAGE::getFileID()
{
    return fileid;
}

std::string POGEL::IMAGE::toString()
{
    if(tstr.length())
    {
        return tstr;
    }
    char *szx = POGEL::string("%u",sizeX);
    char *szy = POGEL::string("%u",sizeY);
    char *sft = POGEL::string("%d",filtertype);
    std::string s =  "{";
    s += "[" + fileid + "],";
    s += "[" + std::string(szx) + "],";
    s += "[" + std::string(szy) + "],";
    s += "[" + std::string(sft) + "]}";
    free(szx);
    free(szy);
    free(sft);
    return s;
}

bool POGEL::IMAGE::operator == (POGEL::IMAGE other)
{
    unsigned int x1=0, y1=0;
    int filter1 = 0;
    std::string name1="";
    unsigned int x2=0, y2=0;
    int filter2 = 0;
    std::string name2="";
    get_things(this->toString(),&name1,&x1,&y1,&filter1);
    get_things(other.toString(),&name2,&x2,&y2,&filter2);
    return x1==x2 && y1==y2 && filter1==filter2 && name1.compare(name2)==0;
}

bool POGEL::IMAGE::compare(POGEL::IMAGE *other)
{
    unsigned int x1=0, y1=0;
    int filter1 = 0;
    std::string name1="";
    unsigned int x2=0, y2=0;
    int filter2 = 0;
    std::string name2="";
    get_things(this->toString(),&name1,&x1,&y1,&filter1);
    get_things(other->toString(),&name2,&x2,&y2,&filter2);
    return x1==x2 && y1==y2 && filter1==filter2 && name1.compare(name2)==0;
}

bool POGEL::IMAGE::isClear()
{
    return numchannels() == 2 || numchannels() == 4;
}
