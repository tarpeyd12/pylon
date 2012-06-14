#include "keycallbacks.h"
#include "../pogel/pogel.h"

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{

    Object* key_callback_add_downfunc(Object* self, Object* args)
    {
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "ss:key_callback_add_downfunc", &inst, &func))
            return NULL;
        Renderer::Key::keyDownCallBacks += new KeyFunction(std::string(inst),std::string(func));
        return Py_BuildValue("i", (int)Renderer::Key::keyDownCallBacks.length()-1);
    }

    Object* key_callback_add_objdownfunc(Object* self, Object* args)
    {
        char* sim;
        char* obj;
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "ssss:key_callback_add_objdownfunc", &sim, &obj, &inst, &func))
            return NULL;
        Renderer::Key::keyDownCallBacks += new KeyObjectFunction( std::string(inst),std::string(func), std::string(sim), std::string(obj) );
        return Py_BuildValue("i", (int)Renderer::Key::keyDownCallBacks.length()-1);
    }

    Object* key_callback_remove_downfunc(Object* self, Object* args)
    {
        int keyfuncid;
        if(!PyArg_ParseTuple(args, "i:key_callback_remove_downfunc", &keyfuncid))
            return NULL;
        if( keyfuncid >= Renderer::Key::keyDownCallBacks.length() || keyfuncid < 0 )
        {
            return Py_BuildValue("i", -1);
        }
        Renderer::Key::KeyCallback * func = Renderer::Key::keyDownCallBacks[ keyfuncid ];
        //Renderer::Key::keyDownCallBacks.replace( keyfuncid, NULL );
        //delete func;
        func->remove = true;
        return Py_BuildValue("i", 0);
    }


    Object* key_callback_add_upfunc(Object* self, Object* args)
    {
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "ss:key_callback_add_upfunc", &inst, &func))
            return NULL;
        Renderer::Key::keyUpCallBacks += new KeyFunction(std::string(inst),std::string(func));
        return Py_BuildValue("i", (int)Renderer::Key::keyUpCallBacks.length()-1);
    }

    Object* key_callback_add_objupfunc(Object* self, Object* args)
    {
         char* sim;
        char* obj;
        char* inst;
        char* func;
        if(!PyArg_ParseTuple(args, "ssss:key_callback_add_objupfunc", &sim, &obj, &inst, &func))
            return NULL;
        Renderer::Key::keyUpCallBacks += new KeyObjectFunction( std::string(inst),std::string(func), std::string(sim), std::string(obj) );
        return Py_BuildValue("i", (int)Renderer::Key::keyUpCallBacks.length()-1);
    }

    Object* key_callback_remove_upfunc(Object* self, Object* args)
    {
        int keyfuncid;
        if(!PyArg_ParseTuple(args, "i:key_callback_remove_upfunc", &keyfuncid))
            return NULL;
        if( keyfuncid >= Renderer::Key::keyUpCallBacks.length() || keyfuncid < 0 )
        {
            return Py_BuildValue("i", -1);
        }
        Renderer::Key::KeyCallback * func = Renderer::Key::keyUpCallBacks[ keyfuncid ];
        //Renderer::Key::keyUpCallBacks.replace( keyfuncid, NULL );
        //delete func;
        func->remove = true;
        return Py_BuildValue("i", 0);
    }


    KeyFunction::KeyFunction()
    {

    }


    KeyFunction::KeyFunction( const std::string& inst, const std::string& func )
    {
        std::string args[4] = { "char:", "int:", "int:", "float:" };
        instructions = new ScriptEngine::FunctionCaller(inst,func,args,4);
    }

    KeyFunction::~KeyFunction()
    {

    }

    void KeyFunction::operator()( unsigned char key, int xpos, int ypos, float curtime )
    {
        char* tmp = NULL;
        std::string args[4] = { "char:", "int:", "int:", "float:" };
        tmp = POGEL::string("%c",key);
        args[ 0 ] += std::string(tmp);
        //delete [] tmp;
        tmp = POGEL::string("%d",xpos);
        args[ 1 ] += std::string(tmp);
        //delete [] tmp;
        tmp = POGEL::string("%d",ypos);
        args[ 2 ] += std::string(tmp);
        //delete [] tmp;
        tmp = POGEL::string("%0.2f",curtime);
        args[ 3 ] += std::string(tmp);
        //delete[]tmp;
        getInstructions()->setArgs(args,4);
        this->Execute();
    }

    KeyObjectFunction::KeyObjectFunction() : KeyFunction()
    {

    }

    KeyObjectFunction::KeyObjectFunction( const std::string& inst, const std::string& func, const std::string& sim, const std::string& obj ) : KeyFunction( inst, func )
    {
        simulation = sim;
        object = obj;
        std::string args[6] = { "char:", "int:", "int:", "float:", "str:", "str:" };
        getInstructions()->setArgs(args,6);
    }

    KeyObjectFunction::~KeyObjectFunction()
    {

    }

    void KeyObjectFunction::operator()( unsigned char key, int xpos, int ypos, float curtime )
    {
        char* tmp = NULL;
        std::string args[6] = { "char:", "int:", "int:", "float:", "str:", "str:" };
        tmp = POGEL::string("%c",key);
        args[ 0 ] += std::string(tmp);
        //delete [] tmp;
        tmp = POGEL::string("%d",xpos);
        args[ 1 ] += std::string(tmp);
        //delete [] tmp;
        tmp = POGEL::string("%d",ypos);
        args[ 2 ] += std::string(tmp);
        //delete [] tmp;
        tmp = POGEL::string("%0.2f",curtime);
        args[ 3 ] += std::string(tmp);
        //delete[]tmp;
        args[ 4 ] += simulation;
        args[ 5 ] += object;
        getInstructions()->setArgs(args,6);
        this->Execute();
    }
}
