#include <stdio.h>
#include <stdlib.h>
#include "image_class.h"
#ifdef OPENGL
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "../templates/templates.h"

#include "../../soil/SOIL.h"

CLASSLIST<POGEL::IMAGE*> imageList;

unsigned int POGEL::imglstlen() {
    return imageList.length();
};

POGEL::IMAGE* POGEL::lstimg(unsigned int i) {
    return imageList[i];
};

POGEL::IMAGE* POGEL::requestImage(std::string s) {
	if(s.length() == 0 || s.compare("{IMAGE_NULL}") == 0)
		return (POGEL::IMAGE*)NULL;
    if(POGEL::getOccurrencesInString(',',s) == 0) {
        if(s[0] == '[' || s[0] == '{') s = s.substr(1);
        if(s[0] == '[' || s[0] == '{') s = s.substr(1);
        if(s[s.length()-1] == ']' || s[s.length()-1] == '}') s = s.substr(0,s.length()-1);
        if(s[s.length()-1] == ']' || s[s.length()-1] == '}') s = s.substr(0,s.length()-1);
        for(unsigned int i = 0; i < imageList.length(); i++) {
            std::string sr = POGEL::getStringComponentLevel('[',false,']',false,imageList[i]->toString(),"0");
            if(s.compare(sr) == 0)
                return imageList[i];
        }
        imageList.add(new POGEL::IMAGE(s.c_str()));
        return imageList.last();
    }
    if(POGEL::getOccurrencesInString(',',s) == 1 || (POGEL::getOccurrencesInString('[',s) == 2 && POGEL::getOccurrencesInString(']',s) == 2)) {
        std::string imgname = POGEL::getStringComponentLevel('[',false,']',false,s,"0");
        std::string filter  = POGEL::getStringComponentLevel('[',false,']',false,s,"1");
        if(imgname[imgname.length()-1] == ']') imgname = imgname.substr(0,imgname.length()-1);
        if(filter[filter.length()-1] == ']') filter = filter.substr(0,filter.length()-1);
        int filtertype = 0; sscanf(filter.c_str(),"%d",&filtertype);
        for(unsigned int i = 0; i < imageList.length(); i++) {
            std::string cimg = imageList[i]->toString();
            std::string in = POGEL::getStringComponentLevel('[',false,']',false,cimg,"0");
            std::string fl = POGEL::getStringComponentLevel('[',false,']',false,cimg,"3");
            if(in[in.length()-1] == ']') in = in.substr(0,in.length()-1);
            if(fl[fl.length()-1] == ']') fl = fl.substr(0,fl.length()-1);
            //cout << "{[" << in << "],[" << fl << "]}" << endl << "{[" << imgname << "],[" << filter << "]}" << endl;
            if(imgname.compare(in) == 0 && filter.compare(fl) == 0)
                return imageList[i];
        }
        imageList.add(new POGEL::IMAGE("{["+imgname+"],[0],[0],["+filter+"]}"));
        return imageList.last();
    }
	for(unsigned int i = 0; i < imageList.length(); i++)
		if(s.compare(imageList[i]->toString()) == 0)
			return imageList[i];
	imageList.add(new POGEL::IMAGE(s));
	return imageList.last();
};

POGEL::IMAGE::IMAGE() {
	data=(char*)NULL;
	base=(unsigned int)NULL;
	fileid = "";
	sizeX = sizeY = 0;
	channels = 0;
	setfilter(IMAGE_LINEAR);
};

POGEL::IMAGE::IMAGE(const char *filename) {
	loadandbuild(filename);
};

POGEL::IMAGE::IMAGE(const char *filename, int filter) {
	setfilter(filter);
	loadandbuild(filename);
};

POGEL::IMAGE::IMAGE(std::string s) {
	std::string filename = POGEL::getStringSection('[',1,false,']',1,false, s);
	unsigned int x, y; int filter;
	sscanf(s.c_str(), std::string("{["+filename+"],[%u],[%u],[%d]}").c_str(), &x, &y, &filter);
	setfilter(filter); //loadandbuild(filename.c_str());
	load(filename.c_str());
	base = (unsigned int) NULL;
	/*bool inlist = false;
	for(unsigned int i = 0; i < imageList.length(); i++)
		if(imageList[i] == this) { inlist = true; break; }
	if(!inlist)
		imageList.add(this);*/
};

POGEL::IMAGE::~IMAGE() {
	delete[] data;
	base=(unsigned int)NULL;
};

int POGEL::IMAGE::load(const char *filename) {

    int sizex, sizey, ch;
    data = (char*)SOIL_load_image(filename, &sizex, &sizey, &ch, SOIL_LOAD_AUTO);
    sizeX = sizex; sizeY = sizey; channels = ch;
    fileid = filename;
    if(data)
        return true;
    else
        return false;
};

unsigned int POGEL::IMAGE::build() {
	#ifdef OPENGL
    switch(getfilter()) {
        default:
        case IMAGE_NEAREST:
            base = SOIL_create_OGL_texture((const unsigned char*)data, sizeX, sizeY, channels, base, SOIL_FLAG_POWER_OF_TWO );
        break;
        case IMAGE_LINEAR:
            base = SOIL_create_OGL_texture((const unsigned char*)data, sizeX, sizeY, channels, base, SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_LINEAR );
        break;
        case IMAGE_MIPMAP:
            base = SOIL_create_OGL_texture((const unsigned char*)data, sizeX, sizeY, channels, base, SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS );
        break;
    }
	#endif
	return base;
};

bool POGEL::IMAGE::isbuilt() {
    return base != (unsigned int)NULL;
};

unsigned int POGEL::IMAGE::loadandbuild(const char *filename) {
	load(filename); return build();
};

std::string POGEL::IMAGE::toString() {
	char *szx = POGEL::string("%u",sizeX), *szy = POGEL::string("%u",sizeY), *sft = POGEL::string("%d",filtertype);
	std::string s =  "{[" + fileid + "],[" + std::string(szx) + "],[" + std::string(szy) + "],[" + std::string(sft) + "]}";
	free(szx); free(szy); free(sft);
	return s;
};

