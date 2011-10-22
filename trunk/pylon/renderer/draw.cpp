#include "draw.h"

namespace Renderer
{
    namespace Draw
    {

        int __sortobjs(POGEL::PHYSICS::SOLID** a, POGEL::PHYSICS::SOLID** b)
        {
            POGEL::VECTOR av((*a)->position), bv((*b)->position);
            POGEL::VECTOR refpos = Renderer::Camera::GetCamDirection();
            if(av.dotproduct(refpos) < bv.dotproduct(refpos))
                return -1;
            return 1;
        }

        int __sorttris(POGEL::TRIANGLE* a, POGEL::TRIANGLE* b)
        {
            POGEL::VECTOR refpos = Renderer::Camera::GetCamDirection();
            POGEL::VECTOR av(a->vertex[0]+Renderer::Camera::campos);
            POGEL::VECTOR bv(b->vertex[0]+Renderer::Camera::campos);
            //float amin, bmin;
            for(int i = 1; i < 3; i++)
            {
                POGEL::VECTOR atmp(a->vertex[i]+Renderer::Camera::campos);
                float adst = atmp.dotproduct(refpos);
                if(av.dotproduct(refpos) < adst)
                    av = atmp;
                POGEL::VECTOR btmp(b->vertex[i]+Renderer::Camera::campos);
                float bdst = btmp.dotproduct(refpos);
                if(bv.dotproduct(refpos) < bdst)
                    bv = btmp;
            }
            if(av.dotproduct(refpos) <= bv.dotproduct(refpos))
                return -1;
            return 1;
        }


        template<class T>
        inline
        ClassList<POGEL::PHYSICS::SOLID*> __sortedDraw(T* sim)
        {
            POGEL::VECTOR refpos = Renderer::Camera::GetCamDirection();
            ClassList<POGEL::PHYSICS::SOLID*> closelist( sim->numobjs() );
            for(unsigned int i = 0; i < sim->numobjs(); i++)
            {
                POGEL::PHYSICS::SOLID* obj = sim->objs(i);
                float objradius = obj->getbounding().maxdistance;
                bool autoinclude = false;//objradius >= 10.0f || obj->hasOption(PHYSICS_SOLID_STATIONARY);// || obj->hasproperty(OBJECT_SORT_TRIANGLES);
                float dst = refpos.dotproduct(obj->position + Renderer::Camera::campos);
                // if the object is in fornt of the camera
                if( dst-objradius < 0.0f )
                {
                    if(autoinclude)
                    {
                        closelist += obj;
                        continue;
                    }
                    float dst2 = (Renderer::Camera::campos*-1).distance(obj->position);
                    if(dst2-objradius < 200.0f*objradius)
                        closelist += obj;
                    else if(dst2-objradius < 500.0f*objradius)
                        obj->draw();
                    else if(POGEL::hasproperty(POGEL_LABEL))
                        obj->position.draw(2,obj->getLabelColor());
                }
            }
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
                        POGEL::PHYSICS::DYNAMICS* sim = \
                        static_cast<POGEL::PHYSICS::DYNAMICS*> \
                        (Renderer::Physics::simulations[i]->getSim());
                        closelist += \
                        __sortedDraw<POGEL::PHYSICS::DYNAMICS>(sim);
                    }
                    else
                    {
                        POGEL::PHYSICS::SIMULATION* sim = \
                        static_cast<POGEL::PHYSICS::SIMULATION*> \
                        (Renderer::Physics::simulations[i]->getSim());
                        closelist += \
                        __sortedDraw<POGEL::PHYSICS::SIMULATION>(sim);
                    }
                }
            }
            closelist.sort(__sortobjs);
            ClassList<POGEL::TRIANGLE> trilist(closelist.length()*50);
            for(unsigned int i = 0; i < closelist.length(); i++)
            {
                POGEL::PHYSICS::SOLID* obj = closelist[i];
                if(!obj->hasproperty(OBJECT_SORT_TRIANGLES) && obj->getbounding().maxdistance < 10.0f)// || POGEL::GetFps() < 15.0f)
                {
                    obj->draw();
                }
                else
                {
                    POGEL::TRIANGLE* tritmplst = new POGEL::TRIANGLE[obj->getnumfaces()];
                    unsigned int len = 0;
                    for(unsigned int t = 0; t < obj->getnumfaces();t++)
                    {
                        POGEL::TRIANGLE tri = obj->gettransformedtriangle(t);
                        if(
                           tri.hasproperty(TRIANGLE_DOUBLESIDED) ||
                           tri.isinfront(Renderer::Camera::campos)
                        )
                        {
                            tritmplst[len++] = tri;
                        }
                    }
                    trilist.add(tritmplst,len);
                    delete[]tritmplst;
                }
            }
            closelist.safeclear();
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
                        POGEL::PHYSICS::DYNAMICS* sim = \
                        static_cast<POGEL::PHYSICS::DYNAMICS*> \
                        (Renderer::Physics::simulations[i]->getSim());
                        sim->draw();
                    }
                    else
                    {
                        POGEL::PHYSICS::SIMULATION* sim = \
                        static_cast<POGEL::PHYSICS::SIMULATION*> \
                        (Renderer::Physics::simulations[i]->getSim());
                        sim->draw();
                    }
                }
            }
        }

    }
}
