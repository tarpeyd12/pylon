#include "object_base.h"

namespace ObjectLoader
{
    TriangleGroup::TriangleGroup()
    {

    }

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
        _BaseObject::_BaseObject(std::string in) : ObjectLoader::_Base(in)
        {
            std::string s_Triangle_Groups = ScriptEngine::Parse::getLabeledSection(in,"C3dTriangleGroups","{","}");

            std::string dat = in;//ScriptEngine::Parse::getStringComponentLevelNoMore("{",false,"}",false,in,"0");

            char* csrtmp;
            std::string tmp;
            //float ftmp;

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Radius","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%f",&Radius);

            /*tmp = ScriptEngine::Parse::getLabeledSection(dat,"Segments","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%u",&Segments);

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Type","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%u",&Type);*/

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Smooth","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%u",&Smooth);

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Smooth Angle","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%f",&SmoothAngle);

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Num Vertices","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%u",&NumVertices);

            while(_Verticies.length() < NumVertices)
            {
                std::string line = ScriptEngine::Parse::getLine(dat, 8+_Verticies.length());
                POGEL::POINT p;
                tmp = ScriptEngine::Parse::getLabeledSection("p" + line,"p","<",">");
                csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
                sscanf(csrtmp,"%f, %f, %f",&p.x,&p.y,&p.z);
                _Verticies += p;
            }

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Num Normals","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%u",&NumNormals);

            while(_Normals.length() < NumNormals)
            {
                std::string line = ScriptEngine::Parse::getLine(dat, NumVertices+9+_Normals.length());
                POGEL::VECTOR p;
                tmp = ScriptEngine::Parse::getLabeledSection("p" + line,"p","<",">");
                csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
                sscanf(csrtmp,"%f, %f, %f",&p.x,&p.y,&p.z);
                _Normals += p;
            }

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Vertex Colors","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%u",&VertexColors);

            while(_Colors.length() < VertexColors)
            {
                std::string line = ScriptEngine::Parse::getLine(dat, NumNormals+NumVertices+10+_Colors.length());
                POGEL::COLOR p;
                tmp = ScriptEngine::Parse::getLabeledSection("p" + line,"p","<",">");
                csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
                sscanf(csrtmp,"%f %f %f %f",&p.r,&p.g,&p.b,&p.a); //
                _Colors += p;
            }

            tmp = ScriptEngine::Parse::getLabeledSection(dat,"Triangles","<",">");
            csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
            sscanf(csrtmp,"%u",&Triangles);

            POGEL::VERTEX a,b,c;
            while(_Triangles.length() < Triangles)
            {
                std::string line = ScriptEngine::Parse::getLine(dat, VertexColors+NumNormals+NumVertices+11+_Triangles.length());
                unsigned int p[6];
                tmp = ScriptEngine::Parse::getLabeledSection("p" + line,"p","<",">");
                csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
                sscanf(csrtmp,"%u/%u/%u, %u/%u/%u",&p[0],&p[1],&p[2],&p[3],&p[4],&p[5]);
                //_ui_Triangles += p;
                a = POGEL::VERTEX(_Verticies[p[0]]), b = POGEL::VERTEX(_Verticies[p[1]]), c = POGEL::VERTEX(_Verticies[p[2]]);
                a.normal = _Normals[p[3]]; b.normal = _Normals[p[4]]; c.normal = _Normals[p[5]];
                // use default texture for now
                _Triangles += POGEL::TRIANGLE(a,b,c,POGEL::requestImage("{[default_2.bmp],[32],[32],[1]}"),TRIANGLE_VERTEX_NORMALS);
            }

            //s_Triangle_Groups ScriptEngine::Parse::getLabeledSection(in,"C3dTriangleGroups","{","}")
            if(s_Triangle_Groups.length() > 50)
                __TriangleGroups += TriangleGroup(ScriptEngine::Parse::getLabeledSection(dat,"C3dTriangleGroups","{","}"));
        }

        _BaseObject::~_BaseObject()
        {
            _Verticies.clear();
            _Normals.clear();
            _Colors.clear();
            _Triangles.clear();
            _ui_Triangles.clear();
            __TriangleGroups.clear();
            if(_Animation_stuff)
                delete _Animation_stuff;
        }

        POGEL::OBJECT* _BaseObject::toObject()
        {
            POGEL::OBJECT* ret = new POGEL::OBJECT((char*)Name.c_str());

            ret->position = Origin;
            ret->rotation = Rotation;

            for(unsigned int i = 0; i < _Triangles.length(); i++)
                ret->addtriangle(_Triangles[i]);
            return ret;
        }

        KeyFrame _BaseObject::frame(float t)
        {
            return _Animation_stuff->keyAt(t);
        }
    }
}
