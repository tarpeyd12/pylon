#ifndef _BOUNDING_CLASS_H
#define _BOUNDING_CLASS_H

namespace POGEL
{
    class BOUNDING;
}

#include "point_class.h"
#include "misc_class.h"

#define             BOUNDING_DEFAULT                0
#define             BOUNDING_OBJECT                 1
#define             BOUNDING_TRIANGLE               2

#define             BOUNDING_DEFAULT_COLOR          POGEL::COLOR(0.0f,1.0f,1.0f,1.0f)
#define             BOUNDING_TRIANGLE_COLOR         POGEL::COLOR(0.0f,1.0f,0.0f,0.75f)
#define             BOUNDING_OBJECT_COLOR           POGEL::COLOR(1.0f,0.0f,1.0f,1.0f)

namespace POGEL
{
    class BOUNDING
    {
        private:
            unsigned long numpoints;
            bool isactual;
            float maxdistance2;
        public:
            float maxdistance;
            POGEL::POINT min;
            POGEL::POINT max;
            POGEL::COLOR color;

            BOUNDING();
            BOUNDING( unsigned int );
            BOUNDING( float, float, float, float, float, float, float );

            inline void set( float, float, float, float, float, float, float );

            inline void addpoint( const POGEL::POINT&, const POGEL::POINT& );
            inline void addpoint( const POGEL::POINT& );
            inline void fin( float f = 0.0f );

            inline void offset( const POGEL::POINT& );

            inline void clear();

            inline void finishactual();
            inline void unsetactual();

            void draw( const POGEL::POINT& ) const;
            void draw() const;

            inline bool checkbounding( const POGEL::POINT&, const POGEL::POINT&, const POGEL::BOUNDING& ) const;
            inline bool checkbounding( const POGEL::BOUNDING& ) const;

            inline bool isinside( const POGEL::POINT&, const POGEL::POINT& ) const;
            inline bool isoutside( const POGEL::POINT&, const POGEL::POINT& ) const;

            inline bool surrounds( const POGEL::POINT&, const POGEL::POINT&, const POGEL::BOUNDING& ) const;

            inline POGEL::BOUNDING& operator = ( const POGEL::BOUNDING& );
    };
}

#include "bounding_class_inline.h"

#endif /* _BOUNDING_CLASS_H */
