#include "subrenderer.h"

#include <typeinfo>

#define DEFAULTRESOLUTION   256

#define DEFAULTRESOLUTIONX   DEFAULTRESOLUTION
#define DEFAULTRESOLUTIONY   DEFAULTRESOLUTION

#define DEFAULTFILTER       IMAGE_DEFAULT_FILTER
//#define DEFAULTFILTER       IMAGE_NEAREST

namespace Renderer
{
    ClassList<Renderer::SubRenderer*> subRenderers;

    SubRenderer::SubRenderer() : POGEL::VIEW()
    {
        setbgcolor(POGEL::COLOR(0.0f,0.0f,0.0f,0.0f));
        setviewport(0,0, DEFAULTRESOLUTIONX, DEFAULTRESOLUTIONY);
        setretscreensize(&Renderer::Window::Size::width, &Renderer::Window::Size::height);
        setfilter(DEFAULTFILTER);
        tstr = std::string("{(SubRenderer),[void]}");
        fileid = std::string("SubRenderer");
        camera = Renderer::Camera::Viewpoint();
        for(unsigned int i = 0; i < MAXNUMLIGHTS; ++i)
            lights[i] = Renderer::Lighting::Light();
        subRenderers += this;
        aspectratio = 0.0f;
    }

    SubRenderer::SubRenderer( const std::string& s ) : POGEL::VIEW()
    {
        setbgcolor(POGEL::COLOR(0.0f,0.0f,0.0f,0.0f));
        setviewport(0,0, DEFAULTRESOLUTIONX, DEFAULTRESOLUTIONY);
        setretscreensize(&Renderer::Window::Size::width, &Renderer::Window::Size::height);
        setfilter(DEFAULTFILTER);
        tstr = "{(SubRenderer),["+s+"]}";
        fileid = std::string("SubRenderer");
        camera = Renderer::Camera::Viewpoint();
        for(unsigned int i = 0; i < MAXNUMLIGHTS; ++i)
            lights[i] = Renderer::Lighting::Light();
        subRenderers += this;
        aspectratio = 0.0f;
    }

    SubRenderer::SubRenderer( const std::string& s, float ar ) : POGEL::VIEW()
    {
        setbgcolor(POGEL::COLOR(0.0f,0.0f,0.0f,0.0f));
        setviewport(0,0, DEFAULTRESOLUTIONX, DEFAULTRESOLUTIONY);
        setretscreensize(&Renderer::Window::Size::width, &Renderer::Window::Size::height);
        setfilter(DEFAULTFILTER);
        tstr = "{(SubRenderer),["+s+"]}";
        fileid = std::string("SubRenderer");
        camera = Renderer::Camera::Viewpoint();
        for(unsigned int i = 0; i < MAXNUMLIGHTS; ++i)
            lights[i] = Renderer::Lighting::Light();
        subRenderers += this;
        aspectratio = ar;
    }

    SubRenderer::~SubRenderer()
    {
        if( glIsTexture(base) )
        {
            glDeleteTextures(1, &base);
        }
        for(unsigned int i = 0; i < simulationBindings.length(); ++i)
            simulationBindings[i]->binding = NULL;
        simulationBindings.clear();
        for(unsigned int i = 0; i < MAXNUMLIGHTS; ++i)
            lights[i] = Renderer::Lighting::Light();
        for(unsigned int i = 0; i < subRenderers.length(); ++i)
        {
            if(subRenderers[i]->toString().compare(this->toString()) == 0)
            {
                subRenderers -= i;
            }
        }
    }

    void SubRenderer::setLight( const Renderer::Lighting::Light& l, int i)
    {
        if( i < 0 || i >= MAXNUMLIGHTS )
        {
            return;
        }
        lights[i] = l;
        lights[i].lightNumber = i;
    }

    Renderer::Physics::Simulation* SubRenderer::getBoundSimulation( const std::string& name )
    {
        for(unsigned int i = 0; i < simulationBindings.length(); ++i)
            if(simulationBindings[i]->getName().length() == name.length() && simulationBindings[i]->getName().compare(name) == 0)
                return simulationBindings[i];
        return NULL;
    }

    int SubRenderer::addSimulationBinding( const std::string& name )
    {
        Renderer::Physics::Simulation* sim = Renderer::Physics::getSimulation(name);
        if( sim == NULL )
            return -1;
        if( sim->binding != NULL && sim->binding != this )
            return -2;
        if( sim->binding == this )
            return -3;
        sim->binding = this;
        simulationBindings += sim;
        return simulationBindings.length()-1;
    }

    int SubRenderer::removeSimulationBinding( const std::string& name )
    {
        for(unsigned int i = 0; i < simulationBindings.length(); ++i)
            if( simulationBindings[i]->getName().compare(name) == 0 )
            {
                if(simulationBindings[i]->binding != this)
                {
                    simulationBindings -= i--;
                    continue;
                }
                simulationBindings[i]->binding = NULL;
                simulationBindings -= i;
                return i;
            }
        return -1;
    }

    int SubRenderer::removeAllSimulationBindings()
    {
        for(unsigned int i = 0; i < simulationBindings.length(); ++i)
        {
            simulationBindings[i]->binding = NULL;
        }
        simulationBindings.clear();
        return 0;
    }

    void SubRenderer::scenesetup()
    {

    }

    int __sortobjs(DataWraper<POGEL::PHYSICS::SOLID*,float>* a, DataWraper<POGEL::PHYSICS::SOLID*,float>* b)
    {
        if( a->value > b->value )
            return -1;
        return 1;
    }

    int __sorttris(DataWraper<POGEL::TRIANGLE,float>* a, DataWraper<POGEL::TRIANGLE,float>* b)
    {
        if( a->value < b->value )
            return -1;
        return 1;
    }

    POGEL::TRIANGLE * __accesstri( void * list, unsigned int index )
    {
        return &((DataWraper<POGEL::TRIANGLE,float>*)list)[ index ].data;
    }

    class __AccessTriangle
    {
        public:
            __AccessTriangle()
                { }
            inline POGEL::TRIANGLE * operator()( void * list, unsigned int index )
            {
                return &((DataWraper<POGEL::TRIANGLE,float>*)list)[ index ].data;
            }
    };

    template<class T>
    inline
    ClassList< DataWraper<POGEL::PHYSICS::SOLID*,float> >
    SubRenderer::__sortedDraw(T* sim)
    {
        POGEL::VECTOR refpos = this->globalTempRefpos;
        POGEL::POINT campos = this->globalTempCampos;
        POGEL::POINT invcampos = this->globalTempInvCampos;

        ClassList< DataWraper<POGEL::PHYSICS::SOLID*,float> > closelist( sim->numobjs() );

        bool label = POGEL::hasproperty(POGEL_LABEL);
        unsigned int numobjs = sim->numobjs();
        for(unsigned int i = 0; i < numobjs; ++i)
        {
            POGEL::PHYSICS::SOLID* obj = sim->objs(i);

            if(!obj->visable)
            {
                continue;
            }

            float objradius = obj->getbounding().maxdistance;
            float dst = refpos.dotproduct(campos + obj->position);

            // if the object is in fornt of the camera
            if( dst+objradius > 0.0f )
            {
                float dst2 = invcampos.distance(obj->position);

                if( dst2+objradius < 50.0f*objradius*1.0f )
                {
                    if( Renderer::Physics::doIncrimentSimulations && obj->getNumFrames() )
                    {
                        //obj->setAnimationTime( fmod(POGEL::GetTimePassed()*obj->getAnimationFPS(),float(obj->getNumFrames())) );
                        obj->playAnimation(POGEL::GetTimePassed());
                        //obj->setAnimationTime(1.0f);
                    }

                    bool autoinclude = false;//obj->hasOption(PHYSICS_SOLID_STATIONARY) || obj->hasproperty(OBJECT_SORT_TRIANGLES);

                    if( autoinclude )
                    {
                        float val = obj->getbounding().maxdistance + POGEL::VECTOR(obj->position).dotproduct(refpos);
                        closelist += DataWraper<POGEL::PHYSICS::SOLID*,float>(obj,val);
                        continue;
                    }
                }

                // if object is closer than 100 times its radius, recomend for sorting
                if( dst2+objradius < 100.0f*objradius*1.0f )
                {
                    float val = obj->getbounding().maxdistance + POGEL::VECTOR(obj->position).dotproduct(refpos);
                    closelist += DataWraper<POGEL::PHYSICS::SOLID*,float>(obj,val);
                }

                // otherwise if object is closer than 250 times its radius, just draw it
                else if( dst2+objradius < 250.0f*objradius*1.0f )
                {
                    obj->draw();
                }

                // otherwise if POGEL wants to draw center positions, do so.
                else if(label)
                {
                    obj->position.draw(2,obj->getLabelColor());
                }
            }
        }
        // return the list of recomended objects.
        return closelist;
    }

    void SubRenderer::RenderNormal()
    {
        POGEL::VECTOR refpos = this->globalTempRefpos = camera.GetCamDirection();
        POGEL::POINT campos = this->globalTempCampos = camera.position;
        POGEL::POINT invcampos = this->globalTempInvCampos = campos*-1.0;
        ClassList< DataWraper<POGEL::PHYSICS::SOLID*,float> > closelist;
        unsigned int numsimulations = simulationBindings.length();
        for( unsigned int i = 0; i < numsimulations; ++i )
        {
            if( !simulationBindings[ i ] )
            {
                continue;
            }
            if( simulationBindings[ i ]->canDrawBound() )
            {
                if( simulationBindings[ i ]->isdyn() )
                {
                    POGEL::PHYSICS::DYNAMICS* sim = static_cast<POGEL::PHYSICS::DYNAMICS*>(simulationBindings[i]->getSim());
                    closelist += __sortedDraw<POGEL::PHYSICS::DYNAMICS>(sim);
                }
                else
                {
                    POGEL::PHYSICS::SIMULATION* sim = static_cast<POGEL::PHYSICS::SIMULATION*>(simulationBindings[i]->getSim());
                    closelist += __sortedDraw<POGEL::PHYSICS::SIMULATION>(sim);
                }
            }
        }
        closelist.sort(__sortobjs);
        #ifndef SORTTRIANGLESPEROBJECT
        ClassList< DataWraper<POGEL::TRIANGLE,float> > gtrilist;
        ClassList< POGEL::TRIANGLE > gtrilist2;
        #endif
        for( unsigned int i = 0; i < closelist.length(); ++i )
        {
            POGEL::PHYSICS::SOLID* obj = closelist[i].data;
            if( !obj->hasproperty(OBJECT_SORT_TRIANGLES) && !obj->hasOption(PHYSICS_SOLID_STATIONARY) )
            {
                obj->draw();
                continue;
            }
            unsigned int p = obj->getproperties();
            obj->addproperty(OBJECT_DRAW_NOFACES);
            obj->draw();
            obj->setproperties(p);
            unsigned int numfaces = obj->getnumfaces();
            float objradius = obj->getbounding().maxdistance;
            ClassList< DataWraper<POGEL::TRIANGLE,float> > trilist(numfaces);
            ClassList< POGEL::TRIANGLE > trilist2(numfaces);
            unsigned int prp = POGEL::getproperties();
            if( POGEL::hasproperty(POGEL_BOUNDING) ) POGEL::removeproperty(POGEL_BOUNDING);
            for(unsigned int t = 0; t < numfaces;++t)
            {
                POGEL::TRIANGLE tri = obj->gettransformedtriangle(t);
                POGEL::POINT trimiddle = tri.middle();
                if( tri.hasproperty(TRIANGLE_DOUBLESIDED) || tri.isinfront(campos) )
                {
                    float tritocam = trimiddle.distance(campos);
                    if( ( tri.hasproperty(TRIANGLE_TRANSPARENT) || tri.isClear() ) && tritocam < objradius*50.0f*1.0f )
                    {
                        trilist += DataWraper<POGEL::TRIANGLE,float>(tri,tritocam);
                    }
                    else
                    {
                        trilist2 += tri;
                        //tri.draw();
                    }
                }
            }
            #ifndef SORTTRIANGLESPEROBJECT
            gtrilist2 += trilist2;
            gtrilist += trilist;
            #else
            POGEL::drawTriangleList( trilist2.getList(), trilist2.length() );
            trilist.sort(__sorttris);
            POGEL::drawTriangleList( (void*)trilist.getList() ,trilist.length(), __AccessTriangle() );
            #endif

            POGEL::setproperties(prp);
            trilist.clear();
            trilist2.clear();
        }
        #ifndef SORTTRIANGLESPEROBJECT
        POGEL::drawTriangleList( gtrilist2.getList(), gtrilist2.length() );
        gtrilist.sort(__sorttris);
        POGEL::drawTriangleList( (void*)gtrilist.getList() ,gtrilist.length(), __AccessTriangle() );
        gtrilist.clear();
        gtrilist2.clear();
        #endif
        closelist.clear();
    }

    void SubRenderer::RenderSimple()
    {
        POGEL::VECTOR refpos = this->globalTempRefpos = camera.GetCamDirection();
        POGEL::POINT campos = this->globalTempCampos = camera.position;
        POGEL::POINT invcampos = this->globalTempInvCampos = campos*-1.0;
        unsigned int numsimulations = simulationBindings.length();
        for( unsigned int i = 0; i < numsimulations; ++i )
        {
            Renderer::Physics::Simulation * sim = simulationBindings[ i ];
            if( !sim || !sim->numObjects() )
            {
                continue;
            }
            if( sim->canDrawBound() )
            {
                //sim->draw();
                unsigned int numobjects = sim->numObjects();
                for( unsigned int a = 0; a < numobjects; ++a )
                //unsigned int a = numobjects; while( a-- )
                {
                    POGEL::PHYSICS::SOLID* obj = sim->getObject( a );

                    if( !obj || !obj->visable )
                    {
                        continue;
                    }

                    float objradius = obj->getbounding().maxdistance;
                    float dst = refpos.dotproduct( campos + obj->position );

                    // if the object is not infornt of the camera
                    if( dst+objradius <= 0.0f )
                    {
                        // skip it
                        continue;
                    }

                    if( sim->inc() && Renderer::Physics::doIncrimentSimulations && obj->getNumFrames() && invcampos.distance(obj->position) + objradius < 50.0f*objradius*2.0f )
                    {
                        //obj->setAnimationTime( fmod(POGEL::GetTimePassed()*obj->getAnimationFPS(),float(obj->getNumFrames())) );
                        obj->playAnimation(POGEL::GetTimePassed());
                        //obj->setAnimationTime(1.0f);
                    }
                    obj->draw();
                }
            }
        }
    }

    void SubRenderer::scene()
    {
        if( !simulationBindings.length() )
        {
            return;
        }
        for(unsigned int i = 0; i < MAXNUMLIGHTS; ++i)
        {
            if( lights[ i ].inCameraSpace )
            {
                lights[ i ].draw();
            }
        }

        camera.set();

        for(unsigned int i = 0; i < MAXNUMLIGHTS; ++i)
        {
            if( !lights[ i ].inCameraSpace )
            {
                lights[ i ].draw();
            }
        }

        //RenderNormal();
        RenderSimple();

    }

    void SubRenderer::draw()
    {
        // Clear The Screen And The Depth Buffer
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();
        glPushMatrix();
        this->startrender();
        this->scene();
        glPopMatrix();
        this->endrender();
    }

    Renderer::SubRenderer* requestSubRenderer( const std::string& s )
    {
        unsigned int numsubrenderers = subRenderers.length();
        for( unsigned int i = 0; i < numsubrenderers; ++i )
        {
            Renderer::SubRenderer * subrend = subRenderers[ i ];
            if( !subrend )
            {
                continue;
            }
            if( subrend->toString().compare( s ) == 0 )
            {
                return subrend;
            }
        }
        return NULL;
    }

    void RenderAllSubRenderers()
    {
        unsigned int numsubrenderers = subRenderers.length();
        for( unsigned int i = 0; i < numsubrenderers; ++i )
        {
            Renderer::SubRenderer * subrend = subRenderers[ i ];
            if( !subrend )
            {
                continue;
            }
            if( !subrend->isbuilt() )
            {
                subrend->build();
            }
            subrend->draw();
        }
    }
}
