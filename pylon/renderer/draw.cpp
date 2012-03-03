#include "draw.h"

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
            if( ar-adiff < br-bdiff )
            {
                return -1;
            }
            return 1;
        }

        int __sorttris(POGEL::TRIANGLE* a, POGEL::TRIANGLE* b)
        {
            POGEL::VECTOR refpos = globalTempRefpos;
            float ar = POGEL::VECTOR(a->middle()+globalTempCampos).dotproduct(refpos);
            float br = POGEL::VECTOR(b->middle()+globalTempCampos).dotproduct(refpos);
            if(ar < br)
            {
                return -1;
            }
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
                if( dst-objradius < 0.0f )
                {
                    bool autoinclude = /*objradius >= 10.0f ||*/ obj->hasOption(PHYSICS_SOLID_STATIONARY);// || obj->hasproperty(OBJECT_SORT_TRIANGLES);

                    if( autoinclude )
                    {
                        closelist += obj;
                        continue;
                    }

                    float dst2 = campos.distance(obj->position);

                    // if object is closer than 100 times its diamiter, recomend for sorting
                    if(dst2-objradius < 100.0f*objradius*2.0f)
                        closelist += obj;
                    // otherwise if object is closer than 250 times its diamiter, just draw it
                    else if(dst2-objradius < 250.0f*objradius*2.0f)
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
            ClassList<POGEL::TRIANGLE> trilist;
            unsigned int objslistlen = closelist.length();
            for(unsigned int i = 0; i < objslistlen; i++)
            {
                POGEL::PHYSICS::SOLID* obj = closelist[i];
                float objradius = obj->getbounding().maxdistance;
                if( /*trilist.length() >= 50 ||*/ (!obj->hasproperty(OBJECT_SORT_TRIANGLES) ) )//&& objradius < 10.0f) )
                {
                    obj->draw();
                }
                else
                {
                    unsigned int p = obj->getproperties();
                    obj->addproperty(OBJECT_DRAW_NOFACES);
                    obj->draw();
                    obj->setproperties(p);
                    unsigned int numfaces = obj->getnumfaces();
                    POGEL::TRIANGLE* tritmplst = new POGEL::TRIANGLE[numfaces];
                    POGEL::POINT refpos2 = campos + obj->position;
                    unsigned int len = 0;
                    for(unsigned int t = 0; t < numfaces; t++)
                    {
                        POGEL::TRIANGLE tri = obj->gettransformedtriangle(t);
                        POGEL::POINT trimiddle = tri.middle();
                        if( refpos.dotproduct(trimiddle + refpos2) < 0.0f )
                        {
                            if( tri.hasproperty(TRIANGLE_DOUBLESIDED) || tri.isinfront(refpos2) )
                            {
                                if( ( tri.hasproperty(TRIANGLE_TRANSPARENT) || tri.isClear() ) && trimiddle.distance(campos) < objradius*50.0*2.0 )
                                {
                                    tritmplst[len++] = tri;
                                }
                                else
                                {
                                    tri.draw();
                                }
                            }
                        }
                    }
                    if(len)
                        trilist.add(tritmplst,len);
                    delete[]tritmplst;
                }
            }
            closelist.safeclear();
            unsigned int trilistlength = trilist.length();
            if(trilistlength)
            {
                if(!POGEL::hasproperty(POGEL_WIREFRAME))
                    trilist.sort(__sorttris);
                for(unsigned int i = 0; i < trilistlength; i++)
                {
                    trilist[i].draw();
                }
                trilist.safeclear();
            }
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
                            if( refpos.dotproduct(obj->position + campos)-obj->getbounding().maxdistance < 0.0f )
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
                            if( refpos.dotproduct(obj->position + campos)-obj->getbounding().maxdistance < 0.0f )
                                closelist += obj;
                        }
                    }
                }
            }
            closelist.sort(__sortobjs);
            ClassList<POGEL::TRIANGLE> trilist;
            for(unsigned int i = 0; i < closelist.length(); i++)
            {
                POGEL::PHYSICS::SOLID* obj = closelist[i];
                unsigned int numfaces = obj->getnumfaces();
                POGEL::TRIANGLE* tritmplst = new POGEL::TRIANGLE[numfaces];
                unsigned int len = 0;
                for(unsigned int t = 0; t < numfaces;t++)
                {
                    POGEL::TRIANGLE tri = obj->gettransformedtriangle(t);
                    if( refpos.dotproduct(tri.middle() + campos) < 0.0 )
                        if( (tri.hasproperty(TRIANGLE_DOUBLESIDED) || tri.isinfront(campos)) && tri.isClear() )
                            tritmplst[len++] = tri;
                }
                if(len)
                    trilist.add(tritmplst,len);
                delete[]tritmplst;
            }
            trilist.sort(__sorttris);
            for(unsigned int i = 0; i < trilist.length(); i++)
                trilist[i].draw();
            closelist.safeclear();
            trilist.safeclear();
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
                    if(Renderer::Physics::simulations[i]->isdyn())
                    {
                        POGEL::PHYSICS::DYNAMICS* sim = static_cast<POGEL::PHYSICS::DYNAMICS*>(Renderer::Physics::simulations[i]->getSim());
                        sim->draw();
                    }
                    else
                    {
                        POGEL::PHYSICS::SIMULATION* sim = static_cast<POGEL::PHYSICS::SIMULATION*>(Renderer::Physics::simulations[i]->getSim());
                        sim->draw();
                    }
                }
            }
        }

    }
}
