
#define T POGEL::PHYSICS::SOLID

namespace POGEL
{
    template <  >
    class OCTREE < POGEL::PHYSICS::SOLID >
    {
        private:
            CLASSLIST< T * > * allobjects;
            CLASSLIST< T * > objects;
            CLASSLIST< unsigned int > indicies;

            CLASSLIST< OCTREE< T > * > children;
            POGEL::OCTREE< T > * parent;

            POGEL::POINT position;
            POGEL::BOUNDING bounding;

            unsigned int level;
            unsigned int leastobjs;

            bool addboundings;

            float mass;
			bool masscenter_good, mass_good;
			POGEL::POINT masscenter;
			float theta;
        protected:

            #include "octree_template_protected_definition.h"

            float avgside() const;

        public:

            OCTREE();
            OCTREE( OCTREE< T > * p, unsigned int lvl );
            OCTREE( OCTREE< T > * p );
            OCTREE( CLASSLIST< T * > * l, unsigned int lobj );
            OCTREE( CLASSLIST< T * > * l, unsigned int lobj, bool addbounds );
            OCTREE( CLASSLIST< T * > * l );

            inline float getMass();
			inline float getDencity();

			inline void boolgrvs( bool * b ) const;
			inline void uintgrvs( unsigned int * b ) const;

			inline POGEL::POINT getmasscenter();

			inline bool objhaspos( const POGEL::POINT& p ) const;

			inline POGEL::VECTOR getpull( const POGEL::POINT& p, float m ) const;

			inline POGEL::VECTOR drawgetpull( const POGEL::POINT& p, float m ) const;

			inline void grow();

			// http://arborjs.org/docs/barnes-hut

            #include "octree_template_general_public_definition.h"
    };
}

#define USESOLID
#include "octree_template_protected_implimentation.h"
#include "octree_template_solid_implimentation.h"
//#include "octree_template_solid_public_implimentation.h"
#include "octree_template_general_public_implimentation.h"
#undef USESOLID
#ifdef T
#undef T
#endif

