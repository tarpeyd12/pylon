#ifndef KEYFRAMELIST_H_INCLUDED
#define KEYFRAMELIST_H_INCLUDED

#include "keyframe.h"

/*
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
*/

namespace ObjectLoader
{
    class KeyFrameList
    {
        private:
            unsigned int NumKeyFrames;
            CLASSLIST<ObjectLoader::KeyFrame*> _Frames;
        public:
            KeyFrameList();
            KeyFrameList(std::string);
            virtual ~KeyFrameList();
    };

    class AnimKeyFrame
    {
        private:
            unsigned int KeyFrameType;
            std::string Name;
            float TimeStart;
            float TimeEnd;
            unsigned int Flags;
            KeyFrameList *KFList;
        public:
            AnimKeyFrame();
            AnimKeyFrame(std::string);
            virtual ~AnimKeyFrame();

            std::string toString();
    };
}


#endif // KEYFRAMELIST_H_INCLUDED
