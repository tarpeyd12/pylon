#ifndef STRINGPARSER_H_INCLUDED
#define STRINGPARSER_H_INCLUDED

#include <string>
#include <iostream>
#include <sstream>

namespace ScriptEngine
{
    namespace Parse
    {
        unsigned int getOccurrencesInString(char, std::string);
        std::string getStringSection(char, unsigned int, bool, char, unsigned int, bool, std::string);
        std::string getStringSection_sc(char, unsigned int, bool, char, unsigned int, bool, std::string);
        std::string getLabeledSection(std::string,std::string,std::string,std::string);
        std::string getStringComponentLevel(char, bool, char, bool, std::string, std::string);
        std::string getStringComponentLevel(char, char, std::string, std::string);
        std::string getStringComponentLevel(std::string, bool, std::string, bool, std::string, std::string);

        std::string getLine(std::string,unsigned int,char);
        std::string getLine(std::string,unsigned int);
    }
}

#endif // STRINGPARSER_H_INCLUDED
