#ifndef RENDERER_KEY_H_INCLUDED
#define RENDERER_KEY_H_INCLUDED

#include "renderer.h"

namespace Renderer
{
    namespace Key
    {
        extern volatile bool keys[256];
        extern volatile float lastpressed[256];
        extern volatile float lastreleased[256];
        extern volatile int mousepospress[256][2];
        extern volatile int mouseposrelease[256][2];

        extern volatile char last;

        class KeyCallback
        {
            private:
                bool haskeyfilters;
                volatile bool keyfilter[256];
            public:
                bool remove;
                KeyCallback();
                virtual ~KeyCallback() { };
                bool hasKeyFilters() const;
                bool hasKeyFiltered(unsigned char ) const;
                void setKeyFilter( unsigned char, bool );
                virtual void operator()( unsigned char, int, int, float ) = 0;
        };

        extern ClassList< KeyCallback * > keyDownCallBacks;
        extern ClassList< KeyCallback * > keyUpCallBacks;

        void Down(unsigned char key, int x, int y);
        void Up(unsigned char key, int x, int y);
    }
}

#endif // RENDERER_KEY_H_INCLUDED
