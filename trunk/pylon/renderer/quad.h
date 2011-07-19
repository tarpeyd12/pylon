#ifndef QUAD_H_INCLUDED
#define QUAD_H_INCLUDED

#include "../pogel/pogel.h"

namespace Renderer
{
    class Quad
    {
        private:
            //POGEL::TRIANGLE triangles[2];
            POGEL::IMAGE *image;
            POGEL::VERTEX verticies[4];
            CLASSLIST<Renderer::Quad*> children;
        public:

            Quad();
            Quad(int,int,int,int,POGEL::IMAGE*);
            //Quad(float,float,float,float,POGEL::IMAGE*);
            ~Quad();

            void draw();
    };
}

#endif // QUAD_H_INCLUDED
