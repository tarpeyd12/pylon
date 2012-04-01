#ifndef _QUAT_CLASS_H
#define _QUAT_CLASS_H

#include <stdio.h>

namespace POGEL
{
    class QUAT;
}

#include "matrix_class.h"
#include "point_class.h"
#include "../pogel_internals.h"

namespace POGEL
{
    class QUAT
    {
        public:
            float x;
            float y;
            float z;
            float w;

            QUAT();
            QUAT( float, float, float, float );

            QUAT( const POGEL::VECTOR &, float );
            QUAT( POGEL::MATRIX & );
            QUAT( POGEL::POINT );
            QUAT( float, float, float );

            POGEL::MATRIX tomatrix() const;

            POGEL::VECTOR getVector();

            void print();

            void normalize();

            POGEL::QUAT getConjugate() const;

            void getAxisAngle( POGEL::VECTOR *, float * );

            float dotproduct( const POGEL::QUAT & ) const;
            float dotproductself() const;

            POGEL::QUAT slerp( const POGEL::QUAT &, float ) const;

            POGEL::QUAT&   operator  = ( const POGEL::QUAT & );

            POGEL::QUAT    operator +  ( const POGEL::QUAT & ) const;
            POGEL::QUAT&   operator += ( const POGEL::QUAT & );

            POGEL::QUAT    operator *  ( float ) const;
            POGEL::QUAT&   operator *= ( float );

            POGEL::QUAT    operator /  ( float ) const;
            POGEL::QUAT&   operator /= ( float );

            POGEL::QUAT    operator *  ( const POGEL::QUAT & ) const;
            POGEL::QUAT&   operator *= ( const POGEL::QUAT & );

            POGEL::VECTOR  operator *  ( const POGEL::VECTOR & ) const;

    };
}

#endif /* _QUAT_CLASS_H */
