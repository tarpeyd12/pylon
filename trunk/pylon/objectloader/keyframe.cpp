#include "keyframe.h"

namespace ObjectLoader
{
    KeyFrame::KeyFrame()
    {

    }

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
        sscanf(csrtmp,"%f %f %f %f",&Origin.x,&Origin.z,&Origin.y,&ftmp); //////////////// z up conversion ARGGG!

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

    KeyFrame::KeyFrame(KeyFrame next, KeyFrame prev, float t)
    {
        if(next.TimeRef == t)
        {
            // make this equal to the next keyframe
            TimeRef = next.TimeRef;
            Color = next.Color;
            Ambient = next.Ambient;
            Diffuse = next.Diffuse;
            Specular = next.Specular;
            Origin = next.Origin;
            Rotation = next.Rotation;
            Scale = next.Scale;
            Translate = next.Translate;
            SpotAngle = next.SpotAngle;
            EyePos = next.EyePos;
            LookatPos = next.LookatPos;
            FocalLength = next.FocalLength;
        }
        else if(prev.TimeRef == t)
        {
            // make this equal to the previous keyframe
            TimeRef = prev.TimeRef;
            Color = prev.Color;
            Ambient = prev.Ambient;
            Diffuse = prev.Diffuse;
            Specular = prev.Specular;
            Origin = prev.Origin;
            Rotation = prev.Rotation;
            Scale = prev.Scale;
            Translate = prev.Translate;
            SpotAngle = prev.SpotAngle;
            EyePos = prev.EyePos;
            LookatPos = prev.LookatPos;
            FocalLength = prev.FocalLength;
        }
        else
        {
            // create a keyframe inbetween the two with refference time
            TimeRef = t;
            t = t - prev.TimeRef;
            t /= (next.TimeRef - prev.TimeRef);
            Color = POGEL::COLOR((next.Color.r - prev.Color.r)*t+prev.Color.r,(next.Color.g - prev.Color.g)*t+prev.Color.g,(next.Color.b - prev.Color.b)*t+prev.Color.b,(next.Color.a - prev.Color.a)*t+prev.Color.a);
            Ambient = POGEL::COLOR((next.Ambient.r - prev.Ambient.r)*t,(next.Ambient.g - prev.Ambient.g)*t,(next.Ambient.b - prev.Ambient.b)*t,(next.Ambient.a - prev.Ambient.a)*t);
            Diffuse = POGEL::COLOR((next.Diffuse.r - prev.Diffuse.r)*t,(next.Diffuse.g - prev.Diffuse.g)*t,(next.Diffuse.b - prev.Diffuse.b)*t,(next.Diffuse.a - prev.Diffuse.a)*t);
            Specular = POGEL::COLOR((next.Specular.r - prev.Specular.r)*t,(next.Specular.g - prev.Specular.g)*t,(next.Specular.b - prev.Specular.b)*t,(next.Specular.a - prev.Specular.a)*t);
            Origin = (next.Origin-prev.Origin)*t+prev.Origin;
            Rotation = (next.Rotation-prev.Rotation)*t+prev.Rotation;
            Scale = (next.Scale-prev.Scale)*t+prev.Scale;
            Translate = (next.Translate-prev.Translate)*t+prev.Translate;
            SpotAngle = (next.SpotAngle-prev.SpotAngle)*t+prev.SpotAngle;
            EyePos = (next.EyePos-prev.EyePos)*t+prev.EyePos;
            LookatPos = (next.LookatPos-prev.LookatPos)*t+prev.LookatPos;
            FocalLength = (next.FocalLength-prev.FocalLength)*t+prev.FocalLength;
        }
    }

    KeyFrame::~KeyFrame()
    {

    }

    std::string KeyFrame::toString()
    {
        return Color.toString();
    }

    float KeyFrame::gettime()
    {
        return TimeRef;
    }

    POGEL::POINT KeyFrame::getpos()
    {
        return Origin;
    }
}
