#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "../pogel/pogel.h"

namespace Renderer
{
    namespace Physics
    {
        class Simulation;
    }
}

#include "subrenderer.h"

#include "renderer.h"

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
                bool clearobjects;
            protected:
                Renderer::SubRenderer* binding;
            public:
                Simulation(std::string);
                Simulation(std::string,POGEL::PHYSICS::SIMULATION*);
                Simulation(std::string,POGEL::PHYSICS::DYNAMICS*);
                ~Simulation();
                void setinc(bool);
                bool canDrawBound();
                bool canDraw();
                bool isdyn();
                bool inc();
                void* getSim();
                POGEL::PHYSICS::SOLID* getObject(std::string);
                std::string getName();
                bool RequestToClearObjects();
                bool ClearObjects();
                bool ShouldClearObjects();
                void draw();
                friend class Renderer::SubRenderer;
        };

        extern ClassList<Simulation*> simulations;

        //void Init();

        Renderer::Physics::Simulation* getSimulation(std::string);
        POGEL::PHYSICS::SOLID* getObject(std::string,std::string);
        void addSimulation(std::string,bool);

        void StopIncrimentation();
        void Incriment();
    }
}

#endif // PHYSICS_H_INCLUDED
