#include "object_platonic.h"

namespace ObjectLoader
{
    namespace Object
    {
        Platonic::Platonic(std::string in) : ObjectLoader::Object::_BaseObject(in)
        {
            std::string s_Triangle_Groups = ScriptEngine::Parse::getLabeledSection(in,"C3dTriangleGroups","{","}");
            std::string s_Animation_Procedures = ScriptEngine::Parse::getLabeledSection(in,"CAnimation Procedures","{","}");

            std::string dat = in;

            char* csrtmp;
            std::string tmp;

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Segments","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%u",&Segments);

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Type","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%u",&Type);
        }

        Platonic::~Platonic()
        {
            //ObjectLoader::Object::_BaseObject::~_BaseObject();
        }

        POGEL::OBJECT* Platonic::toObject()
        {
            POGEL::OBJECT* ret = new POGEL::OBJECT((char*)Name.c_str());

            ret->position = Origin;
            ret->rotation = Rotation;

            for(unsigned int i = 0; i < _Triangles.length(); i++)
                ret->addtriangle(_Triangles[i]);
            return ret;
        }

        KeyFrame Platonic::frame(float t)
        {
            return _Animation_stuff->keyAt(t);
        }
    }
}
