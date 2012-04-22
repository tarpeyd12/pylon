#include "physics.h"

namespace Renderer
{
    namespace Physics
    {
        ClassList<Simulation*> simulations;

        Simulation::Simulation(std::string n)
        {
            binding = NULL;
            name = n;
            sim = NULL;
            dyn = NULL;
            incrementable = false;
            drawable = false;
            clearobjects = false;
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
            binding = NULL;
            sim = s;
            sim->FORCEfastAccessList();
            dyn = NULL;
            name = n;
            incrementable = true;
            drawable = true;
            clearobjects = false;
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
            binding = NULL;
            sim = NULL;
            dyn = s;
            dyn->FORCEfastAccessList();
            name = n;
            incrementable = true;
            drawable = true;
            clearobjects = false;
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
            binding = NULL;
            incrementable = false;
            drawable = false;
            clearobjects = false;
            if(sim)
                delete sim;
            if(dyn)
                delete dyn;
            unsigned int numsimulations( simulations.length() );
            for(unsigned int i = 0; i < numsimulations; ++i)
            {
                if(simulations.get(i) == this)
                {
                    simulations.remove(i);
                    break;
                }
            }
        }

        void Simulation::setinc(bool i)
        {
            incrementable = i;
        }

        bool Simulation::canDrawBound()
        {
            return drawable;
        }

        bool Simulation::canDraw()
        {
            return drawable && NULL == binding;
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
            return incrementable && !clearobjects;
        }

        void* Simulation::getSim()
        {
            if(isdyn())
                return dyn;
            return sim;
        }

        POGEL::PHYSICS::SOLID* Simulation::getObject(std::string s)
        {
            if(clearobjects)
                return NULL;
            if(this->isdyn())
                return static_cast<POGEL::PHYSICS::DYNAMICS*>(this->getSim())->getSolid(s);
            else
                return static_cast<POGEL::PHYSICS::SIMULATION*>(this->getSim())->getSolid(s);
            return NULL;
        }

        std::string Simulation::getName()
        {
            return name;
        }

        bool Simulation::RequestToClearObjects()
        {
            drawable = false;
            clearobjects = true;
            return true;
        }

        bool Simulation::ClearObjects()
        {
            if(this->isdyn())
                static_cast<POGEL::PHYSICS::DYNAMICS*>(this->getSim())->clearAllSolids();
            else
                static_cast<POGEL::PHYSICS::SIMULATION*>(this->getSim())->clearAllSolids();
            drawable = true;
            clearobjects = false;
            return true;
        }

        bool Simulation::ShouldClearObjects()
        {
            return clearobjects;
        }

        void Simulation::draw()
        {
            if(this->isdyn())
                static_cast<POGEL::PHYSICS::DYNAMICS*>(this->getSim())->draw();
            else
                static_cast<POGEL::PHYSICS::SIMULATION*>(this->getSim())->draw();
        }

        bool Simulation::isEmpty()
        {
            if(this->isdyn())
                return !static_cast<POGEL::PHYSICS::DYNAMICS*>(this->getSim())->numobjs();
            else
                return !static_cast<POGEL::PHYSICS::SIMULATION*>(this->getSim())->numobjs();
            return false;
        }


        /*void Init()
        {

        }*/

        Renderer::Physics::Simulation* getSimulation(std::string name)
        {
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for(unsigned int i = 0; i < numsimulations; ++i)
                if(Renderer::Physics::simulations[i]->getName().length() == name.length() && Renderer::Physics::simulations[i]->getName().compare(name) == 0)
                    return Renderer::Physics::simulations[i];
            return NULL;
        }

        POGEL::PHYSICS::SOLID* getObject(std::string s, std::string o)
        {
            Renderer::Physics::Simulation* sim = getSimulation(s);
            if( sim == NULL )
                return NULL;
            return sim->getObject(o);
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


        void StopIncrimentation()
        {
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for(unsigned int i = 0; i < numsimulations; ++i)
            {
                Renderer::Physics::simulations.get(i)->setinc(false);
            }
        }

        void Incriment()
        {
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for(unsigned int i = 0; i < numsimulations; ++i)
            {
                if(Renderer::Physics::simulations[i]->inc())
                {
                    void* vp_sim = Renderer::Physics::simulations[i]->getSim();
                    if(Renderer::Physics::simulations[i]->isdyn())
                    {
                        POGEL::PHYSICS::DYNAMICS* sim = static_cast<POGEL::PHYSICS::DYNAMICS*>(vp_sim);
                        if(sim->numobjs())
                        {
                            sim->increment();
                        }
                    }
                    else
                    {
                        POGEL::PHYSICS::SIMULATION* sim = static_cast<POGEL::PHYSICS::SIMULATION*>(vp_sim);
                        if(sim->numobjs())
                        {
                            sim->increment();
                        }
                    }
                }
                else if(Renderer::Physics::simulations[i]->ShouldClearObjects())
                {
                    Renderer::Physics::simulations[i]->ClearObjects();
                }
            }
        }

        void cleanSimulations()
        {
            while( Renderer::Physics::simulations.length() )
            {
                Renderer::Physics::Simulation * sim = Renderer::Physics::simulations.get(Renderer::Physics::simulations.length()-1);
                if( !sim->isEmpty() )
                    sim->ClearObjects();
                delete sim;
            }
            Renderer::Physics::simulations.clear();
        }

    }
}
