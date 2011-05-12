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
        std::string getLabeledSection(std::string,std::string,std::string,std::string);
        std::string getStringComponentLevel(char, bool, char, bool, std::string, std::string);
        std::string getStringComponentLevel(char, char, std::string, std::string);
    }
}

#endif // STRINGPARSER_H_INCLUDED
