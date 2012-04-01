#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

//#include "objectloader.h"

#include "../scriptengine/scriptengine.h"
#include "../pogel/pogel.h"
#include "../fileloader/fileloader.h"

#include "keyframelist.h"

/*
C3dCamera {
	LookAt    < -7.927460 -16.687195 4.024653 >
	EyePos    < -7.927460 -38.801399 4.024653 >
	UpDir     < 0.000000 0.000000 1.000000 >
	Perspective View  < 0 >
	Field of View 'Y' < 45.000000 >
	Near clip Plane   < 0.500000 >
	Far clip Plane    < 774.444031 >
	View Type         < 1 >
	CAnimation Procedures {
	}
}
*/

namespace ObjectLoader
{
    class Camera
    {
        private:
            POGEL::POINT LookAt;
            POGEL::POINT EyePos;
            POGEL::VECTOR UpDir;
            unsigned int PerspectiveView;
            float FieldofView;
            float NearClipPlane;
            float FarClipPlane;
            unsigned int ViewType;
            // animationstuffs
            AnimKeyFrame *_Animation_stuff;
        public:
            Camera(std::string);
            virtual ~Camera();


    };
}

#endif // CAMERA_H_INCLUDED
