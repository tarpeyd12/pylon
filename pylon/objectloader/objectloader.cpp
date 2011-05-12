#include "objectloader.h"

namespace ObjectLoader
{
    std::string getobject(std::string name, std::string dat)
    {
        std::string rel;
        std::string curname;
        char* num;
        int count = 0;
        do
        {
            num = POGEL::string("%d",count);
            rel = ScriptEngine::Parse::getStringComponentLevel('{','}',dat,std::string(num));
            curname = ScriptEngine::Parse::getLabeledSection(rel,name,"<",">");
            free(num);
            count++;
            if(curname.length() == 0)
                return "";
        }
        while(name.compare(curname) != 0);

        return ScriptEngine::Parse::getStringComponentLevel('{','}',dat,std::string(POGEL::string("%d",count-1)));
    }
}
