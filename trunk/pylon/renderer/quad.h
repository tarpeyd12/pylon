#ifndef QUAD_H_INCLUDED
#define QUAD_H_INCLUDED

#include "../pogel/pogel.h"
#include "../lists/lists.h"

namespace Renderer
{
    class Quad
    {
        private:
            //POGEL::TRIANGLE triangles[2];
            POGEL::IMAGE *image;
            POGEL::VERTEX verticies[4];
            unsigned int properties;
            ClassList<Renderer::Quad*> *children;
        public:

            Quad();
            Quad(int,int,int,int,POGEL::IMAGE*);
            Quad(int,int,int,int,POGEL::IMAGE*,unsigned int);
            Quad(float,float,float,float,POGEL::IMAGE*);
            Quad(float,float,float,float,POGEL::IMAGE*,unsigned int);
            ~Quad();

            PROPERTIES_METHODS;

            void set(Renderer::Quad*);

            void draw();
    };
}

#endif // QUAD_H_INCLUDED
