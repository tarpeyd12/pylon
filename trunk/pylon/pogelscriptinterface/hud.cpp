#include "hud.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{

    Object* addquad(Object* self, Object* args)
    {
        int corners[4];
        char* c_image;
        if(!PyArg_ParseTuple(args, "iiiis:addquad", &corners[0], &corners[1], &corners[2], &corners[3], &c_image))
            return NULL;
        POGEL::IMAGE* image = POGEL::requestImage(std::string(c_image));
        //delete c_image;
        Renderer::Quad* quad = new Renderer::Quad(corners[0], corners[1], corners[2], corners[3], image);
        int ret = Renderer::HUD::addQuad(quad);
        if(ret < 0)
        {
            delete quad;
            //return Py_BuildValue("s", "Unable to add Quad to HUD.");
        }
        //return Py_BuildValue("s", "Added Quad to HUD.");
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
