#include "renderer.h"

#include "quad.h"

namespace Renderer
{
    Quad::Quad()
    {
        visable = true;
        properties = 0;
        image = NULL;
        for(unsigned int i = 0; i < 4; i++)
            verticies[i] = POGEL::VERTEX(0,0,0,0,0);
        triangles[0] = POGEL::TRIANGLE(verticies[0],verticies[1],verticies[2],image,properties|TRIANGLE_DOUBLESIDED);
        triangles[1] = POGEL::TRIANGLE(verticies[2],verticies[1],verticies[3],image,properties|TRIANGLE_DOUBLESIDED);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::Quad(int x1, int y1, int x2, int y2, POGEL::IMAGE* img)
    {
        visable = true;
        properties = 0;
        image = img;
        verticies[0] = POGEL::VERTEX(x1,y1,0.0f, 0.0f,0.0f);
        verticies[1] = POGEL::VERTEX(x1,y2,0.0f, 0.0f,1.0f);
        verticies[2] = POGEL::VERTEX(x2,y1,0.0f, 1.0f,0.0f);
        verticies[3] = POGEL::VERTEX(x2,y2,0.0f, 1.0f,1.0f);
        triangles[0] = POGEL::TRIANGLE(verticies[0],verticies[1],verticies[2],image,properties|TRIANGLE_DOUBLESIDED);
        triangles[1] = POGEL::TRIANGLE(verticies[2],verticies[1],verticies[3],image,properties|TRIANGLE_DOUBLESIDED);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::Quad(int x1, int y1, int x2, int y2, POGEL::IMAGE* img, unsigned int p)
    {
        visable = true;
        properties = p;
        image = img;
        verticies[0] = POGEL::VERTEX(x1,y1,0.0f, 0.0f,0.0f);
        verticies[1] = POGEL::VERTEX(x1,y2,0.0f, 0.0f,1.0f);
        verticies[2] = POGEL::VERTEX(x2,y1,0.0f, 1.0f,0.0f);
        verticies[3] = POGEL::VERTEX(x2,y2,0.0f, 1.0f,1.0f);
        triangles[0] = POGEL::TRIANGLE(verticies[0],verticies[1],verticies[2],image,properties|TRIANGLE_DOUBLESIDED);
        triangles[1] = POGEL::TRIANGLE(verticies[2],verticies[1],verticies[3],image,properties|TRIANGLE_DOUBLESIDED);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::Quad(float x1, float y1, float x2, float y2, POGEL::IMAGE* img)
    {
        visable = true;
        properties = 0;
        image = img;
        float w = float(Renderer::Window::Size::width);
        float h = float(Renderer::Window::Size::height);
        verticies[0] = POGEL::VERTEX(x1*w,y1*h,0.0f, 0.0f,0.0f);
        verticies[1] = POGEL::VERTEX(x1*w,y2*h,0.0f, 0.0f,1.0f);
        verticies[2] = POGEL::VERTEX(x2*w,y1*h,0.0f, 1.0f,0.0f);
        verticies[3] = POGEL::VERTEX(x2*w,y2*h,0.0f, 1.0f,1.0f);
        triangles[0] = POGEL::TRIANGLE(verticies[0],verticies[1],verticies[2],image,properties|TRIANGLE_DOUBLESIDED);
        triangles[1] = POGEL::TRIANGLE(verticies[2],verticies[1],verticies[3],image,properties|TRIANGLE_DOUBLESIDED);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::Quad(float x1, float y1, float x2, float y2, POGEL::IMAGE* img, unsigned int p)
    {
        visable = true;
        properties = p;
        image = img;
        float w = float(Renderer::Window::Size::width);
        float h = float(Renderer::Window::Size::height);
        verticies[0] = POGEL::VERTEX(x1*w,y1*h,0.0f, 0.0f,0.0f);
        verticies[1] = POGEL::VERTEX(x1*w,y2*h,0.0f, 0.0f,1.0f);
        verticies[2] = POGEL::VERTEX(x2*w,y1*h,0.0f, 1.0f,0.0f);
        verticies[3] = POGEL::VERTEX(x2*w,y2*h,0.0f, 1.0f,1.0f);
        triangles[0] = POGEL::TRIANGLE(verticies[0],verticies[1],verticies[2],image,properties|TRIANGLE_DOUBLESIDED);
        triangles[1] = POGEL::TRIANGLE(verticies[2],verticies[1],verticies[3],image,properties|TRIANGLE_DOUBLESIDED);
        children = NULL;//new CLASSLIST<Renderer::Quad*>();
    }

    Quad::~Quad()
    {
        visable = false;
        properties = 0;
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
        /*this->properties = other->properties;
        this->visable = other->visable;
        this->image = other->image;
        for(int i = 0; i < 4; ++i)
            this->verticies[i] = other->verticies[i];
        triangles[0] = POGEL::TRIANGLE(verticies[0],verticies[1],verticies[2],image,properties|TRIANGLE_DOUBLESIDED);
        triangles[1] = POGEL::TRIANGLE(verticies[2],verticies[1],verticies[3],image,properties|TRIANGLE_DOUBLESIDED);*/
        if(this->children != NULL)
        {
            for(unsigned int i = 0; i < this->children->length(); i++)
                delete this->children->get(i);
            delete this->children;
        }
        //this->children = other->children;
        memcpy(this,other,sizeof(*other));
        other->children = NULL;
    }

    void Quad::draw()
    {
        if(!visable)
        {
            return;
        }

        if( !triangles[ 0 ].settriangletexture() )
        {
            return;
        }
        triangles[ 0 ].initializetriangledraw();
        glBegin( GL_TRIANGLES );
        unsigned int p = POGEL::properties;
        if( p & POGEL_WIREFRAME )
        {
            POGEL::removeproperty( POGEL_WIREFRAME );
        }
        triangles[ 0 ].drawgeometry();
        triangles[ 1 ].drawgeometry();
        POGEL::properties = p;
        glEnd();
        triangles[ 1 ].finalizetriangledraw();

        if(this->children != NULL)
        {
            for(unsigned int i = 0; i < children->length(); ++i)
            {
                children->get(i)->draw();
            }
        }
    }
}
