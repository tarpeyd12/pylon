#include "quad.h"

namespace Renderer
{
    Quad::Quad()
    {
        image = NULL;
        for(unsigned int i = 0; i < 4; i++)
            verticies[i] = POGEL::VERTEX(0,0,0,0,0);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::Quad(int x1, int y1, int x2, int y2, POGEL::IMAGE* img)
    {
        image = img;
        verticies[0] = POGEL::VERTEX(x1,y1,0, 0,0);
        verticies[1] = POGEL::VERTEX(x1,y2,0, 0,1);
        verticies[2] = POGEL::VERTEX(x2,y1,0, 1,0);
        verticies[3] = POGEL::VERTEX(x2,y2,0, 1,1);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::~Quad()
    {
        image = NULL;
        if(this->children != NULL)
        {
            for(unsigned int i = 0; i < children->length(); i++)
                delete children->get(i);
            delete children;
        }
    }

    void Quad::set(Renderer::Quad* other)
    {
        this->image = other->image;
        for(int i = 0; i < 4; i++)
            this->verticies[i] = other->verticies[i];
        if(this->children != NULL)
        {
            for(unsigned int i = 0; i < this->children->length(); i++)
                delete this->children->get(i);
            delete this->children;
        }
        this->children = other->children;
        other->children = NULL;
    }

    void Quad::draw()
    {
        POGEL::TRIANGLE(verticies[0],verticies[1],verticies[2],image,0).draw();
        POGEL::TRIANGLE(verticies[2],verticies[1],verticies[3],image,0).draw();
        if(this->children != NULL)
            for(unsigned int i = 0; i < children->length(); i++)
                children->get(i)->draw();
    }
}
