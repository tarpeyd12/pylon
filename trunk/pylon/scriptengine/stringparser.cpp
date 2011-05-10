#include "stringparser.h"

namespace ScriptEngine
{
    namespace Parse
    {
        unsigned int getOccurrencesInString(char c, std::string s) {
            unsigned int count = 0;
            for(unsigned int i = 0; i < s.length(); i++) if(s[i] == c) count++;
            return count;
        };

        // getStringSection('[', 2, false, '>', 1, true, "{[5],[__2<33>]}");
        //    will return "__2<33>"
        std::string getStringSection(char firstChar, unsigned int startingOccurrence, bool firstInclusive, char lastChar, unsigned int endingOccurrence, bool lastInclusive, std::string s) {
            if( firstChar == lastChar || s.empty()) return "";
            char chars[2]; chars[0]=firstChar; chars[1]=lastChar;
            unsigned int pos[2], occs[2], p[2], c;
            occs[0] = occs[1] = pos[0] = pos[1] = c = 0;
            p[0] = startingOccurrence; p[1] = endingOccurrence;
            for(unsigned int i = 0; i < s.length(); i++) if(s[i] == chars[c] && ++occs[c] == p[c]) {
                pos[c] = i+(c==0?(firstInclusive?0:1):(lastInclusive?1:0));
                if(++c>=2) break;
            }
            if(pos[0] >= pos[1]) return "";
            return s.substr(pos[0], pos[1]-pos[0]);

        };

        // getStringComponentLevel( '{', false, '}', false, "{{} {} {{} {{{} {hello}} {} {}}} {}}", "0 2 1 0 1");
        //    will return "hello"
        std::string getStringComponentLevel(char startChar, bool firstInclusive, char endChar, bool lastInclusive, std::string s, std::string path_s) {
            if( startChar == endChar || s.empty() || path_s.empty()) return "";
            std::stringstream path(std::stringstream::in | std::stringstream::out); path << path_s;
            unsigned int numEndChars = ScriptEngine::Parse::getOccurrencesInString(endChar, s);
            if(numEndChars == 0) return "";
            unsigned int level = 0, levelocc = 0, branchpos = 0, branch; path >> branch;
            for(unsigned int i = 0; i < s.length(); i++) {
                if(s[i] == startChar && level++ == branchpos && levelocc++ >= branch) {
                    branchpos++; levelocc = 0;
                    if(path.good()) path >> branch;
                    else for(unsigned int p = i; i < s.length(); i++)
                        if(s[i] == startChar) level++;
                        else if(s[i] == endChar && level-- == branchpos+1) return s.substr(p+(firstInclusive?0:1), i-p+(lastInclusive?1:0));
                }
                if(s[i] == endChar) { level--; if(--numEndChars <= 0) return ""; }
            }
            return "";
        };

        // getStringComponentLevel( '{', '}', "{{} {} {{} {{{} {hello}} {} {}}} {}}", "0 2 1 0 1");
        //    will return "{hello}"
        std::string getStringComponentLevel(char startChar, char endChar, std::string s, std::string path_s) {
            return ScriptEngine::Parse::getStringComponentLevel(startChar, true, endChar, true, s, path_s);
        };
    }
}
