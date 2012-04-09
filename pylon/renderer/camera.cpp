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
            POGEL::MATRIX mat(Renderer::Camera::camrot*-1.0f,MATRIX_CONSTRUCT_ROTATION);
            POGEL::VECTOR refpos = mat.transformVector(POGEL::VECTOR(0.0f,0.0f,-1.0f));
            return refpos.normal();
        }

        Viewpoint::Viewpoint() : rotation(), position()
        {
            //position = rotation = POGEL::POINT();
        }

        Viewpoint::Viewpoint( const POGEL::POINT& pos, const POGEL::POINT& rot ) : rotation( rot ), position( pos )
        {
            /*position = pos;
            rotation = rot;*/
        }

        void Viewpoint::set()
        {
            glRotatef( rotation.x,  1.0f, 0.0f, 0.0f );
            glRotatef( rotation.y,  0.0f, 1.0f, 0.0f );
            glRotatef( rotation.z,  0.0f, 0.0f, 1.0f );
            glTranslatef( position.x, position.y, position.z );
        }

        POGEL::VECTOR Viewpoint::GetCamDirection()
        {
            POGEL::MATRIX mat(rotation*-1.0f,MATRIX_CONSTRUCT_ROTATION);
            POGEL::VECTOR refpos(mat.transformVector(POGEL::VECTOR(0.0f,0.0f,-1.0f)));
            return refpos.normal();
        }

    }
}
