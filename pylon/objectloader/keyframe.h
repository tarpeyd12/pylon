#ifndef KEYFRAME_H_INCLUDED
#define KEYFRAME_H_INCLUDED

#include "objectloader.h"

/*
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
*/

namespace ObjectLoader
{
    class KeyFrame
    {
        private:
            float TimeRef;
            POGEL::COLOR Color;
            POGEL::COLOR Ambient;
            POGEL::COLOR Diffuse;
            POGEL::COLOR Specular;
            POGEL::POINT Origin;
            POGEL::POINT Rotation;
            POGEL::POINT Scale;
            POGEL::POINT Translate;
            float SpotAngle;
            POGEL::POINT EyePos;
            POGEL::POINT LookatPos;
            float FocalLength;
        public:
            KeyFrame(std::string);
            KeyFrame(KeyFrame,KeyFrame,float);
            virtual ~KeyFrame();

            std::string toString();
    };
}

#endif // KEYFRAME_H_INCLUDED
