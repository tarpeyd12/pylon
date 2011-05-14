#include "keyframe.h"

namespace ObjectLoader
{
    KeyFrame::KeyFrame(std::string dat)
    {
        //std::cout << "hello" << std::endl;
        char* csrtmp;
        std::string tmp;
        float ftmp;

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Time Ref","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&TimeRef);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Color","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&Color.r,&Color.g,&Color.b,&Color.a);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Ambient","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&Ambient.r,&Ambient.g,&Ambient.b,&Ambient.a);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Diffuse","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&Diffuse.r,&Diffuse.g,&Diffuse.b,&Diffuse.a);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Specular","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&Specular.r,&Specular.g,&Specular.b,&Specular.a);

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

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"SpotAngle","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&SpotAngle);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Eye Pos","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&EyePos.x,&EyePos.y,&EyePos.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Lookat Pos","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&LookatPos.x,&LookatPos.y,&LookatPos.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Focal Length","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&FocalLength);
    }

    KeyFrame::~KeyFrame()
    {

    }

    std::string KeyFrame::toString()
    {
        return "";
    }
}
