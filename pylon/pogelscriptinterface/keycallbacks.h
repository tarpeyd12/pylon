#ifndef KEYCALLBACKS_H_INCLUDED
#define KEYCALLBACKS_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* key_callback_add_downfunc(Object*,Object*);
    Object* key_callback_add_objdownfunc(Object*,Object*);
    Object* key_callback_add_downfilters(Object*,Object*);
    Object* key_callback_remove_downfunc(Object*,Object*);

    Object* key_callback_add_upfunc(Object*,Object*);
    Object* key_callback_add_objupfunc(Object*,Object*);
    Object* key_callback_add_upfilters(Object*,Object*);
    Object* key_callback_remove_upfunc(Object*,Object*);

    class KeyFunction : public Renderer::Key::KeyCallback, public ScriptEngine::InterpreterThread
    {
        public:
            KeyFunction();
            KeyFunction( const std::string&, const std::string& );
            ~KeyFunction();
            virtual void operator()( unsigned char, int, int, float );
    };

    class KeyObjectFunction : public KeyFunction
    {
        private:
            std::string simulation;
            //std::string object;
            //Object* object;
            ClassList<std::string> * object;
        public:
            KeyObjectFunction();
            KeyObjectFunction( const std::string&, const std::string&, const std::string&, const std::string& );
            //KeyObjectFunction( const std::string&, const std::string&, const std::string&, Object* );
            ~KeyObjectFunction();
            virtual void operator()( unsigned char, int, int, float );
    };
}


#endif // KEYCALLBACKS_H_INCLUDED
