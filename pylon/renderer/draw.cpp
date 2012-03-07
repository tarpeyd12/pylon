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

        int __sortobjs(POGEL::PHYSICS::SOLID** a, POGEL::PHYSICS::SOLID** b)
        {
            POGEL::VECTOR refpos = globalTempRefpos;
            POGEL::VECTOR av((*a)->position), bv((*b)->position);
            float adiff = (*a)->getbounding().maxdistance;
            float bdiff = (*b)->getbounding().maxdistance;
            float ar = av.dotproduct(refpos);
            float br = bv.dotproduct(refpos);
            if( ar+adiff > br+bdiff )
                return -1;
            return 1;
        }

        int __sorttris(POGEL::TRIANGLE* a, POGEL::TRIANGLE* b)
        {
            if( a->middle().distance(globalTempCampos) < b->middle().distance(globalTempCampos) )
                return -1;
            return 1;
        }

        template<class T>
        inline
        ClassList<POGEL::PHYSICS::SOLID*> __sortedDraw(T* sim)
        {
            POGEL::VECTOR refpos = globalTempRefpos;
            POGEL::POINT campos = globalTempCampos;
            POGEL::POINT invcampos = globalTempInvCampos;

            ClassList<POGEL::PHYSICS::SOLID*> closelist( sim->numobjs() );

            bool label = POGEL::hasproperty(POGEL_LABEL);
            unsigned int numobjs = sim->numobjs();
            for(unsigned int i = 0; i < numobjs; i++)
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
                    bool autoinclude = /*objradius >= 10.0f ||*/ obj->hasOption(PHYSICS_SOLID_STATIONARY);// || obj->hasproperty(OBJECT_SORT_TRIANGLES);

                    if( autoinclude )
                    {
                        closelist += obj;
                        continue;
                    }

                    float dst2 = invcampos.distance(obj->position);

                    // if object is closer than 100 times its diamiter, recomend for sorting
                    if(dst2+objradius < 100.0f*objradius*2.0f)
                        closelist += obj;
                    // otherwise if object is closer than 250 times its diamiter, just draw it
                    else if(dst2+objradius < 250.0f*objradius*2.0f)
                        obj->draw();
                    // otherwise if POGEL wants to draw center positions, do so.
                    else if(label)
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
            POGEL::POINT invcampos = globalTempInvCampos = campos*-1.0;
            ClassList<POGEL::PHYSICS::SOLID*> closelist;
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for(unsigned int i = 0; i < numsimulations; i++)
            {
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
            for(unsigned int i = 0; i < closelist.length(); i++)
            {
                POGEL::PHYSICS::SOLID* obj = closelist[i];
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
                ClassList<POGEL::TRIANGLE> trilist(numfaces);
                for(unsigned int t = 0; t < numfaces;t++)
                {
                    POGEL::TRIANGLE tri = obj->gettransformedtriangle(t);
                    if( tri.hasproperty(TRIANGLE_DOUBLESIDED) || tri.isinfront(campos) )
                    {
                        if( ( tri.hasproperty(TRIANGLE_TRANSPARENT) || tri.isClear() ) && tri.middle().distance(campos) < objradius*50.0*2.0 )
                            trilist += tri;
                        else
                            tri.draw();
                    }
                }
                trilist.sort(__sorttris);
                for(unsigned int i = 0; i < trilist.length(); i++)
                    trilist[i].draw();
                trilist.clear();
            }
            closelist.clear();
        }

        void PerfectDraw()
        {
            if(drawLock)
                return;
            POGEL::VECTOR refpos = globalTempRefpos = Renderer::Camera::GetCamDirection();
            POGEL::POINT campos = globalTempCampos = Renderer::Camera::campos;
            POGEL::POINT invcampos = globalTempInvCampos = campos*-1.0;
            ClassList<POGEL::PHYSICS::SOLID*> closelist;
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
                            if( refpos.getangle(POGEL::VECTOR(campos,obj->position).normal()) < 90.0f )
                                closelist += obj;
                        }
                    }
                    else
                    {
                        POGEL::PHYSICS::SIMULATION* sim = static_cast<POGEL::PHYSICS::SIMULATION*>(Renderer::Physics::simulations[i]->getSim());
                        unsigned int numobjs = sim->numobjs();
                        for(unsigned int o = 0; o < numobjs; o++)
                        {
                            POGEL::PHYSICS::SOLID* obj = sim->objs(o);
                            if( refpos.getangle(POGEL::VECTOR(campos,obj->position).normal()) < 90.0f )
                                closelist += obj;
                        }
                    }
                }
            }
            closelist.sort(__sortobjs);
            for(unsigned int i = 0; i < closelist.length(); i++)
            {
                ClassList<POGEL::TRIANGLE> trilist;
                POGEL::PHYSICS::SOLID* obj = closelist[i];
                unsigned int numfaces = obj->getnumfaces();
                for(unsigned int t = 0; t < numfaces;t++)
                {
                    POGEL::TRIANGLE tri = obj->gettransformedtriangle(t);
                    if( tri.hasproperty(TRIANGLE_DOUBLESIDED) || tri.isinfront(campos) )
                    {
                        if( ( tri.hasproperty(TRIANGLE_TRANSPARENT) || tri.isClear() ) )
                            trilist += tri;
                        else
                            tri.draw();
                    }
                }
                trilist.sort(__sorttris);
                for(unsigned int i = 0; i < trilist.length(); i++)
                    trilist[i].draw();
                trilist.safeclear();
            }
            closelist.safeclear();
        }

        void SimpleDraw()
        {
            if(drawLock)
                return;
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for(unsigned int i = 0; i < numsimulations; i++)
            {
                if(Renderer::Physics::simulations[i]->canDraw())
                {
                    Renderer::Physics::simulations[i]->draw();
                }
            }
        }

    }
}
