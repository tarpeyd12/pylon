#include "renderer.h"

#include "quad.h"

namespace Renderer
{
    Quad::Quad()
    {
        properties = 0;
        image = NULL;
        for(unsigned int i = 0; i < 4; i++)
            verticies[i] = POGEL::VERTEX(0,0,0,0,0);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::Quad(int x1, int y1, int x2, int y2, POGEL::IMAGE* img)
    {
        properties = 0;
        image = img;
        verticies[0] = POGEL::VERTEX(x1,y1,0.0f, 0.0f,0.0f);
        verticies[1] = POGEL::VERTEX(x1,y2,0.0f, 0.0f,1.0f);
        verticies[2] = POGEL::VERTEX(x2,y1,0.0f, 1.0f,0.0f);
        verticies[3] = POGEL::VERTEX(x2,y2,0.0f, 1.0f,1.0f);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::Quad(int x1, int y1, int x2, int y2, POGEL::IMAGE* img, unsigned int p)
    {
        properties = p;
        image = img;
        verticies[0] = POGEL::VERTEX(x1,y1,0.0f, 0.0f,0.0f);
        verticies[1] = POGEL::VERTEX(x1,y2,0.0f, 0.0f,1.0f);
        verticies[2] = POGEL::VERTEX(x2,y1,0.0f, 1.0f,0.0f);
        verticies[3] = POGEL::VERTEX(x2,y2,0.0f, 1.0f,1.0f);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::Quad(float x1, float y1, float x2, float y2, POGEL::IMAGE* img)
    {
        properties = 0;
        image = img;
        float w = float(Renderer::Window::Size::width);
        float h = float(Renderer::Window::Size::height);
        verticies[0] = POGEL::VERTEX(x1*w,y1*h,0.0f, 0.0f,0.0f);
        verticies[1] = POGEL::VERTEX(x1*w,y2*h,0.0f, 0.0f,1.0f);
        verticies[2] = POGEL::VERTEX(x2*w,y1*h,0.0f, 1.0f,0.0f);
        verticies[3] = POGEL::VERTEX(x2*w,y2*h,0.0f, 1.0f,1.0f);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::Quad(float x1, float y1, float x2, float y2, POGEL::IMAGE* img, unsigned int p)
    {
        properties = 0;
        image = img;
        float w = float(Renderer::Window::Size::width);
        float h = float(Renderer::Window::Size::height);
        verticies[0] = POGEL::VERTEX(x1*w,y1*h,0.0f, 0.0f,0.0f);
        verticies[1] = POGEL::VERTEX(x1*w,y2*h,0.0f, 0.0f,1.0f);
        verticies[2] = POGEL::VERTEX(x2*w,y1*h,0.0f, 1.0f,0.0f);
        verticies[3] = POGEL::VERTEX(x2*w,y2*h,0.0f, 1.0f,1.0f);
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
        this->properties = other->properties;
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
        POGEL::TRIANGLE(verticies[0],verticies[1],verticies[2],image,properties|TRIANGLE_DOUBLESIDED).draw();
        POGEL::TRIANGLE(verticies[2],verticies[1],verticies[3],image,properties|TRIANGLE_DOUBLESIDED).draw();
        if(this->children != NULL)
            for(unsigned int i = 0; i < children->length(); i++)
                children->get(i)->draw();
    }
}
