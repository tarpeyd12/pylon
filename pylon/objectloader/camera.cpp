#include "camera.h"

namespace ObjectLoader
{
    Camera::Camera(std::string dat)
    {
        char* csrtmp;
        std::string tmp;
        float ftmp;

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"LookAt","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&LookAt.x,&LookAt.y,&LookAt.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"EyePos","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&EyePos.x,&EyePos.y,&EyePos.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"UpDir","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f",&UpDir.x,&UpDir.y,&UpDir.z);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Perspective View","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&PerspectiveView);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Field of View 'Y'","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&FieldofView);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Near clip Plane","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&NearClipPlane);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Far clip Plane","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&FarClipPlane);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"View Type","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&ViewType);

        // animation stuffs
    }

    Camera::~Camera()
    {

    }
}
