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

    Light::Light(std::string in)
    {
        SDepthMap = ShadowDepthMap(ScriptEngine::Parse::getLabeledSection(in,"CShadowDepthMap","{","}"));
        TShadowMap_1 = TransparentShadowMap(ScriptEngine::Parse::getLabeledSection(in,"CTransparentShadowMap","{","}"));
        TShadowMap_2 = TransparentShadowMap(ScriptEngine::Parse::getLabeledSection(in,"CTransparentShadowMap","{","}"));
        FArray = FlareArray(ScriptEngine::Parse::getLabeledSection(in,"CFlareArray","{","}"));
        std::string dat = ScriptEngine::Parse::getStringComponentLevelNoMore("{",false,"}",false,in,"0");

        char* csrtmp;
        std::string tmp;
        float ftmp;

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

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Name","<",">");
        Name = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Color","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&Color.r,&Color.g,&Color.b,&Color.a);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Origin","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&Origin.x,&Origin.y,&Origin.z,&ftmp);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Rotation","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&Rotation.x,&Rotation.y,&Rotation.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Scale","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&Scale.x,&Scale.y,&Scale.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Translate","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&Translate.x,&Translate.y,&Translate.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Constraints","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&Constraints);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"OrgnLimitsNeg","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&OrgnLimitsNeg.x,&OrgnLimitsNeg.y,&OrgnLimitsNeg.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"OrgnLimitsPos","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&OrgnLimitsPos.x,&OrgnLimitsPos.y,&OrgnLimitsPos.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"RotnLimitsNeg","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&RotnLimitsNeg.x,&RotnLimitsNeg.y,&RotnLimitsNeg.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"RotnLimitsPos","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&RotnLimitsPos.x,&RotnLimitsPos.y,&RotnLimitsPos.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"DisplayMode","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&DisplayMode);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"ShowObject","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&ShowObject);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Solid Color","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&SolidColor);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"RenderMode","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&RenderMode);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Casts Shadows","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&CastsShadows);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Receives Shadows","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&ReceivesShadows);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Enable Lighting","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&EnableLighting);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Material Name","<",">");
        MaterialName = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Num Textures","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&NumTextures);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"GLSL Shader","<",">");
        GLSLShader = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        // animation stuff
    }

    Light::~Light()
    {

    }
}
