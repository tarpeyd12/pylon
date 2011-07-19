#include "quad.h"

namespace Renderer
{
    Quad::Quad()
    {
        image = NULL;
        for(unsigned int i = 0; i < 4; i++)
            verticies[i] = POGEL::VERTEX(0,0,0,0,0);
    }

    Quad::Quad(int x1, int y1, int x2, int y2, POGEL::IMAGE* img)
    {
        image = img;
        verticies[0] = POGEL::VERTEX(x1,y1,0, 0,0);
        verticies[1] = POGEL::VERTEX(x1,y2,0, 0,1);
        verticies[2] = POGEL::VERTEX(x2,y1,0, 1,0);
        verticies[3] = POGEL::VERTEX(x2,y2,0, 1,1);
    }

    Quad::~Quad()
    {
        image = NULL;
        for(unsigned int i = 0; i < children.length(); i++)
            delete children[i];
        children.clear();
    }

    void Quad::draw()
    {
        POGEL::TRIANGLE(verticies[0],verticies[1],verticies[2],image,0).draw();
        POGEL::TRIANGLE(verticies[2],verticies[1],verticies[3],image,0).draw();
        for(unsigned int i = 0; i < children.length(); i++)
            children[i]->draw();
    }
}
