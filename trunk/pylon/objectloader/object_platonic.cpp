#include "object_platonic.h"

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
        Platonic::Platonic(std::string in)
        {
            std::string s_Triangle_Groups = ScriptEngine::Parse::getLabeledSection(in,"C3dTriangleGroups","{","}");
            std::string s_Animation_Procedures = ScriptEngine::Parse::getLabeledSection(in,"CAnimation Procedures","{","}");

            std::string dat = in;//ScriptEngine::Parse::getStringComponentLevelNoMore("{",false,"}",false,in,"0");

            char* csrtmp;
            std::string tmp;
            float ftmp;

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

            dat = ScriptEngine::Parse::getStringComponentLevelNoMore("{",false,"}",false,in,"0");

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
        }

        Platonic::~Platonic()
        {
            _Verticies.clear();
            _Normals.clear();
            _Colors.clear();
            _Triangles.clear();
            _ui_Triangles.clear();
            __TriangleGroups.clear();
            delete _Animation_stuff;
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
