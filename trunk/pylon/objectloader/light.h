#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

//#include "objectloader.h"

#include "../scriptengine/scriptengine.h"
#include "../pogel/pogel.h"
#include "../fileloader/fileloader.h"

/*
C3dObjectLight {
	Radius        < 2.000000 >
	Direction     < 0.000000 0.000000 0.000000 >
	Light Type    < 2 >
	Spot Light    < 0 >
	Display As    < 1 >
	AmbientColor  < 0.100000 0.100000 0.100000 1.000000 > //RGBA
	DiffuseColor  < 0.700000 0.700000 0.700000 1.000000 > //RGBA
	SpecularColor < 0.900000 0.900000 0.900000 1.000000 > //RGBA
	Spot Exponent < 20.000000 >
	Cutoff Angle  < 180.000000 >
	Constant Attenuation  < 1.000000 >
	Linear Attenuation    < 0.000000 >
	Quadratic Attenuation < 0.000000 >
	Enable Opaque Shadows               < 1 >
	Shadow All Opaque Objects           < 1 >
	CShadowDepthMap {
			Caster Name    <  >
			ShadowMap Size < 512 >
			Buffer Method  < 0 >
	}
	Num Opaque Shadow Casters           < 0 >
	Enable Transparent Shadows          < 0 >
	Shadow All Transparent Objects      < 1 >
	CTransparentShadowMap {
			Caster Name    <  >
			ShadowMap Size < 512 >
			Buffer Method  < 0 >
	}
	Num Transparent Shadow Casters      < 0 >
	Enable Particle Emitter Shadows     < 0 >
	Shadow All Particle Emitters        < 1 >
	CTransparentShadowMap {
			Caster Name    <  >
			ShadowMap Size < 512 >
			Buffer Method  < 0 >
	}
	Num Particle Emitter Shadow Casters < 0 >
	CFlareArray {
		Glow List     < Manual >
		Glow Scale    < 1.000000 >
		Glow Sat'n    < 1.000000 >
		Reflex List   < Manual >
		Reflex Scale  < 1.000000 >
		Reflex Sat'n  < 1.000000 >
	}
	Enable Lens flare depth test < 0 >
	Name          < Light 0 >
	Color         < 0.900000 0.900000 0.900000 1.000000 > // RGBA
	Origin        < 150.000000 -150.000000 750.000000 1.000000 >
	Rotation      < 0.000000 0.000000 0.000000 >
	Scale         < 1.000000 1.000000 1.000000 >
	Translate     < 0.000000 0.000000 0.000000 >
	Constraints   < 0 >
	OrgnLimitsNeg < -2147483648.000000 -2147483648.000000 -2147483648.000000 >
	OrgnLimitsPos < 2147483648.000000 2147483648.000000 2147483648.000000 >
	RotnLimitsNeg < -360.000000 -360.000000 -360.000000 >
	RotnLimitsPos < 360.000000 360.000000 360.000000 >
	DisplayMode   < 0 >
	ShowObject    < 1 >
	Solid Color   < 1 >
	RenderMode    < 1 >
	Casts Shadows    < 0 >
	Receives Shadows < 0 >
	Enable Lighting  < 1 >
	Material Name < None >
	Num Textures  < 0 >
	GLSL Shader   < None >
	CAnimation Procedures {
	}
}
*/

namespace ObjectLoader
{
    class ShadowMap
    {
        private:
            std::string CasterName;
			unsigned int ShadowMapSize;
			unsigned int BufferMethod;
        public:
            ShadowMap();
            ShadowMap(std::string);
            virtual ~ShadowMap();
    };

    class ShadowDepthMap : public ObjectLoader::ShadowMap
    {
        public:
            ShadowDepthMap();
            ShadowDepthMap(std::string);
            virtual ~ShadowDepthMap();
    };

    class TransparentShadowMap : public ObjectLoader::ShadowMap
    {
        public:
            TransparentShadowMap();
            TransparentShadowMap(std::string);
            virtual ~TransparentShadowMap();
    };

    class FlareArray
    {
        private:
            std::string GlowList;
            float GlowScale;
            float GlowSatn;
            std::string ReflexList;
            float ReflexScale;
            float ReflexSatn;
        public:
            FlareArray();
            FlareArray(std::string);
            virtual ~FlareArray();
    };

    class Light
    {
        private:
            float Radius;
            POGEL::VECTOR Direction;
            unsigned int LightType;
            unsigned int SpotLight;
            unsigned int DisplayAs;
            POGEL::COLOR AmbientColor;
            POGEL::COLOR DiffuseColor;
            POGEL::COLOR SpecularColor;
            float SpotExponent;
            float CutoffAngle;
            float ConstantAttenuation;
            float LinearAttenuation;
            float QuadraticAttenuation;
            unsigned int EnableOpaqueShadows;
            unsigned int ShadowAllOpaqueObjects;
            ShadowDepthMap SDepthMap;
            unsigned int NumOpaqueShadowCasters;
            unsigned int EnableTransparentShadows;
            unsigned int ShadowAllTransparentObjects;
            TransparentShadowMap TShadowMap_1;
            unsigned int NumTransparentShadowCasters;
            unsigned int EnableParticleEmitterShadows;
            unsigned int ShadowAllParticleEmitters;
            TransparentShadowMap TShadowMap_2;
            unsigned int NumParticleEmitterShadowCasters;
            FlareArray FArray;
            unsigned int EnableLensflaredepthtest;
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
            std::string GLSLShader;

            // animation stuff
        public:
            Light(std::string);
            virtual ~Light();
    };
}

#endif // LIGHT_H_INCLUDED
