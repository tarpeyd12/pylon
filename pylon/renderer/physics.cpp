#include "physics.h"

namespace Renderer
{
    namespace Physics
    {
        ClassList< Simulation * > simulations;

        volatile bool doIncrimentSimulations = true;

        Simulation::Simulation( const std::string& n )
        {
            binding = NULL;
            name = n;
            sim = NULL;
            dyn = NULL;
            incrementable = false;
            drawable = false;
            clearobjects = false;
            bool in = false;
            for( unsigned int i = 0; i < Renderer::Physics::simulations.length(); ++i )
            {
                if( Renderer::Physics::simulations[ i ] == this )
                {
                    in = true;
                    break;
                }
            }
            if( !in )
            {
                simulations.add(this);
            }
        }

        Simulation::Simulation( const std::string& n, POGEL::PHYSICS::SIMULATION * s )
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
            for( unsigned int i = 0; i < Renderer::Physics::simulations.length(); ++i )
            {
                if( Renderer::Physics::simulations[ i ] == this )
                {
                    in = true;
                    break;
                }
            }
            if( !in )
            {
                simulations.add(this);
            }
        }

        Simulation::Simulation( const std::string& n, POGEL::PHYSICS::DYNAMICS * s )
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
            for( unsigned int i = 0; i < Renderer::Physics::simulations.length(); ++i )
            {
                if( Renderer::Physics::simulations[ i ] == this )
                {
                    in = true;
                    break;
                }
            }
            if( !in )
            {
                simulations.add(this);
            }
        }

        Simulation::~Simulation()
        {
            binding = NULL;
            incrementable = false;
            drawable = false;
            clearobjects = false;
            if( sim )
            {
                delete sim;
            }
            else if( dyn )
            {
                delete dyn;
            }
            unsigned int numsimulations( Renderer::Physics::simulations.length() );
            for( unsigned int i = 0; i < numsimulations; ++i )
            {
                if( Renderer::Physics::simulations[ i ] == this )
                {
                    Renderer::Physics::simulations -= i;
                    break;
                }
            }
        }

        void Simulation::setinc( bool i )
        {
            incrementable = i;
        }

        void Simulation::setdraw( bool d )
        {
            drawable = d;
        }

        bool Simulation::canDrawBound() const
        {
            return drawable;
        }

        bool Simulation::canDraw() const
        {
            return drawable && NULL == binding;
        }

        bool Simulation::isdyn() const
        {
            if(dyn != NULL && sim == NULL)
            {
                return true;
            }
            if(dyn == NULL && sim != NULL)
            {
                return false;
            }
            cout << "ERROR Simulation Type failure (dyn == NULL && sim == NULL) evaluated to true" << endl;
            throw int(-1);
            return false;
        }

        bool Simulation::inc() const
        {
            return incrementable && !clearobjects;
        }

        void* Simulation::getSim() const
        {
            if( isdyn() )
            {
                return dyn;
            }
            return sim;
        }

        unsigned int Simulation::numObjects() const
        {
            if( clearobjects )
            {
                return 0;
            }
            if( this->isdyn() )
            {
                return static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->numobjs();
            }
            else
            {
                return static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->numobjs();
            }
            return 0;
        }

        POGEL::PHYSICS::SOLID* Simulation::getObject( const std::string& s ) const
        {
            if( clearobjects )
            {
                return NULL;
            }
            if( this->isdyn() )
            {
                return static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->getSolid( s );
            }
            else
            {
                return static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->getSolid( s );
            }
            return NULL;
        }

        POGEL::PHYSICS::SOLID* Simulation::getObject( unsigned int i ) const
        {
            if( clearobjects )
            {
                return NULL;
            }
            if( this->isdyn() )
            {
                return static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->objs( i );
            }
            else
            {
                return static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->objs( i );
            }
            return NULL;
        }

        POGEL::OBJECT* Simulation::getObject( const ClassList<std::string>& o ) const
        {
            unsigned int numst = o.length();
            if( !numst )
            {
                return NULL;
            }
            POGEL::PHYSICS::SOLID * sl = this->getObject( o[0] );
            if( !sl )
            {
                return NULL;
            }
            if( numst == 1 )
            {
                return (POGEL::OBJECT*)sl;
            }
            if( numst == 2 && o[1].size() && o[1].at(0) == ':' )
            {
                return (POGEL::OBJECT*)sl->getdecendant( (const char*)o[1].c_str() );
            }
            POGEL::OBJECT * ret = (POGEL::OBJECT*)sl;
            for( unsigned int i = 1; i < numst; ++i )
            {
                ret = (POGEL::OBJECT*)ret->getchild( (const char*)o[i].c_str() );
                if( !ret )
                {
                    return NULL;
                }
            }
            return (POGEL::OBJECT*)ret;
        }

        std::string Simulation::getName() const
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
            if( !clearobjects )
            {
                return false;
            }
            if( this->isdyn() )
            {
                static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->clearAllSolids();
            }
            else
            {
                static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->clearAllSolids();
            }
            drawable = true;
            clearobjects = false;
            return true;
        }

        bool Simulation::ShouldClearObjects() const
        {
            return clearobjects;
        }

        void Simulation::draw() const
        {
            if( this->isdyn() )
            {
                static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->draw();
            }
            else
            {
                static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->draw();
            }
        }

        bool Simulation::isEmpty() const
        {
            if( this->isdyn() )
            {
                return !static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->numobjs();
            }
            else
            {
                return !static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->numobjs();
            }
            return false;
        }

        POGEL::PHYSICS::SOLID* Simulation::getIntersected( const POGEL::POINT& origin, const POGEL::VECTOR& direction ) const
        {
            POGEL::PHYSICS::SOLID* ret = NULL;
            unsigned int numobjects = numObjects();
            float dist = 100000000.0f;
            POGEL::POINT col3d, col2d;
            POGEL::TRIANGLE tri;
            for( unsigned int i = 0; i < numobjects; ++i )
            {
                POGEL::PHYSICS::SOLID* current = getObject( i );

                float objradius = current->getbounding().maxdistance;
                float dst = direction.dotproduct( origin + current->position );

                if( dst + objradius <= 0.0f )
                {
                    continue;
                }

                bool hit = POGEL::PHYSICS::solid_ray_collision( PHYSICS_LINESOLID_COLLISION_LEAST, current, origin, direction, &tri, &col2d, &col3d );

                if( hit && col2d.z < dist )
                {
                    dist = col2d.z;
                    ret = current;
                }
            }
            return ret;
        }


        /*void Init()
        {

        }*/

        Renderer::Physics::Simulation* getSimulation( unsigned int i )
        {
            if( i >= Renderer::Physics::simulations.length() )
            {
                return NULL;
            }
            return Renderer::Physics::simulations[ i ];
        }

        Renderer::Physics::Simulation* getSimulation( const std::string& name )
        {
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for( unsigned int i = 0; i < numsimulations; ++i )
            {
                if( Renderer::Physics::simulations[ i ]->getName().compare( name ) == 0 )
                {
                    return Renderer::Physics::simulations[ i ];
                }
            }
            return NULL;
        }

        POGEL::PHYSICS::SOLID* getObject( const std::string& s, const std::string& o )
        {
            Renderer::Physics::Simulation* sim = getSimulation( s );
            if( sim == NULL )
            {
                return NULL;
            }
            return sim->getObject( o );
        }

        POGEL::OBJECT* getObject( const std::string& s, const ClassList<std::string>& o )
        {
            Renderer::Physics::Simulation * sim = getSimulation( s );
            if( !sim )
            {
                return NULL;
            }
            return sim->getObject( o );
        }

        bool addSimulation( const std::string& name, bool col )
        {
            if( Renderer::Physics::getSimulation( name ) )
            {
                return false;
            }
            if( col )
            {
                new Renderer::Physics::Simulation( name, new POGEL::PHYSICS::SIMULATION() );
            }
            else
            {
                new Renderer::Physics::Simulation( name, new POGEL::PHYSICS::DYNAMICS() );
            }
            return true;
        }


        void StopIncrimentation()
        {
            doIncrimentSimulations = false;
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for( unsigned int i = 0; i < numsimulations; ++i )
            {
                Renderer::Physics::simulations[ i ]->setinc( false );
            }
        }

        void Incriment()
        {
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for( unsigned int i = 0; i < numsimulations; ++i )
            {
                Renderer::Physics::Simulation * sim = Renderer::Physics::simulations[ i ];
                if( doIncrimentSimulations && sim && sim->inc() )
                {
                    void* vp_sim = sim->getSim();
                    if( !vp_sim )
                    {
                        throw -10;
                    }
                    if( sim->isdyn() )
                    {
                        POGEL::PHYSICS::DYNAMICS* dsim = static_cast<POGEL::PHYSICS::DYNAMICS*>( vp_sim );
                        if( dsim->numobjs() )
                        {
                            dsim->increment();
                        }
                        dsim = NULL;
                    }
                    else
                    {
                        POGEL::PHYSICS::SIMULATION* ssim = static_cast<POGEL::PHYSICS::SIMULATION*>( vp_sim );
                        if( ssim->numobjs() )
                        {
                            ssim->increment();
                        }
                        ssim = NULL;
                    }
                    vp_sim = NULL;
                }
                else if( sim->ShouldClearObjects() )
                {
                    if( !sim->ClearObjects() )
                    {
                        cout << "ERROR could not clear all objects from simulation \"" << sim->getName() << "\"" << endl;
                    }
                }
            }
        }

        void cleanSimulations()
        {
            while( Renderer::Physics::simulations.length() )
            {
                Renderer::Physics::Simulation * sim = Renderer::Physics::simulations.get( Renderer::Physics::simulations.length() - 1 );
                if( !sim->isEmpty() )
                {
                    sim->RequestToClearObjects();
                    if( !sim->ClearObjects() )
                    {
                        cout << "ERROR could not clear all objects from simulation \"" << sim->getName() << "\"" << endl;
                    }
                }
                delete sim;
            }
            Renderer::Physics::simulations.clear();
        }

    }
}
