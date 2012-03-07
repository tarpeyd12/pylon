#include "hud.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{

    Object* addquadi(Object* self, Object* args)
    {
        int corners[4];
        char* c_image;
        unsigned int p;
        if(!PyArg_ParseTuple(args, "iiiisi:addquad", &corners[0], &corners[1], &corners[2], &corners[3], &c_image, &p))
            return NULL;
        POGEL::IMAGE* image = Renderer::requestImage(std::string(c_image));
        Renderer::Quad* quad = new Renderer::Quad(corners[0], corners[1], corners[2], corners[3], image, p);
        int ret = Renderer::HUD::addQuad(quad);
        if(ret < 0)
        {
            delete quad;
        }
        return Py_BuildValue("i",ret);
    }

    Object* addquadf(Object* self, Object* args)
    {
        float corners[4];
        char* c_image;
        unsigned int p;
        if(!PyArg_ParseTuple(args, "ffffsi:addquad", &corners[0], &corners[1], &corners[2], &corners[3], &c_image, &p))
            return NULL;
        POGEL::IMAGE* image = Renderer::requestImage(std::string(c_image));
        Renderer::Quad* quad = new Renderer::Quad(corners[0], corners[1], corners[2], corners[3], image, p);
        int ret = Renderer::HUD::addQuad(quad);
        if(ret < 0)
        {
            delete quad;
        }
        return Py_BuildValue("i",ret);
    }

    Object* updatequadi(Object* self, Object* args)
    {
        int corners[4];
        char* c_image;
        unsigned int p;
        int quadID = -5;
        if(!PyArg_ParseTuple(args, "iiiisii:updatequad", &corners[0], &corners[1], &corners[2], &corners[3], &c_image, &p, &quadID))
            return NULL;
        POGEL::IMAGE* image = Renderer::requestImage(std::string(c_image));
        Renderer::Quad* quad = new Renderer::Quad(corners[0], corners[1], corners[2], corners[3], image, p);
        int ret = Renderer::HUD::updateQuad(quad, quadID);
        if(ret < 0)
        {
            delete quad;
        }
        return Py_BuildValue("i",ret);
    }

    Object* updatequadf(Object* self, Object* args)
    {
        float corners[4];
        char* c_image;
        unsigned int p;
        int quadID = -5;
        if(!PyArg_ParseTuple(args, "ffffsii:updatequad", &corners[0], &corners[1], &corners[2], &corners[3], &c_image, &p, &quadID))
            return NULL;
        POGEL::IMAGE* image = Renderer::requestImage(std::string(c_image));
        Renderer::Quad* quad = new Renderer::Quad(corners[0], corners[1], corners[2], corners[3], image, p);
        int ret = Renderer::HUD::updateQuad(quad, quadID);
        if(ret < 0)
        {
            delete quad;
        }
        return Py_BuildValue("i",ret);
    }

    Object* removequad(Object* self, Object* args)
    {
        int quadID = -5;
        if(!PyArg_ParseTuple(args, "i:removequad", &quadID))
            return NULL;
        int ret = Renderer::HUD::removeQuad(quadID);
        return Py_BuildValue("i", ret);
    }

    Object* clearquads(Object* self, Object* args)
    {
        if(!PyArg_ParseTuple(args, ":clearquads"))
            return NULL;
        Renderer::HUD::clearNextCycle = true;
        return Py_BuildValue("s", "HUD set to be cleared next draw cycle.");
    }

    Object* maxquads(Object* self, Object* args)
    {
        if(!PyArg_ParseTuple(args, ":maxquads"))
            return NULL;
        return Py_BuildValue("i", int(NUM_QUAD_SLOTS));
    }

    Object* checkquad(Object* self, Object* args)
    {
        int quadID = -5;
        if(!PyArg_ParseTuple(args, "i:checkquad", &quadID))
            return NULL;
        return Py_BuildValue("i", Renderer::HUD::checkQuad(quadID));
    }
}
