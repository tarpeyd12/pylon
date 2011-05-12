#include "fileloader.h"

namespace FileLoader
{
    std::string getline(std::string filename, int lineNum)
    {
        if(lineNum < 0)
            return "";
        std::ifstream ifs ( filename.c_str(), std::ifstream::in );
        std::string line;
        if(!ifs.good())
        {
            ifs.close();
            return "";
        }
        int currentLine = 0;
        do
        {
            line.clear();
            std::getline(ifs,line);
            currentLine++;
        }
        while(ifs.good() && currentLine < lineNum);
        ifs.close();
        return line;
    }

    std::string totalfile(std::string filename)
    {
        std::string ret = "";
        std::ifstream ifs ( filename.c_str(), std::ifstream::in );
        std::string line;
        if(!ifs.good())
        {
            ifs.close();
            return "";
        }
        do
        {
            line.clear();
            std::getline(ifs,line);
            ret += line + "\n";
        }
        while(ifs.good());
        ifs.close();
        return ret;
    }

    bool checkfile(std::string filename)
    {
        std::ifstream ifs ( filename.c_str(), std::ifstream::in );
        bool ret = ifs.good();
        ifs.close();
        return ret;
    }
}

