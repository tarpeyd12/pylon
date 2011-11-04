#include "camera.h"

namespace Renderer
{
    namespace Camera
    {
        POGEL::POINT camrot;
        POGEL::POINT prot;
        POGEL::POINT campos;
        POGEL::POINT ppos;

        POGEL::VECTOR GetCamDirection()
        {
            POGEL::MATRIX mat(POGEL::POINT(360)-Renderer::Camera::camrot,MATRIX_CONSTRUCT_ROTATION);
            POGEL::VECTOR refpos = mat.transformPoint(POGEL::POINT(0,0,1));
            return refpos.normal();
        }

    }
}