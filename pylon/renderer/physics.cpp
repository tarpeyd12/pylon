#include "physics.h"

namespace Renderer
{
    namespace Physics
    {
        CLASSLIST<Simulation*> simulations;

        Simulation::Simulation(std::string n, POGEL::PHYSICS::SIMULATION* s)
        {
            sim = s;
            sim->FORCEfastAccessList();
            dyn = NULL;
            name = n;
            incrementable = true;
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

        bool Simulation::isdyn()
        {
            return dyn != NULL && sim == NULL;
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
    }
}
