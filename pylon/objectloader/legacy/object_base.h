#ifndef OBJECT_BASE_H_INCLUDED
#define OBJECT_BASE_H_INCLUDED

//#include "objectloader.h"
#include "../scriptengine/scriptengine.h"
#include "../pogel/pogel.h"
#include "../fileloader/fileloader.h"

#include "keyframelist.h"
#include "base.h"

namespace ObjectLoader
{
    class TriangleGroup
    {
        private:
            std::string Name;
			POGEL::COLOR Color;
			std::string MaterialName;
			unsigned int NumTextures;
            std::string GLSLShader;
			unsigned int NumTriangles;
			unsigned int Sequential;
			unsigned int MinMaxRange[2];
        public:
            TriangleGroup();
            TriangleGroup(std::string);
            virtual ~TriangleGroup();
    };

    namespace Object
    {
        class _BaseObject : public ObjectLoader::_Base
        {
            public:
                float Radius;
                unsigned int Smooth;
                float SmoothAngle;
                unsigned int NumVertices;
                CLASSLIST<POGEL::POINT> _Verticies;
                unsigned int NumNormals;
                CLASSLIST<POGEL::VECTOR> _Normals;
                unsigned int VertexColors;
                CLASSLIST<POGEL::COLOR> _Colors;
                unsigned int Triangles;
                CLASSLIST<POGEL::TRIANGLE> _Triangles;
                CLASSLIST<unsigned int*> _ui_Triangles;
                CLASSLIST<TriangleGroup> __TriangleGroups;
            public:
                _BaseObject(std::string);
                virtual ~_BaseObject();

                POGEL::OBJECT* toObject();
                KeyFrame frame(float);
        };
    }
}

#endif // OBJECT_BASE_H_INCLUDED
