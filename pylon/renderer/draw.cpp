#include "draw.h"

#include "physics.h"

namespace Renderer
{
    namespace Draw
    {
        // these three variables are to 'simplify' the sorting process
        //  they are only calculated once per frame, then set to these variables
        //  instead of being calculated every time they are needed.
        POGEL::VECTOR globalTempRefpos;
        POGEL::POINT globalTempCampos;
        POGEL::POINT globalTempInvCampos;

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
        __sortedDraw(T* sim)
        {
            POGEL::VECTOR refpos( globalTempRefpos );
            POGEL::POINT campos( globalTempCampos );
            POGEL::POINT invcampos( globalTempInvCampos );

            unsigned int numobjs = sim->numobjs();

            ClassList< DataWraper<POGEL::PHYSICS::SOLID*,float> > closelist( numobjs );

            bool label = POGEL::hasproperty(POGEL_LABEL);

            for( unsigned int i = 0; i < numobjs; ++i )
            {
                POGEL::PHYSICS::SOLID* obj = sim->objs(i);

                if(!obj->visable)
                {
                    continue;
                }

                float objradius = obj->getbounding().maxdistance;
                float dst = refpos.dotproduct(campos + obj->position);

                // if the object is not infornt of the camera
                if( dst+objradius <= 0.0f )
                {
                    // skip it
                    continue;
                }

                float dst2 = invcampos.distance(obj->position) + objradius;

                if( dst2 < 50.0f*objradius*2.0f )
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

                // if object is closer than 100 times its diamiter, recomend for sorting
                if( dst2 < 100.0f*objradius*2.0f )
                {
                    float val = obj->getbounding().maxdistance + POGEL::VECTOR(obj->position).dotproduct(refpos);
                    closelist += DataWraper<POGEL::PHYSICS::SOLID*,float>(obj,val);
                    continue;
                }

                // otherwise if object is closer than 250 times its diamiter, just draw it
                else if( dst2 < 250.0f*objradius*2.0f )
                {
                    obj->draw();
                    continue;
                }

                // otherwise if POGEL wants to draw center positions, do so.
                else if( label )
                {
                    obj->position.draw(2,obj->getLabelColor());
                }
            }

            // return the list of recomended objects.
            return closelist;
        }

        void Draw()
        {
            if(drawLock)
                return;
            POGEL::VECTOR refpos = globalTempRefpos = Renderer::Camera::GetCamDirection();
            POGEL::POINT campos = globalTempCampos = Renderer::Camera::campos;
            POGEL::POINT invcampos = globalTempInvCampos = campos*-1.0f;
            ClassList< DataWraper<POGEL::PHYSICS::SOLID*,float> > closelist;
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for(unsigned int i = 0; i < numsimulations; ++i)
            {
                if( !Renderer::Physics::simulations[i] )
                {
                    continue;
                }
                if(Renderer::Physics::simulations[i]->canDraw())
                {
                    if(Renderer::Physics::simulations[i]->isdyn())
                    {
                        POGEL::PHYSICS::DYNAMICS* sim = static_cast<POGEL::PHYSICS::DYNAMICS*>(Renderer::Physics::simulations[i]->getSim());
                        closelist += __sortedDraw<POGEL::PHYSICS::DYNAMICS>(sim);
                    }
                    else
                    {
                        POGEL::PHYSICS::SIMULATION* sim = static_cast<POGEL::PHYSICS::SIMULATION*>(Renderer::Physics::simulations[i]->getSim());
                        closelist += __sortedDraw<POGEL::PHYSICS::SIMULATION>(sim);
                    }
                }
            }
            closelist.sort(__sortobjs);
            #ifndef SORTTRIANGLESPEROBJECT
            ClassList< DataWraper<POGEL::TRIANGLE,float> > gtrilist;
            ClassList< POGEL::TRIANGLE > gtrilist2;
            #endif
            for(unsigned int i = 0; i < closelist.length(); ++i)
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
                ClassList< DataWraper<POGEL::TRIANGLE,float> > trilist( numfaces );
                ClassList< POGEL::TRIANGLE > trilist2( numfaces );
                unsigned int prp = POGEL::getproperties();
                if( POGEL::hasproperty(POGEL_BOUNDING) )
                {
                    POGEL::removeproperty(POGEL_BOUNDING);
                }
                for( unsigned int t = 0; t < numfaces; ++t )
                {
                    POGEL::TRIANGLE tri = obj->gettransformedtriangle(t);
                    POGEL::POINT trimiddle = tri.middle();
                    if( tri.hasproperty(TRIANGLE_DOUBLESIDED) || tri.isinfront(campos) )
                    {
                        float tritocam = trimiddle.distance(campos);
                        if( ( tri.hasproperty(TRIANGLE_TRANSPARENT) || tri.isClear() ) && tritocam < objradius*50.0f*2.0f )
                        {
                            trilist += DataWraper<POGEL::TRIANGLE,float>(tri,tritocam);
                        }
                        else
                        {
                            //tri.draw();
                            trilist2 += tri;
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

        void PerfectDraw()
        {
            if(drawLock)
                return;
            POGEL::VECTOR refpos = globalTempRefpos = Renderer::Camera::GetCamDirection();
            POGEL::POINT campos = globalTempCampos = Renderer::Camera::campos;
            POGEL::POINT invcampos = globalTempInvCampos = campos*-1.0;
            ClassList< DataWraper<POGEL::PHYSICS::SOLID*,float> > closelist;
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for(unsigned int i = 0; i < numsimulations; i++)
            {
                if(Renderer::Physics::simulations[i]->canDraw())
                {
                    if(Renderer::Physics::simulations[i]->isdyn())
                    {
                        POGEL::PHYSICS::DYNAMICS* sim = static_cast<POGEL::PHYSICS::DYNAMICS*>(Renderer::Physics::simulations[i]->getSim());
                        unsigned int numobjs = sim->numobjs();
                        for(unsigned int o = 0; o < numobjs; o++)
                        {
                            POGEL::PHYSICS::SOLID* obj = sim->objs(o);
                            if( refpos.dotproduct(campos + obj->position)+obj->getbounding().maxdistance > 0.0f )
                            {
                                float val = obj->getbounding().maxdistance + POGEL::VECTOR(obj->position).dotproduct(refpos);
                                closelist += DataWraper<POGEL::PHYSICS::SOLID*,float>(obj,val);
                            }
                        }
                    }
                    else
                    {
                        POGEL::PHYSICS::SIMULATION* sim = static_cast<POGEL::PHYSICS::SIMULATION*>(Renderer::Physics::simulations[i]->getSim());
                        unsigned int numobjs = sim->numobjs();
                        for(unsigned int o = 0; o < numobjs; o++)
                        {
                            POGEL::PHYSICS::SOLID* obj = sim->objs(o);
                            if( refpos.dotproduct(campos + obj->position)+obj->getbounding().maxdistance > 0.0f )
                            {
                                float val = obj->getbounding().maxdistance + POGEL::VECTOR(obj->position).dotproduct(refpos);
                                closelist += DataWraper<POGEL::PHYSICS::SOLID*,float>(obj,val);
                            }
                        }
                    }
                }
            }
            closelist.sort(__sortobjs);
            for(unsigned int i = 0; i < closelist.length(); i++)
            {
                POGEL::PHYSICS::SOLID* obj = closelist[i].data;
                if( Renderer::Physics::doIncrimentSimulations && obj->getNumFrames() )
                {
                    //obj->setAnimationTime( fmod(POGEL::GetTimePassed()*obj->getAnimationFPS(),float(obj->getNumFrames())) );
                    obj->playAnimation(POGEL::GetTimePassed());
                    //obj->setAnimationTime(1.0f);
                }
                unsigned int numfaces = obj->getnumfaces();
                ClassList< DataWraper<POGEL::TRIANGLE,float> > trilist(numfaces);
                for(unsigned int t = 0; t < numfaces;t++)
                {
                    POGEL::TRIANGLE tri = obj->gettransformedtriangle(t);
                    if( tri.hasproperty(TRIANGLE_DOUBLESIDED) || tri.isinfront(campos) )
                    {
                        if( ( tri.hasproperty(TRIANGLE_TRANSPARENT) || tri.isClear() ) )
                        {
                            trilist += DataWraper<POGEL::TRIANGLE,float>(tri,tri.middle().distance(campos));
                        }
                        else
                        {
                            tri.draw();
                        }
                    }
                }
                trilist.sort(__sorttris);
                POGEL::drawTriangleList( (void*)trilist.getList() ,trilist.length(), __AccessTriangle() );
                trilist.clear();
            }
            closelist.clear();
        }

        void SimpleDraw()
        {
            if(drawLock)
                return;
            POGEL::VECTOR refpos = globalTempRefpos = Renderer::Camera::GetCamDirection();
            POGEL::POINT campos = globalTempCampos = Renderer::Camera::campos;
            POGEL::POINT invcampos = globalTempInvCampos = campos*-1.0;
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for(unsigned int i = 0; i < numsimulations; ++i)
            {
                if(Renderer::Physics::simulations[i]->canDraw())
                {
                    //Renderer::Physics::simulations[i]->draw();
                    unsigned int numobjects = Renderer::Physics::simulations[ i ]->numObjects();
                    for( unsigned int a = 0; a < numobjects; ++a )
                    //unsigned int a = numobjects; while( a-- )
                    {
                        POGEL::PHYSICS::SOLID* obj = Renderer::Physics::simulations[ i ]->getObject( a );

                        if( !obj->visable )
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

                        if( Renderer::Physics::doIncrimentSimulations && obj->getNumFrames() && invcampos.distance(obj->position) + objradius < 50.0f*objradius*2.0f )
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

        union colorIDstruct
        {
            unsigned char colorid[4];
            unsigned int idnum;
        };

        void PickDraw()
        {
            if( drawLock )
            {
                return;
            }
            POGEL::VECTOR refpos = globalTempRefpos = Renderer::Camera::GetCamDirection();
            POGEL::POINT campos = globalTempCampos = Renderer::Camera::campos;
            POGEL::POINT invcampos = globalTempInvCampos = campos * -1.0;

            unsigned int numsimulations = Renderer::Physics::simulations.length();

            unsigned int simid = 0;

            unsigned char colorid[4] = { 0, 0, 0, 0 };

            glDisable( GL_LIGHTING );
            glDisable( GL_TEXTURE_2D );
            glDisable( GL_BLEND );

            for( unsigned int i = 0; i < numsimulations; ++i )
            {
                ++simid;
                if( !Renderer::Physics::simulations[ i ]->canDraw() )
                {
                    continue;
                }

                colorid[ 0 ] = (unsigned char)(simid >> 8);
                colorid[ 1 ] = (unsigned char)(simid >> 0);

                unsigned int numobjects = Renderer::Physics::simulations[ i ]->numObjects();

                unsigned int objid = 0;

                for( unsigned int a = 0; a < numobjects; ++a )
                {
                    ++objid;
                    POGEL::PHYSICS::SOLID* obj = Renderer::Physics::simulations[ i ]->getObject( a );

                    if( !obj->visable )
                    {
                        continue;
                    }

                    float objradius = obj->getbounding().maxdistance;
                    float dst = refpos.dotproduct( campos + obj->position );

                    // if the object is not infornt of the camera
                    if( dst + objradius <= 0.0f )
                    {
                        // skip it
                        continue;
                    }

                    colorid[ 2 ] = (unsigned char)(objid >> 8);
                    colorid[ 3 ] = (unsigned char)(objid >> 0);

                    /*if( POGEL::hasproperty( POGEL_LABEL ) && dst > 250.0f*objradius )
                    {
                        glPointSize( 1 );
                        glColor4ub( colorid[ 0 ], colorid[ 1 ], colorid[ 2 ], colorid[ 3 ] );
                        glBegin( GL_POINTS );
                        glVertex3f( obj->position.x, obj->position.y, obj->position.z );
                        glEnd();
                        continue;
                    }*/

                    obj->drawColored( colorid );
                }
                //unsigned int simid = (colorid[0] << 8) | (colorid[1] << 0);
                //unsigned int objid = (colorid[2] << 8) | (colorid[3] << 0);
            }

            glEnable( GL_LIGHTING );
            glEnable( GL_TEXTURE_2D );
            glEnable( GL_BLEND );
            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
        }

    }
}
