#include "physics.h"

namespace Renderer
{
    namespace Physics
    {
        ClassList<Simulation*> simulations;

        Simulation::Simulation(std::string n)
        {
            name = n;
            sim = NULL;
            dyn = NULL;
            incrementable = false;
            drawable = false;
            bool in = false;
            for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
                if(Renderer::Physics::simulations[i] == this)
                {
                    in = true;
                    break;
                }
            if(!in)
                simulations.add(this);
        }

        Simulation::Simulation(std::string n, POGEL::PHYSICS::SIMULATION* s)
        {
            sim = s;
            sim->FORCEfastAccessList();
            dyn = NULL;
            name = n;
            incrementable = true;
            drawable = true;
            bool in = false;
            for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
                if(Renderer::Physics::simulations[i] == this)
                {
                    in = true;
                    break;
                }
            if(!in)
                simulations.add(this);
        }

        Simulation::Simulation(std::string n, POGEL::PHYSICS::DYNAMICS* s)
        {
            sim = NULL;
            dyn = s;
            dyn->FORCEfastAccessList();
            name = n;
            incrementable = true;
            drawable = true;
            bool in = false;
            for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
                if(Renderer::Physics::simulations[i] == this)
                {
                    in = true;
                    break;
                }
            if(!in)
                simulations.add(this);
        }

        Simulation::~Simulation()
        {
            incrementable = false;
            drawable = false;
            if(sim)
                delete sim;
            if(dyn)
                delete dyn;
            for(unsigned int i = 0; i < simulations.length(); i++)
                if(simulations[i] == this)
                {
                    simulations.remove(i);
                    break;
                }
        }

        void Simulation::setinc(bool i)
        {
            incrementable = i;
        }

        bool Simulation::canDraw()
        {
            return drawable;
        }

        bool Simulation::isdyn()
        {
            if(dyn != NULL && sim == NULL)
                return true;
            if(dyn == NULL && sim != NULL)
                return false;
            cout << "Simulation Type Handleing ERROR!" << endl;
            return false;
        }

        bool Simulation::inc()
        {
            return incrementable;
        }

        void* Simulation::getSim()
        {
            if(isdyn())
                return dyn;
            return sim;
        }

        std::string Simulation::getName()
        {
            return name;
        }

        Renderer::Physics::Simulation* getSimulation(std::string name)
        {
            for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
                if(Renderer::Physics::simulations[i]->getName().length() == name.length() && Renderer::Physics::simulations[i]->getName().compare(name) == 0)
                    return Renderer::Physics::simulations[i];
            return NULL;
        }

        void addSimulation(std::string name, bool col)
        {
            if(Renderer::Physics::getSimulation(name) != NULL)
                return;
            if(col)
                new Renderer::Physics::Simulation(name,new POGEL::PHYSICS::SIMULATION());
            else
                new Renderer::Physics::Simulation(name,new POGEL::PHYSICS::DYNAMICS());
        }

        template<class T>
        ClassList<POGEL::PHYSICS::SOLID*> __sortedDraw(T* sim)
        {
            POGEL::VECTOR refpos = Renderer::Camera::GetCamDirection();
            ClassList<POGEL::PHYSICS::SOLID*> closelist( sim->numobjs() );
            for(unsigned int i = 0; i < sim->numobjs(); i++)
            {
                POGEL::PHYSICS::SOLID* obj = sim->objs(i);
                float dst = refpos.dotproduct(obj->position + Renderer::Camera::campos);
                // if the object is in fornt of the camera
                if(dst < 0.0f)
                {
                    float dst2 = (Renderer::Camera::campos*-1).distance(obj->position);
                    if(dst2 < 10.0f)
                        closelist += obj;
                    else if(dst2 < 50.0f)
                        obj->draw();
                }
            }
            return closelist;
        }

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
            POGEL::VECTOR av(a->middle()+Renderer::Camera::campos);
            POGEL::VECTOR bv(b->middle()+Renderer::Camera::campos);
            if(av.dotproduct(refpos) <= bv.dotproduct(refpos))
                return -1;
            return 1;
        }

        void Draw()
        {
            if(!drawLock)
            {
                ClassList<POGEL::PHYSICS::SOLID*> closelist;
                for(unsigned int i = 0; i < Renderer::Physics::simulations.length(); i++)
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
                closelist.sort(__sortobjs);
                ClassList<POGEL::TRIANGLE> trilist;
                for(unsigned int i = 0; i < closelist.length(); i++)
                {
                    POGEL::PHYSICS::SOLID* obj = closelist[i];
                    if(!obj->hasproperty(OBJECT_SORT_TRIANGLES))
                        obj->draw();
                    else
                        for(unsigned int t = 0; t < obj->getnumfaces();t++)
                            trilist += obj->gettransformedtriangle(t);
                }
                trilist.sort(__sorttris);
                for(unsigned int i = 0; i < trilist.length(); i++)
                    trilist[i].draw();
                trilist.safeclear();
                closelist.safeclear();
            }
        }

    }
}
