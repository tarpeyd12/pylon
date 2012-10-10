#ifndef _IMAGE_CLASS_H
#define _IMAGE_CLASS_H

namespace POGEL
{
    class IMAGE;
}

//#include "view_class.h"

#include "../pogel_internals.h"

#define             IMAGE_NEAREST           0
#define             IMAGE_LINEAR            1
#define             IMAGE_MIPMAP            2
#define             IMAGE_MIPMAP2           3

//#define             IMAGE_DEFAULT_FILTER    IMAGE_MIPMAP
#define             IMAGE_DEFAULT_FILTER    IMAGE_MIPMAP2
//#define             IMAGE_DEFAULT_FILTER    IMAGE_NEAREST
//#define             IMAGE_DEFAULT_FILTER    IMAGE_LINEAR

namespace POGEL
{

    POGEL::IMAGE* getNullImage();
    void setNullImage(std::string);

    unsigned int addImage(POGEL::IMAGE*);
    POGEL::IMAGE* requestImage(std::string);
    unsigned int imglstlen();
    POGEL::IMAGE* lstimg(unsigned int);

    class IMAGE {
        protected:
            /* properties */
            std::string fileid;
            std::string tstr;
            int filtertype;
            char *data; // the bytes of data in the pixels
            unsigned short int channels; // the number of bytes per pixel
            unsigned int base; // the opengl texture identification number
        public:
            unsigned long sizeX;
            unsigned long sizeY;

            /* constructors */
            IMAGE();
            IMAGE(const char*);
            IMAGE(const char*,int);
            IMAGE(std::string);
            IMAGE(std::string,bool);

            /* deconstructor */
            ~IMAGE();

            /* methods */
            int load(const char*);
            virtual unsigned int build();
            virtual bool isbuilt();
            bool isloaded();
            unsigned int loadandbuild(const char*);
            unsigned int loadandbuild();
            unsigned int getbase();
            void set();
            unsigned long getheight();
            unsigned long getwidth();
            void setfilter(int t);
            int getfilter();

            unsigned int numchannels();

            std::string getFileID();

            std::string toString() const;

            bool operator == (const POGEL::IMAGE&);
            bool compare(POGEL::IMAGE*);

            bool isClear();
    };
}

#endif /* _IMAGE_CLASS_H */
