#include "light.h"

namespace Renderer
{
    namespace Lighting
    {

        Renderer::Lighting::Light Lights[MAXNUMLIGHTS];


        Light::Light()
        {
            position = POGEL::POINT();
            ambient = POGEL::COLOR();
            diffuse = POGEL::COLOR();
            specular = POGEL::COLOR();
            inCameraSpace = false;
            lightNumber = -1;
        }

        Light::Light(POGEL::POINT p, POGEL::COLOR a, POGEL::COLOR d, POGEL::COLOR s)
        {
            position = p;
            ambient = a;
            diffuse = d;
            specular = s;
            inCameraSpace = false;
            lightNumber = -1;
        }

        Light::Light(POGEL::POINT p, POGEL::COLOR a, POGEL::COLOR d, POGEL::COLOR s, bool i)
        {
            position = p;
            ambient = a;
            diffuse = d;
            specular = s;
            inCameraSpace = i;
            lightNumber = -1;
        }

        Light::~Light()
        {
            lightNumber = -1;
        }

        void Light::draw()
        {
            if(lightNumber < 0 || lightNumber >= MAXNUMLIGHTS)
            {
                glDisable(glLight(lightNumber));
                return;
            }

            glEnable(glLight(lightNumber));

            float light_ambient[4]  = { ambient.r, ambient.g, ambient.b, ambient.a };
            float light_diffuse[4]  = { diffuse.r, diffuse.g, diffuse.b, diffuse.a };
            float light_specular[4] = { specular.r, specular.g, specular.b, specular.a };
            float light_position[4] = { position.x, position.y, position.z, 1.0f };

            glLightfv(glLight(lightNumber), GL_AMBIENT,  light_ambient);
            glLightfv(glLight(lightNumber), GL_DIFFUSE,  light_diffuse);
            glLightfv(glLight(lightNumber), GL_SPECULAR, light_specular);
            glLightfv(glLight(lightNumber), GL_POSITION, light_position);
        }

    }
}
