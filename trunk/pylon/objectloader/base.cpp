#include "base.h"

namespace ObjectLoader
{
    /// \brief _Base class generic blind constructor
    /// \return an unusable _Base object
    /// do not use, is only so the compiler would stop complaning
    _Base::_Base()
    {

    }

    /// \brief _Base class specific constructor
    ///
    /// \param a string that contains the data to be parsed
    /// \return a new _Base object
    ///
    /// should not be used other than to create a new class for 3d data loading.

    _Base::_Base(std::string in)
    {
        std::string s_Animation_Procedures = ScriptEngine::Parse::getLabeledSection(in,"CAnimation Procedures","{","}");
        std::string dat = ScriptEngine::Parse::getStringComponentLevelNoMore("{",false,"}",false,in,"0");

        char* csrtmp;
        std::string tmp;
        float ftmp;

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

        if(s_Animation_Procedures.length() > 50)
            _Animation_stuff = new AnimKeyFrame(ScriptEngine::Parse::getLabeledSection(s_Animation_Procedures,"CAnimKeyFrame","{","}"));
        else
            _Animation_stuff = NULL;
    }

    _Base::~_Base()
    {
        if(_Animation_stuff)
            delete _Animation_stuff;
    }
}
