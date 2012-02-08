#include "draw.h"

namespace Renderer
{
    namespace Draw
    {

        int __sortobjs(POGEL::PHYSICS::SOLID** a, POGEL::PHYSICS::SOLID** b)
        {
            POGEL::VECTOR av((*a)->position), bv((*b)->position);
            POGEL::VECTOR refpos = Renderer::Camera::GetCamDirection();
            if( av.dotproduct(refpos) < bv.dotproduct(refpos) )
                return -1;
            return 1;
        }

        int __sorttris(POGEL::TRIANGLE* a, POGEL::TRIANGLE* b)
        {
            POGEL::VECTOR refpos = Renderer::Camera::GetCamDirection();
            POGEL::VECTOR av(a->middle()+Renderer::Camera::campos);
            POGEL::VECTOR bv(b->middle()+Renderer::Camera::campos);
            if(av.dotproduct(refpos) < bv.dotproduct(refpos))
                return -1;
            return 1;
        }

        template<class T>
        inline
        ClassList<POGEL::PHYSICS::SOLID*> __sortedDraw(T* sim)
        {
            POGEL::VECTOR refpos = Renderer::Camera::GetCamDirection();
            POGEL::POINT campos = Renderer::Camera::campos;
            POGEL::POINT invcampos = campos*-1.0;

            ClassList<POGEL::PHYSICS::SOLID*> closelist( sim->numobjs() );

            bool label = POGEL::hasproperty(POGEL_LABEL);
            unsigned int numobjs = sim->numobjs();

            for(unsigned int i = 0; i < numobjs; i++)
            {
                POGEL::PHYSICS::SOLID* obj = sim->objs(i);

                float objradius = obj->getbounding().maxdistance;
                float dst = refpos.dotproduct(obj->position + campos);

                // if the object is in fornt of the camera
                if( dst-objradius < 0.0f )
                {
                    if( false )
                    {

                        continue;
                    }

                    bool autoinclude = objradius >= 10.0f || obj->hasOption(PHYSICS_SOLID_STATIONARY);// || obj->hasproperty(OBJECT_SORT_TRIANGLES);

                    if( autoinclude )
                    {
                        closelist += obj;
                        continue;
                    }

                    float dst2 = obj->position.distance(invcampos);

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
            //closelist.sort(__sortobjs);
            // return the list of recomended objects.
            return closelist;
        }

        void Draw()
        {
            if(drawLock)
                return;
            ClassList<POGEL::PHYSICS::SOLID*> closelist;
            for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
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
            for(unsigned int i = 0; i < closelist.length(); i++)
            {
                POGEL::PHYSICS::SOLID* obj = closelist[i];
                float objradius = obj->getbounding().maxdistance;
                if(!obj->hasproperty(OBJECT_SORT_TRIANGLES) && objradius < 10.0f)// || POGEL::GetFps() < 15.0f)
                {
                    obj->draw();
                }
                else
                {
                    unsigned int numfaces = obj->getnumfaces();
                    POGEL::TRIANGLE* tritmplst = new POGEL::TRIANGLE[numfaces];
                    unsigned int len = 0;
                    POGEL::VECTOR refpos = Renderer::Camera::GetCamDirection();
                    POGEL::POINT campos = Renderer::Camera::campos;
                    POGEL::POINT invcampos = campos*-1.0;
                    for(unsigned int t = 0; t < numfaces;t++)
                    {
                        POGEL::TRIANGLE tri = obj->gettransformedtriangle(t);
                        POGEL::POINT trimiddle = tri.middle();
                        if( refpos.dotproduct(trimiddle + campos) < 0.0 )
                        {
                            if( tri.hasproperty(TRIANGLE_DOUBLESIDED) || tri.isinfront(campos) )
                            {
                                if( trimiddle.distance(invcampos) < objradius*50.0*2.0 )
                                    tritmplst[len++] = tri;
                                else tri.draw();
                            }
                        }
                    }
                    trilist.add(tritmplst,len);
                    delete[]tritmplst;
                }
            }
            closelist.safeclear();
            if(!POGEL::hasproperty(POGEL_WIREFRAME))
                trilist.sort(__sorttris);
            for(unsigned int i = 0; i < trilist.length(); i++)
            {
                trilist[i].draw();
            }
            trilist.safeclear();
        }

        void SimpleDraw()
        {
            if(drawLock)
                return;
            for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
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
