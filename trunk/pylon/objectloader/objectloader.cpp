#include "objectloader.h"

namespace ObjectLoader
{
    std::string getobject(std::string name, std::string type, std::string dat)
    {
        std::string ctype = "";
        int linenum = 0;
        int totallinenum = ScriptEngine::Parse::getOccurrencesInString('\n',dat);
        std::string rdat = "";
        std::string gline = "";
        bool end = false;
        do
        {
            std::string line = ScriptEngine::Parse::getLine(dat,linenum++);
            unsigned int nlc = 0;
            while(line[nlc] == '\t' || line[nlc] == ' ')
                nlc++;
            unsigned int nlnc = line.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890",nlc);
            gline = line.substr(nlc,nlnc);
            if(gline.compare(type) == 0)
            {
                unsigned int i = 0, ch = 0;
                while(i < linenum-2)
                    if(dat[ch++] == '\n')
                        i++;
                rdat = dat.substr(ch-1);
                end = true;
            }
        }
        while(!end && linenum <= totallinenum);

        return gline + " " + ScriptEngine::Parse::getStringComponentLevel("{<",true,"}>",true,rdat,"0");
    }

    std::string getobjectformfile(std::string name, std::string type, std::string filename)
    {
        return getobject(name,type,FileLoader::totalfile(filename));
    }
}
