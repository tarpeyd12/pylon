
namespace POGEL
{
    template < class T >
    class OCTREE
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
        protected:

            #include "octree_template_protected_definition.h"

        public:

            OCTREE();
            OCTREE( OCTREE< T > * p, unsigned int lvl );
            OCTREE( OCTREE< T > * p );
            OCTREE( CLASSLIST< T * > * l, unsigned int lobj );
            OCTREE( CLASSLIST< T * > * l, unsigned int lobj, bool addbounds );
            OCTREE( CLASSLIST< T * > * l );

            inline float getDencity() const;
            inline void grow();

            #include "octree_template_general_public_definition.h"
    };
}

#include "octree_template_protected_implimentation.h"
#include "octree_template_general_implimentation.h"
#include "octree_template_general_public_implimentation.h"

