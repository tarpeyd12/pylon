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

    ShadowDepthMap::ShadowDepthMap() : ShadowMap()
    {

    }

    ShadowDepthMap::ShadowDepthMap(std::string dat) : ShadowMap(dat)
    {

    }

    ShadowDepthMap::~ShadowDepthMap()
    {

    }

    TransparentShadowMap::TransparentShadowMap() : ShadowMap()
    {

    }

    TransparentShadowMap::TransparentShadowMap(std::string dat) : ShadowMap(dat)
    {

    }

    TransparentShadowMap::~TransparentShadowMap()
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

    Light::Light(std::string in) : ObjectLoader::_Base(in)
    {
        SDepthMap = ShadowDepthMap(ScriptEngine::Parse::getLabeledSection(in,"CShadowDepthMap","{","}"));
        TShadowMap_1 = TransparentShadowMap(ScriptEngine::Parse::getLabeledSection(in,"CTransparentShadowMap","{","}"));
        TShadowMap_2 = TransparentShadowMap(ScriptEngine::Parse::getLabeledSection(in,"CTransparentShadowMap","{","}"));
        FArray = FlareArray(ScriptEngine::Parse::getLabeledSection(in,"CFlareArray","{","}"));
        std::string dat = ScriptEngine::Parse::getStringComponentLevelNoMore("{",false,"}",false,in,"0");

        char* csrtmp;
        std::string tmp;
        //float ftmp;

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Radius","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&Radius);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Direction","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&Direction.x,&Direction.y,&Direction.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Light Type","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&LightType);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Spot Light","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&SpotLight);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Display As","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&DisplayAs);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"AmbientColor","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&AmbientColor.r,&AmbientColor.g,&AmbientColor.b,&AmbientColor.a);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"DiffuseColor","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&DiffuseColor.r,&DiffuseColor.g,&DiffuseColor.b,&DiffuseColor.a);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"SpecularColor","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&SpecularColor.r,&SpecularColor.g,&SpecularColor.b,&SpecularColor.a);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Spot Exponent","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&SpotExponent);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Cutoff Angle","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&CutoffAngle);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Constant Attenuation","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&ConstantAttenuation);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Linear Attenuation","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&LinearAttenuation);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Quadratic Attenuation","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&QuadraticAttenuation);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Enable Opaque Shadows","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&EnableOpaqueShadows);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Shadow All Opaque Objects","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&ShadowAllOpaqueObjects);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Num Opaque Shadow Casters","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&NumOpaqueShadowCasters);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Enable Transparent Shadows","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&EnableTransparentShadows);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Shadow All Transparent Objects","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&ShadowAllTransparentObjects);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Num Transparent Shadow Casters","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&NumTransparentShadowCasters);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Enable Particle Emitter Shadows","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&EnableParticleEmitterShadows);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Shadow All Particle Emitters","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&ShadowAllParticleEmitters);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Num Particle Emitter Shadow Casters","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&NumParticleEmitterShadowCasters);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Enable Lens flare depth test","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&EnableLensflaredepthtest);
    }

    Light::~Light()
    {

    }
}
