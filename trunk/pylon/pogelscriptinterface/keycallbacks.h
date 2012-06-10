#ifndef KEYCALLBACKS_H_INCLUDED
#define KEYCALLBACKS_H_INCLUDED

#ifndef POGELSCRIPTINTERFACE_H_INCLUDED
#include "pogelscriptinterface.h"
#endif // POGELSCRIPTINTERFACE_H_INCLUDED

using namespace ScriptEngine::MethodInterface;

namespace pogelInterface
{
    Object* key_callback_add_downfunc(Object*,Object*);
    Object* key_callback_remove_downfunc(Object*,Object*);

    Object* key_callback_add_upfunc(Object*,Object*);
    Object* key_callback_remove_upfunc(Object*,Object*);

    class KeyFunction : public Renderer::Key::KeyCallback, public ScriptEngine::InterpreterThread
    {
        public:
            KeyFunction();
            KeyFunction( const std::string&, const std::string& );
            ~KeyFunction();
            void operator()( unsigned char, int, int, float );
    };
}


#endif // KEYCALLBACKS_H_INCLUDED
