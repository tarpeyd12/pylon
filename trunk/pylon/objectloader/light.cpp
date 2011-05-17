#include "light.h"

namespace ObjectLoader
{
    ShadowMap::ShadowMap()
    {
        CasterName = "";
        ShadowMapSize = 512;
        BufferMethod = 0;
    }

    ShadowMap::ShadowMap(std::string dat)
    {
        char* csrtmp;
        std::string tmp;
        //float ftmp;

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Caster Name","<",">");
        CasterName = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"ShadowMap Size","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&ShadowMapSize);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Buffer Method","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&BufferMethod);
    }

    ShadowMap::~ShadowMap()
    {

    }

    FlareArray::FlareArray()
    {
        GlowList = "";
        GlowScale = 1.0;
        GlowScale = 1.0;
        ReflexList = "";
        ReflexScale = 1.0;
        ReflexScale = 1.0;
    }

    FlareArray::FlareArray(std::string dat)
    {
        char* csrtmp;
        std::string tmp;
        //float ftmp;

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Glow List","<",">");
        GlowList = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Glow Scale","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&GlowScale);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Glow Sat'n","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&GlowSatn);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Reflex List","<",">");
        ReflexList = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Reflex Scale","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&ReflexScale);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Reflex Sat'n","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&ReflexSatn);
    }

    FlareArray::~FlareArray()
    {

    }

    Light::Light(std::string dat)
    {
        std::string toplevel = ScriptEngine::Parse::getStringComponentLevelNoMore("{",false,"}",false,dat,"0");
    }

    Light::~Light()
    {

    }
}
