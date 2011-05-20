#include "object_platonic.h"

namespace ObjectLoader
{
    TriangleGroup::TriangleGroup(std::string dat)
    {
        char* csrtmp;
        std::string tmp;

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Name","<",">");
        Name = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Color","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f %f %f %f",&Color.r,&Color.g,&Color.b,&Color.a);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Material Name","<",">");
        MaterialName = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Num Textures","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&NumTextures);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"GLSL Shader","<",">");
        GLSLShader = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Num Triangles","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&NumTriangles);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Sequential?","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&Sequential);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Min-Max Range","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u, %u",&MinMaxRange[0], &MinMaxRange[1]);
    }

    TriangleGroup::~TriangleGroup()
    {

    }

    namespace Object
    {
        Platonic::Platonic(std::string dat)
        {
            _Animation_stuff = AnimKeyFrame("");
        }

        Platonic::~Platonic()
        {

        }
    }
}
