#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#ifndef RENDERER_H_INCLUDED
#include "renderer.h"
#endif // RENDERER_H_INCLUDED

namespace Renderer
{
    namespace Physics
    {
        class Simulation
        {
            private:
                std::string name;
                POGEL::PHYSICS::SIMULATION* sim;
                POGEL::PHYSICS::DYNAMICS* dyn;
                bool incrementable;
                bool drawable;
            public:
                Simulation(std::string);
                Simulation(std::string,POGEL::PHYSICS::SIMULATION*);
                Simulation(std::string,POGEL::PHYSICS::DYNAMICS*);
                ~Simulation();
                void setinc(bool);
                bool canDraw();
                bool isdyn();
                bool inc();
                void* getSim();
                std::string getName();
        };

        extern ClassList<Simulation*> simulations;

        Renderer::Physics::Simulation* getSimulation(std::string);
        void addSimulation(std::string,bool);

        void Draw();
    }
}

#endif // PHYSICS_H_INCLUDED