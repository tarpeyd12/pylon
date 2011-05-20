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

        std::string getStringSection_sc(char firstChar, unsigned int startingOccurrence, bool firstInclusive, char lastChar, unsigned int endingOccurrence, bool lastInclusive, std::string s) {
            if( /*firstChar == lastChar ||*/ s.empty()) return "";
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

        std::string getLabeledSection(std::string in, std::string secname, std::string start_str, std::string end_str)
        {
            if(in.empty() || secname.empty() || start_str.empty() || end_str.empty() || start_str.compare(end_str) == 0) return "";
            std::string cur = "", sec = "";
            unsigned int b = 0, lastpos = -1;
            do {
                cur.clear(); sec.clear();
                lastpos = in.find(secname,lastpos+1);
                cur = in.substr(lastpos);
                b = cur.find_first_of(start_str + end_str, secname.length());
                while(cur[b-1] == ' ' || cur[b-1] == '\t') b--;
                sec = cur.substr(0,b);
            } while(secname.compare(sec) != 0);
            return getStringComponentLevel(start_str,false,end_str,false,cur,"0");
        }

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

        std::string getStringComponentLevel(std::string startChar, bool firstInclusive, std::string endChar, bool lastInclusive, std::string s, std::string path_s)
        {
            if( startChar.compare(endChar) == 0 || startChar.length() == 0 || endChar.length() == 0 || s.empty() || path_s.empty())
                return "";
            std::stringstream path(std::stringstream::in | std::stringstream::out); path << path_s;
            unsigned int numEndChars = 0;
            for(unsigned int i = 0; i < endChar.length(); i++)
                 numEndChars += ScriptEngine::Parse::getOccurrencesInString(endChar[i], s);
            if(numEndChars == 0) return "";
            unsigned int level = 0, levelocc = 0, branchpos = 0, branch; path >> branch;
            bool isschr = false, isechr = false;
            unsigned int chlen = (startChar.length() > endChar.length() ? startChar.length() : endChar.length());
            for(unsigned int i = 0; i < s.length(); i++) {
                isschr = isechr = false;
                for(unsigned int p = 0; p < chlen; p++)
                    if(p < startChar.length() && s[i] == startChar[p]) isschr = true;
                    else if(p < endChar.length() && s[i] == endChar[p]) isechr = true;
                if(isschr && level++ == branchpos && levelocc++ >= branch) {
                    branchpos++; levelocc = 0;
                    if(path.good()) path >> branch;
                    else for(unsigned int g = i; i < s.length(); i++) {
                        bool uisschr = false, uisechr = false;
                        for(unsigned int p = 0; p < chlen; p++)
                            if(p < startChar.length() && s[i] == startChar[p]) uisschr = true;
                            else if(p < endChar.length() && s[i] == endChar[p]) uisechr = true;
                        if(uisschr) level++;
                        else if(uisechr && level-- == branchpos+1)
                            return s.substr(g+(firstInclusive?0:1), i-g+(lastInclusive?1:0)-1);
                    }
                }
                if(isechr) { level--; if(--numEndChars <= 0) return ""; }
            }
            return "";
        }

        std::string getStringComponentLevelNoMore(std::string startChar, bool firstInclusive, std::string endChar, bool lastInclusive, std::string s, std::string path_s)
        {
            std::string level_str = getStringComponentLevel(startChar,firstInclusive,endChar,lastInclusive,s,path_s);
            unsigned int level = 0, beg = 0;
            for(unsigned int i = 0; i < level_str.length(); i++) {
                for(unsigned int p = 0; p < startChar.length(); p++)
                    if(level_str[i] == startChar[p] && level++ == 0) beg = i;
                for(unsigned int p = 0; p < endChar.length(); p++) if(level_str[i] == endChar[p] && --level == 0) {
                    level_str = level_str.substr(0,beg) + level_str.substr(i+1);
                    i = beg = 0;
                }
            }
            return level_str;
        }

        std::string getLine(std::string dat, unsigned int ln, char ch)
        {
            return getStringSection_sc(ch,ln-1,false,ch,ln+1,false,dat);
        }

        std::string getLine(std::string dat, unsigned int ln)
        {
            return getLine(dat,ln,'\n');
        }
    }
}
