#ifndef SELECTION_H_INCLUDED
#define SELECTION_H_INCLUDED

#include "renderer.h"

namespace Renderer
{
    namespace Selection
    {
        extern unsigned char * pixeldata;

        extern std::string lastsimname;
        extern std::string lastobjname;
        extern volatile bool lastwasselected;

        void Init( unsigned int, unsigned int );
        void Resize( unsigned int, unsigned int );

        void Retrieve();
        void RetrieveAt( unsigned int, unsigned int );
        void RetrieveAt( unsigned int, unsigned int, int*, int* );

        int GetSimulation( unsigned int, unsigned int );
        int GetObject( unsigned int, unsigned int );

        void DoMouseSelection();
    }
}

#endif // SELECTION_H_INCLUDED
