#ifndef OBJECT_PLATONIC_H_INCLUDED
#define OBJECT_PLATONIC_H_INCLUDED

//#include "objectloader.h"
#include "../scriptengine/scriptengine.h"
#include "../pogel/pogel.h"
#include "../fileloader/fileloader.h"

#include "keyframelist.h"

/*
C3dObjectPlatonic {
	Radius        < 1.000000 >
	Segments      < 8 >
	Type          < 4 >
	Smooth        < 1 >
	Smooth Angle  < 20.000000 >
	Num Vertices  < 20 >
		        < -0.618034, 0.000000, 1.618034 >
		        < 0.628034, 0.020000, 2.728034 >
		        < -1.000000, -2.170000, -1.000000 >
		        *//* ... *//*

	Num Normals   < 73 >
		        < -0.850651, 0.000000, 0.525731 >
		        < -0.649238, -0.204731, 0.732513 >
		        < -0.000000, 0.525731, 0.850651 >
		        *//* ... *//*

	Vertex Colors < 0 >
	Triangles     < 36 >
			  < 0/1/9, 3/8/36 >
			  < 0/9/16, 2/35/60 >
			  < 0/16/5, 2/60/23 >
			 *//* ... *//*

	C3dTriangleGroups {

		C3dTriangleGroup {
			Name          < default >
			Color         < 0.571429 1.000000 0.333333 1.000000 > // RGBA
			Material Name < None >
			Num Textures  < 0 >
		GLSL Shader   < None >
			Num Triangles < 36 >
			Sequential?   < 1 >
			Min-Max Range < 0, 35 >
		}
	}
	Name          < Platonic 0 >
	Color         < 0.571429 1.000000 0.333333 1.000000 > // RGBA
	Origin        < -12.987937 4.429999 4.287852 0.000000 >
	Rotation      < 0.000000 0.000000 0.000000 >
	Scale         < 1.000000 1.000000 1.000000 >
	Translate     < -0.510001 0.000000 -0.390000 >
	Constraints   < 0 >
	OrgnLimitsNeg < -2147483648.000000 -2147483648.000000 -2147483648.000000 >
	OrgnLimitsPos < 2147483648.000000 2147483648.000000 2147483648.000000 >
	RotnLimitsNeg < -360.000000 -360.000000 -360.000000 >
	RotnLimitsPos < 360.000000 360.000000 360.000000 >
	DisplayMode   < 2 >
	ShowObject    < 1 >
	Solid Color   < 1 >
	RenderMode    < 3 >
	Casts Shadows    < 1 >
	Receives Shadows < 1 >
	Enable Lighting  < 1 >
	Material Name < None >
	Num Textures  < 1 >
	Texture Map   < C:\Users\TarpeyD12\Pictures\itunes_homemade_movie_cover.bmp >
		CTextureMap {
			TexGenMethod  < 9217 >
			ProjectionMap < 2 >
			Map Mode      < 8448 >
			Blend Color   < 1.000000 1.000000 1.000000 1.000000 > // RGBA
			Texture Hint  < 4353 >
			Origin        < 2.180000 0.000000 1.410000 0.000000 >
			Rotation      < 0.000000 0.000000 0.000000 >
			Scale         < 1.000000 1.000000 1.000000 >
			Translate     < 0.000000 0.000000 0.000000 >
		}
	GLSL Shader   < None >
	CAnimation Procedures {
		CAnimKeyFrame {
			KeyFrame Type < 3 >
			Name          < KeyFrame >
			Time Start    < 0.000000 >
			Time End      < 10.000000 >
			Flags         < 4294967295 >
			CKeyFrame List {
				NumKeyFrames  < 2 >

				CKeyFrame {
					Time Ref      < 0.000000 >
					Color         < 0.571429 1.000000 0.333333 1.000000 > // RGBA
					Ambient       < 1.000000 1.000000 1.000000 1.000000 > // RGBA
					Diffuse       < 1.000000 1.000000 1.000000 1.000000 > // RGBA
					Specular      < 1.000000 1.000000 1.000000 1.000000 > // RGBA
					Origin        < -10.530001 4.429999 2.850000 0.000000 >
					Rotation      < 0.000000 0.000000 0.000000 >
					Scale         < 1.000000 1.000000 1.000000 >
					Translate     < -0.510001 0.000000 -0.390000 >
					SpotAngle     < 0.000000 >
					Eye Pos       < 0.000000 0.000000 0.000000 >
					Lookat Pos    < 0.000000 0.000000 0.000000 >
					Focal Length  < 0.000000 >
				}

				CKeyFrame {
					Time Ref      < 10.000000 >
					Color         < 0.571429 1.000000 0.333333 1.000000 > // RGBA
					Ambient       < 1.000000 1.000000 1.000000 1.000000 > // RGBA
					Diffuse       < 1.000000 1.000000 1.000000 1.000000 > // RGBA
					Specular      < 1.000000 1.000000 1.000000 1.000000 > // RGBA
					Origin        < -22.650002 4.429999 9.940001 0.000000 >
					Rotation      < 0.000000 0.000000 0.000000 >
					Scale         < 1.000000 1.000000 1.000000 >
					Translate     < -0.510001 0.000000 -0.390000 >
					SpotAngle     < 0.000000 >
					Eye Pos       < 0.000000 0.000000 0.000000 >
					Lookat Pos    < 0.000000 0.000000 0.000000 >
					Focal Length  < 0.000000 >
				}
			}
		}
	}
}
*/

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
        class Platonic
        {
            private:
                float Radius;
                unsigned int Segments;
                unsigned int Type;
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
                std::string Name;
                POGEL::COLOR Color;
                POGEL::POINT Origin;
                POGEL::POINT Rotation;
                POGEL::POINT Scale;
                POGEL::POINT Translate;
                unsigned int Constraints;
                POGEL::POINT OrgnLimitsNeg;
                POGEL::POINT OrgnLimitsPos;
                POGEL::POINT RotnLimitsNeg;
                POGEL::POINT RotnLimitsPos;
                unsigned int DisplayMode;
                unsigned int ShowObject;
                unsigned int SolidColor;
                unsigned int RenderMode;
                unsigned int CastsShadows;
                unsigned int ReceivesShadows;
                unsigned int EnableLighting;
                std::string MaterialName;
                unsigned int NumTextures;
                //CLASSLIST<> _Textures;
                std::string GLSLShader;
                AnimKeyFrame *_Animation_stuff;
            public:
                Platonic(std::string);
                virtual ~Platonic();

                POGEL::OBJECT* toObject();
                KeyFrame frame(float);
        };
    }
}

#endif // OBJECT_PLATONIC_H_INCLUDED
