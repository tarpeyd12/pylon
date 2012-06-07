#include <typeinfo>

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
    //POGEL::OBJECT * bob;

    Renderer::Timing::Timer* timer30;

    volatile bool DoExit = false;
    volatile int ExitValue = 0;

    volatile bool HaltPhysics = false;

    bool SingleThreaded = false;
    void (*SciptCall)(void) = NULL;

    // do not tamper with drawLock
    volatile bool drawLock = false;

    // *******************************

    void Idle()
    {
        if( Renderer::DoExit )
        {
            exit( Renderer::ExitValue );
        }

        if( POGEL::frames > 1 )
        {
            Renderer::BuildImages();
        }
        else
        {
            Renderer::BuildAllImages();
        }

        glutPostRedisplay();
    }

    void BuildImage(unsigned int i)
    {
        if( i >= POGEL::imglstlen() || !POGEL::lstimg(i) )
            return;

        POGEL::IMAGE* image = POGEL::lstimg(i);
        std::string fileid = image->getFileID();
        if(typeid(Renderer::SubRenderer*) == typeid(image) || fileid.compare("SubRenderer")==0)
        {
            if( !static_cast<Renderer::SubRenderer*>(image)->isbuilt() )
            {
                //static_cast<Renderer::SubRenderer*>(image)->build();
            }
            return;
        }
        if( POGEL::lstimg(i)->isbuilt() )
            return;
        bool fileexists = FileLoader::checkfile( fileid );
        if( !fileexists && !image->isloaded())
        {
            if(POGEL::hasproperty(POGEL_DEBUG))
                cout << "extracting: \"" << fileid << "\"" << endl;
            FileLoader::ArchiveHandler::extractKnownFile( fileid );
            fileexists = FileLoader::checkfile( fileid );
        }
        if( fileexists || image->isloaded())
        {
            if(POGEL::hasproperty(POGEL_DEBUG))
                cout << "building unbuilt image: \"" << image->toString() << "\"" << endl;
            if(image->isloaded())
                image->build();
            else
                image->loadandbuild();
            if( fileexists && !FileLoader::noremoval )
            {
                if(POGEL::hasproperty(POGEL_DEBUG))
                    cout << "removing: \"" << fileid << "\"" << endl;
                FileLoader::System::Files::remove( fileid );
            }
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

    POGEL::IMAGE* requestImage(std::string s)
    {
        Renderer::SubRenderer* subrend = Renderer::requestSubRenderer(s);
        if(subrend == NULL)
        {
            POGEL::IMAGE* image = POGEL::requestImage(s);
            if(image != NULL && !image->isloaded())
            {
                std::string fileid = image->getFileID();
                bool fileexists = FileLoader::checkfile( fileid );
                if( !fileexists )
                {
                    FileLoader::ArchiveHandler::extractKnownFile( fileid );
                    fileexists = FileLoader::checkfile( fileid );
                }
                if( fileexists )
                {
                    if( !image->load(fileid.c_str()) )
                    {
                        if( !FileLoader::noremoval )
                            FileLoader::System::Files::remove( fileid );
                        cout << "Error: " << fileid << " loading error" << endl;
                        throw -1;
                    }
                    if( !FileLoader::noremoval )
                        FileLoader::System::Files::remove( fileid );
                }
                else
                {
                    cout << "Error: " << fileid << " extracted, but nonexistant" << endl;
                    throw -2;
                }
            }
            return image;
        }
        return (POGEL::IMAGE*)subrend;
    }

}
