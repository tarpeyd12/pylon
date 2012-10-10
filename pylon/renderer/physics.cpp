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

        bool Simulation::AddObject( POGEL::PHYSICS::SOLID * obj )
        {
            if( !obj )
            {
                return false;
            }

            POGEL::PHYSICS::SOLID * pobj = NULL;

            if( this->isdyn() )
            {
                pobj = static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->getSolid( obj->getsname().c_str() );
            }
            else
            {
                pobj = static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->getSolid( obj->getsname().c_str() );
            }

            if( pobj )
            {
                return false;
            }

            IncLock.Lock();
            //int cl = Renderer::calcLockMutex.TryLock();
            Renderer::drawLockMutex.Lock();

            if( this->isdyn() )
            {
                static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->addSolid( obj );
            }
            else
            {
                static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->addSolid( obj );
            }
            IncLock.Unlock();
            //if(!cl)Renderer::calcLockMutex.Unlock();
            Renderer::drawLockMutex.Unlock();

            return true;
        }

        unsigned int Simulation::numObjects() const
        {
            /*if( clearobjects )
            {
                return 0;
            }*/
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
            if( clearobjects )
            {
                return NULL;
            }
            unsigned int numst = o.length();
            if( !numst )
            {
                return NULL;
            }
            POGEL::PHYSICS::SOLID * sl = this->getObject( o[0] );
            if( !sl )
            {
                cout << "Invalid Reference to Object" << endl;
                return NULL;
            }
            if( numst == 1 )
            {
                return (POGEL::OBJECT*)sl;
            }
            POGEL::OBJECT * ret = (POGEL::OBJECT*)sl;
            for( unsigned int i = 1; i < numst; ++i )
            {
                if( !o[i].size() )
                {
                    cout << "Invalid Object Reference List" << endl;
                    return NULL;
                }
                if( o[i].size() >= 2 && o[i].at(0) == ':' )
                {
                    ret = (POGEL::OBJECT*)ret->getdecendant( (const char*)(o[i].substr(1)).c_str() );
                }
                else
                {
                    ret = (POGEL::OBJECT*)ret->getchild( (const char*)o[i].c_str() );
                }
                if( !ret )
                {
                    cout << "Invalid Reference to Child Object" << endl;
                    return NULL;
                }
            }
            return (POGEL::OBJECT*)ret;
        }

        bool Simulation::RemoveObject( const std::string& sobj )
        {
            if( !sobj.length() )
            {
                return false;
            }

            POGEL::PHYSICS::SOLID * obj = NULL;

            if( this->isdyn() )
            {
                obj = static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->getSolid( sobj );
            }
            else
            {
                obj = static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->getSolid( sobj );
            }

            if( !obj )
            {
                return false;
            }

            IncLock.Lock();
            Renderer::drawLockMutex.Lock();
            //Renderer::calcLockMutex.TryLock();

            if( this->isdyn() )
            {
                static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->removeSolid( obj );
            }
            else
            {
                static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->removeSolid( obj );
            }

            delete obj;

            IncLock.Unlock();
            Renderer::drawLockMutex.Unlock();
            //Renderer::calcLockMutex.Unlock();

            return true;
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

        bool Simulation::ClearObjectsNow()
        {
            //Renderer::calcLockMutex.Lock();
            IncLock.Lock();
            Renderer::drawLockMutex.Lock();
            if( this->isdyn() )
            {
                static_cast<POGEL::PHYSICS::DYNAMICS*>( this->getSim() )->clearAllSolids();
            }
            else
            {
                static_cast<POGEL::PHYSICS::SIMULATION*>( this->getSim() )->clearAllSolids();
            }
            IncLock.Unlock();
            Renderer::drawLockMutex.Unlock();
            //Renderer::calcLockMutex.Unlock();
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

        void Simulation::Incriment()
        {
            IncLock.Lock();
            void* vp_sim = this->getSim();
            if( !vp_sim )
            {
                IncLock.Unlock();
                throw -10;
            }
            if( this->isdyn() )
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
            IncLock.Unlock();
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
            Renderer::drawLockMutex.Lock();
            Renderer::calcLockMutex.Lock();
            if( col )
            {
                new Renderer::Physics::Simulation( name, new POGEL::PHYSICS::SIMULATION() );
            }
            else
            {
                new Renderer::Physics::Simulation( name, new POGEL::PHYSICS::DYNAMICS() );
            }
            Renderer::drawLockMutex.Unlock();
            Renderer::calcLockMutex.Unlock();
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
            Renderer::calcLockMutex.Lock();
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            for( unsigned int i = 0; i < numsimulations; ++i )
            {
                Renderer::Physics::Simulation * sim = Renderer::Physics::simulations[ i ];
                if( doIncrimentSimulations && sim && sim->inc() )
                {
                    sim->Incriment();
                }
                else if( sim->ShouldClearObjects() )
                {
                    Renderer::drawLockMutex.Lock();
                    if( !sim->ClearObjects() )
                    {
                        cout << "ERROR could not clear all objects from simulation \"" << sim->getName() << "\"" << endl;
                    }
                    Renderer::drawLockMutex.Unlock();
                }
            }
            Renderer::calcLockMutex.Unlock();
        }

        class _IncrimentThread : public Threads::ExThread
        {
            private:
                Renderer::Physics::Simulation * sim;
            public:
                bool running;
                _IncrimentThread()
                {
                    running = false;
                    sim = NULL;
                }
                _IncrimentThread( Renderer::Physics::Simulation * s )
                {
                    running = false;
                    sim = s;
                }
                ~_IncrimentThread()
                {
                    running = false;
                    sim = NULL;
                }
                void Start( Renderer::Physics::Simulation * s )
                {
                    sim = s;
                    running = true;
                    this->startThread();
                }
                void Stop()
                {
                    this->joinThread();
                    running = false;
                }
                void run()
                {
                    if( sim )
                        sim->Incriment();
                }
        };

        void Incriment( int thn )
        {
            Renderer::calcLockMutex.Lock();
            unsigned int numsimulations = Renderer::Physics::simulations.length();
            ClassList< _IncrimentThread * > incthreads( thn );
            unsigned int thcount = 0;
            for( unsigned int i = 0; i < numsimulations; ++i )
            {
                Renderer::Physics::Simulation * sim = Renderer::Physics::simulations[ i ];
                if( doIncrimentSimulations && sim && sim->inc() )
                {
                    if( incthreads.length() < thn )
                    {
                        incthreads += new _IncrimentThread( sim );
                        incthreads.last()->Start( sim );
                    }
                    else
                    {
                        incthreads[ thcount % thn ]->Stop();
                        incthreads[ thcount % thn ]->Start( sim );
                    }
                    ++thcount;
                }
                else if( sim->ShouldClearObjects() )
                {
                    Renderer::drawLockMutex.Lock();
                    if( !sim->ClearObjects() )
                    {
                        cout << "ERROR could not clear all objects from simulation \"" << sim->getName() << "\"" << endl;
                    }
                    Renderer::drawLockMutex.Unlock();
                }
            }
            for( unsigned int i = 0; i < incthreads.length(); ++i )
            {
                incthreads[ i ]->Stop();
                delete incthreads[ i ];
            }
            incthreads.clear();
            Renderer::calcLockMutex.Unlock();
        }

        void cleanSimulations()
        {
            Renderer::drawLockMutex.Lock();
            Renderer::calcLockMutex.Lock();
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
            Renderer::drawLockMutex.Unlock();
            Renderer::calcLockMutex.Unlock();
        }

    }
}
