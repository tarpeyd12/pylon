#include "renderer.h"

#ifdef _POSIX_C_SOURCE
#undef _POSIX_C_SOURCE
#endif
#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#endif

//#include "../objectloader/objectloader.h"

//#include "../pogel/pogel.h"

#include "hud.h"

namespace Renderer
{
    // do not edit
    // *******************************
    POGEL::OBJECT* bob;
    //ObjectLoader::Object::_BaseObject* gr;

    Renderer::Timing::Timer* timer30;

    bool HaltPhysics = false;

    bool SingleThreaded = false;
    void (*SciptCall)(void) = NULL;

    // do not tamper with drawLock
    bool drawLock = false;

    // *******************************

    void Idle()
    {
        glutPostRedisplay();
        //cout << "Idle at frame: " << POGEL::frames << endl;
    }

    void BuildImage(unsigned int i)
    {
        if( i >= POGEL::imglstlen() || !POGEL::lstimg(i) || POGEL::lstimg(i)->isbuilt() )
            return;

        POGEL::IMAGE* image = POGEL::lstimg(i);
        std::string fileid = image->getFileID();

        if( !FileLoader::checkfile( fileid ) )
        {
            if(POGEL::hasproperty(POGEL_DEBUG))
                cout << "extracting: \"" << fileid << "\"" << endl;
            FileLoader::ArchiveHandler::extractKnownFile( fileid );
        }
        if( FileLoader::checkfile( fileid ) )
        {
            if(POGEL::hasproperty(POGEL_DEBUG))
                cout << "building unbuilt image: \"" << image->toString() << "\"" << endl;
            image->loadandbuild();
        }
        if( !FileLoader::noremoval && FileLoader::checkfile( fileid ) )
        {
            if(POGEL::hasproperty(POGEL_DEBUG))
                cout << "removing: \"" << fileid << "\"" << endl;
            FileLoader::System::Files::remove( fileid );
        }
    }

    void BuildImages()
    {
        if( POGEL::imglstlen() )
            BuildImage( POGEL::frames % POGEL::imglstlen() );
    }

    void BuildAllImages()
    {
        for(unsigned int i = 0; i < POGEL::imglstlen(); i++)
            BuildImage( i );
    }

}
