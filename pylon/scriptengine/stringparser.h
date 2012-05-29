#ifndef STRINGPARSER_H_INCLUDED
#define STRINGPARSER_H_INCLUDED

#include <string>
#include <iostream>
#include <sstream>

namespace ScriptEngine
{
    namespace Parse
    {
        bool endsWith(const std::string&, const std::string&);
        unsigned int getOccurrencesInString(char, const std::string&);
        std::string getStringSection(char, unsigned int, bool, char, unsigned int, bool, const std::string&);
        std::string getStringSection_sc(char, unsigned int, bool, char, unsigned int, bool, const std::string&);
        std::string getLabeledSection(const std::string&,const std::string&,const std::string&,const std::string&);
        std::string getStringComponentLevel(char, bool, char, bool, const std::string&, const std::string&);
        std::string getStringComponentLevel(char, char, const std::string&, const std::string&);
        std::string getStringComponentLevel(const std::string&, bool, const std::string&, bool, const std::string&, const std::string&);

        std::string getStringComponentLevelNoMore(const std::string&, bool, const std::string&, bool, const std::string&, const std::string&);

        std::string getLine(const std::string&, unsigned int, char);
        std::string getLine(const std::string&, unsigned int);

        std::string reverse(const std::string&);

        std::string removeLeading(const std::string&, const std::string&);
        std::string removeTrailing(const std::string&, const std::string&);

        std::string removeAllAfter(const std::string&, char);

    }
}

#endif // STRINGPARSER_H_INCLUDED
