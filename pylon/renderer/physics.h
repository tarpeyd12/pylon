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
                volatile bool incrementable;
                volatile bool drawable;
                volatile bool clearobjects;
                Threads::Mutex IncLock;
            protected:
                Renderer::SubRenderer* binding;
            public:
                Simulation( const std::string& );
                Simulation( const std::string&, POGEL::PHYSICS::SIMULATION* );
                Simulation( const std::string&, POGEL::PHYSICS::DYNAMICS* );
                ~Simulation();
                void setinc( bool );
                void setdraw( bool );
                bool canDrawBound() const;
                bool canDraw() const;
                bool isdyn() const;
                bool inc() const;
                void* getSim() const;
                bool AddObject( POGEL::PHYSICS::SOLID* );
                unsigned int numObjects() const;
                POGEL::PHYSICS::SOLID* getObject( const std::string& ) const;
                POGEL::PHYSICS::SOLID* getObject( unsigned int ) const;
                POGEL::OBJECT* getObject( const ClassList<std::string>& ) const;
                bool RemoveObject( const std::string& );
                std::string getName() const;
                bool RequestToClearObjects();
                bool ClearObjects();
                bool ClearObjectsNow();
                bool ShouldClearObjects() const;
                void draw() const;
                bool isEmpty() const;
                void Incriment();
                POGEL::PHYSICS::SOLID* getIntersected( const POGEL::POINT&, const POGEL::VECTOR& ) const;
                friend class Renderer::SubRenderer;
        };

        extern ClassList< Simulation * > simulations;

        extern volatile bool doIncrimentSimulations;

        //void Init();

        Renderer::Physics::Simulation* getSimulation( unsigned int );
        Renderer::Physics::Simulation* getSimulation( const std::string& );
        POGEL::PHYSICS::SOLID* getObject( const std::string&, const std::string& );
        POGEL::OBJECT* getObject( const std::string&, const ClassList<std::string>& );
        bool addSimulation( const std::string&, bool );

        void StopIncrimentation();
        void Incriment();
        void Incriment( int );

        void cleanSimulations();
    }
}

#endif // PHYSICS_H_INCLUDED
