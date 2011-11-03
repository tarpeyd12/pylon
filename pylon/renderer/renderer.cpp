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

    void BuildImages()
    {
        if(POGEL::imglstlen() > 0)
        {
            unsigned int i = POGEL::frames%POGEL::imglstlen();
            if(!POGEL::lstimg(i)->isbuilt())
            {
                if(!FileLoader::checkfile(POGEL::lstimg(i)->getFileID())) {
                    if(POGEL::hasproperty(POGEL_DEBUG))
                        cout << "extracting: \"" << POGEL::lstimg(i)->getFileID() << "\"" << endl;
                    FileLoader::ArchiveHandler::extractKnownFile(POGEL::lstimg(i)->getFileID());
                }
                if(FileLoader::checkfile(POGEL::lstimg(i)->getFileID()))
                {
                    if(POGEL::hasproperty(POGEL_DEBUG))
                        cout << endl << "building unbuilt image: \"" << POGEL::lstimg(i)->toString() << "\"" << endl;
                    POGEL::lstimg(i)->loadandbuild();
                }
                if( !FileLoader::noremoval && !FileLoader::checkfile(POGEL::lstimg(i)->getFileID()) ) {
                    if(POGEL::hasproperty(POGEL_DEBUG))
                        cout << "removing: \"" << POGEL::lstimg(i)->getFileID() << "\"" << endl;
                    FileLoader::System::Files::remove(POGEL::lstimg(i)->getFileID());
                }
            }
        }
    }

}
