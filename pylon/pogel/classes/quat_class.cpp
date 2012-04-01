#include "quat_class.h"

/*
 *  http://web.archive.org/web/20041029003853/http:/www.j3d.org/matrix_faq/matrfaq_latest.html
 *  http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
 *  http://en.wikipedia.org/wiki/Slerp
 *  http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
 *  http://number-none.com/product/Understanding%20Slerp,%20Then%20Not%20Using%20It/
 */

#define     TOLERANCE        0.00001f

POGEL::QUAT::QUAT()
{
    // set everything to zero
    x = y = z = w = 0.0f;
}

POGEL::QUAT::QUAT(float fx, float fy, float fz, float fw)
{
    // no brainer
    x = fx;
    y = fy;
    z = fz;
    w = fw;
}

POGEL::QUAT::QUAT( const POGEL::VECTOR & v, float angle )
{
    // construct the quaternion from an axis and an angle

    // take the input vector and normalize it(it is a const so we copy it to)
    POGEL::VECTOR vn(v);
    vn.normalize();

    // half the angle
    angle *= 0.5f;

    // so sin() is not called more than needed
    float sinAngle = sin(angle);

    // set the x, y, and z values to the respective values
    //  of the notrmalized vector, scalled bu sin(angle/2)
    x = (vn.x * sinAngle);
    y = (vn.y * sinAngle);
    z = (vn.z * sinAngle);
    // the last value in the quaternion is cos(angle/2)
    w = cos(angle);
}

POGEL::QUAT::QUAT( POGEL::MATRIX & mat )
{
    // creates a quaternion from a matrix

    // use the matrixes handy-dandy convert to quaternion method
    *this = mat.toquat();
}

POGEL::QUAT::QUAT( POGEL::POINT p )
{
    // Basically we create 3 Quaternions, one for pitch, one for yaw, one for roll
    // and multiply those together.
    // the calculation below does the same, just shorter

    /*float fp = DegreesToRadians(p.x) / 2.0f;
    float fy = DegreesToRadians(p.y) / 2.0f;
    float fr = DegreesToRadians(p.z) / 2.0f;*/

    float fp = (p.x) / 2.0f;
    float fy = (p.y) / 2.0f;
    float fr = (p.z) / 2.0f;

    float sinfp = sin(fp);
    float sinfy = sin(fy);
    float sinfr = sin(fr);
    float cosfp = cos(fp);
    float cosfy = cos(fy);
    float cosfr = cos(fr);

    x = sinfr * cosfp * cosfy - cosfr * sinfp * sinfy;
    y = cosfr * sinfp * cosfy + sinfr * cosfp * sinfy;
    z = cosfr * cosfp * sinfy - sinfr * sinfp * cosfy;
    w = cosfr * cosfp * cosfy + sinfr * sinfp * sinfy;

    normalize();
}

POGEL::QUAT::QUAT( float pitch, float yaw, float roll )
{
    // Basically we create 3 Quaternions, one for pitch, one for yaw, one for roll
    // and multiply those together.
    // the calculation below does the same, just shorter

    float fp = DegreesToRadians(pitch) / 2.0f;
    float fy = DegreesToRadians(yaw) / 2.0f;
    float fr = DegreesToRadians(roll) / 2.0f;

    float sinfp = sin(fp);
    float sinfy = sin(fy);
    float sinfr = sin(fr);
    float cosfp = cos(fp);
    float cosfy = cos(fy);
    float cosfr = cos(fr);

    x = sinfr * cosfp * cosfy - cosfr * sinfp * sinfy;
    y = cosfr * sinfp * cosfy + sinfr * cosfp * sinfy;
    z = cosfr * cosfp * sinfy - sinfr * sinfp * cosfy;
    w = cosfr * cosfp * cosfy + sinfr * sinfp * sinfy;

    normalize();
}

POGEL::MATRIX
POGEL::QUAT::tomatrix() const
{
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;
    float m[16];
    m[ 0] = 1.0f-2.0f*(y2+z2); m[ 4] = 2.0f*(xy-wz);      m[ 8] = 2.0f*(xz+wy);      m[12] = 0.0f;
    m[ 1] = 2.0f*(xy+wz);      m[ 5] = 1.0f-2.0f*(x2+z2); m[ 9] = 2.0f*(yz-wx);      m[13] = 0.0f;
    m[ 2] = 2.0f*(xz-wy);      m[ 6] = 2.0f*(yz+wx);      m[10] = 1.0f-2.0f*(x2+y2); m[14] = 0.0f;
    m[ 3] = 0.0f;              m[ 7] = 0.0f;              m[11] = 0.0f;              m[15] = 1.0f;

    /*m[ 0] = 1.0f-2.0f*(y2+z2); m[ 1] = 2.0f*(xy-wz);      m[ 2] = 2.0f*(xz+wy);      m[ 3] = 0.0f;
    m[ 4] = 2.0f*(xy+wz);      m[ 5] = 1.0f-2.0f*(x2+z2); m[ 6] = 2.0f*(yz-wx);      m[ 7] = 0.0f;
    m[ 8] = 2.0f*(xz-wy);      m[ 9] = 2.0f*(yz+wx);      m[10] = 1.0f-2.0f*(x2+y2); m[11] = 0.0f;
    m[12] = 0.0f;              m[13] = 0.0f;              m[14] = 0.0f;              m[15] = 1.0f;*/
    return POGEL::MATRIX(m);
}

POGEL::VECTOR
POGEL::QUAT::getVector()
{
    return POGEL::VECTOR(x, y, z);
}

void
POGEL::QUAT::print()
{
    POGEL::message( "%6.3f,%6.3f,%6.3f,%6.3f", x, y, z, w );
}

void
POGEL::QUAT::normalize()
{
    // Don't normalize if we don't have to
    float mag2 = dotproductself();
    if ( fabs(mag2) > TOLERANCE && fabs(mag2 - 1.0f) > TOLERANCE )
    {
        float mag = sqrt( mag2 );
        *this /= mag; // would this work?
        /*x /= mag;
        y /= mag;
        z /= mag;
        w /= mag;*/
    }
}

POGEL::QUAT
POGEL::QUAT::getConjugate() const
{
    // same but const
    return POGEL::QUAT( -x, -y, -z,  w );
}

void
POGEL::QUAT::getAxisAngle( POGEL::VECTOR * axis, float * angle )
{
    // convert the quaternion to axis and agnle rotation representation
    *axis = this->getVector().normal();
    *angle = acos(w) * 2.0f;
}

float
POGEL::QUAT::dotproduct(const POGEL::QUAT & q) const
{
    // the dotProduct of this quaternion agenst q
    return (x * q.x) + (y * q.y) + (z * q.z) + (w * q.w);
}

float
POGEL::QUAT::dotproductself() const
{
    // the dotProduct of this quaternion agenst itself
    return (x * x) + (y * y) + (z * z) + (w * w);
}

POGEL::QUAT
POGEL::QUAT::slerp(const POGEL::QUAT & in, float t) const
{
    POGEL::QUAT qt;
    POGEL::QUAT p = *this;
    POGEL::QUAT q = in;

    // decide if one of the quaternions is backwards
    float a = POGEL::QUAT(p.x-q.x,p.y-q.y,p.z-q.z,p.w-q.w).dotproductself();
    float b = POGEL::QUAT(p.x+q.x,p.y+q.y,p.z+q.z,p.w+q.w).dotproductself();

    // compare them
    if (a > b)
    {
        // ok it is backwards, reverse!
        q *= -1.0f;
        //q = q.getConjugate(); // I don't know if this is what should really happen
    }

    // get the dotProduct of q to itself
    float dot = p.dotproduct(q);

    // the rest of this I do not understand, F.Y.I.

    // check something
    if( (1.0f + dot) > TOLERANCE )
    {
        float scalep, scaleq;

        // check another thing
        if( (1.0f - dot) > TOLERANCE )
        {
            // do some confusing math
            float omega = acos( dot );
            float sinomega = sin( omega );
            scalep = sin( (1.0f - t) *omega ) / sinomega;
            scaleq = sin( t * omega ) / sinomega;
        }
        else
        {
            scalep = 1.0f - t;
            scaleq = t;
        }

        // set qt
        qt = p * scalep + q * scaleq;
    }
    else
    {
        // do something?
        //qt = POGEL::QUAT( -p.y, p.x, -p.w, p.z );

        // set qt
        qt = (p * sin( (1.0f - t) * 0.5f * PI )) + (POGEL::QUAT( -p.y, p.x, -p.w, p.z ) * sin( t * 0.5f * PI ));
    }

    // return the slurped Quaternion
    return qt;
}

POGEL::QUAT&
POGEL::QUAT::operator  = (const POGEL::QUAT & q)
{
    // set this quats values to that of q
    x = q.x;
    y = q.y;
    z = q.z;
    w = q.w;

    // return this
    return *this;
}

POGEL::QUAT
POGEL::QUAT::operator +  ( const POGEL::QUAT & q ) const
{
    // return a new quat like this one, but with all values
    //  respectively added with those of quat q
    return POGEL::QUAT( x + q.x, y + q.y, z + q.z, w + q.w );
}

POGEL::QUAT&
POGEL::QUAT::operator += ( const POGEL::QUAT & q )
{
    // add the respective values of q to this
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;

    // return this
    return *this;
}

POGEL::QUAT
POGEL::QUAT::operator *  ( float c ) const
{
    // return a new quat like this, but all values are scaled by constant c
    return POGEL::QUAT( x * c, y * c, z * c, w * c );
}

POGEL::QUAT&
POGEL::QUAT::operator *= ( float c )
{
    // multiply all values by constant c
    x *= c;
    y *= c;
    z *= c;
    w *= c;

    // return this
    return *this;
}

POGEL::QUAT
POGEL::QUAT::operator /  ( float c ) const
{
    // multiplication is usually faster than division(I think), so inverse, then multiply
    float c2 = 1.0f / c;

    // return a new quat like this, but all values are divided by constant c
    return POGEL::QUAT( x * c2, y * c2, z * c2, w * c2 );
}

POGEL::QUAT&
POGEL::QUAT::operator /= ( float c )
{
    // multiplication is usually faster than division(I think), so inverse, then multiply
    float c2 = 1.0f / c;

    // devide all values by constant c
    x *= c2;
    y *= c2;
    z *= c2;
    w *= c2;

    // return this
    return *this;
}

POGEL::QUAT
POGEL::QUAT::operator *  ( const POGEL::QUAT & rq) const
{
    // math that I dont understand
    // NOTE: QuatA*QuatB != QuatB*QuatA
    float fx = w * rq.x + x * rq.w + y * rq.z - z * rq.y;
    float fy = w * rq.y + y * rq.w + z * rq.x - x * rq.z;
    float fz = w * rq.z + z * rq.w + x * rq.y - y * rq.x;
    float fw = w * rq.w - x * rq.x - y * rq.y - z * rq.z;
    return POGEL::QUAT( fx, fy, fz, fw );
}

POGEL::QUAT&
POGEL::QUAT::operator *= ( const POGEL::QUAT & rq)
{
    // same math as above
    // NOTE: QuatA*QuatB != QuatB*QuatA, SO BE CAREFUL WHERE YOU USE THIS!
    // this quat is set to the quat rq transformed by this quat, I think?
    float fx = w * rq.x + x * rq.w + y * rq.z - z * rq.y;
    float fy = w * rq.y + y * rq.w + z * rq.x - x * rq.z;
    float fz = w * rq.z + z * rq.w + x * rq.y - y * rq.x;
    float fw = w * rq.w - x * rq.x - y * rq.y - z * rq.z;
    x = fx;
    y = fy;
    z = fz;
    w = fw;
    return *this;
}

POGEL::VECTOR
POGEL::QUAT::operator *  ( const POGEL::VECTOR & vec ) const
{
    // copy and normalize the input vector
    POGEL::VECTOR vn(vec);
    vn.normalize();

    // multiply the vector(as a quat) by this quat's conjugate
    POGEL::QUAT resQuat = POGEL::QUAT( vn.x, vn.y, vn.z, 0.0f ) * this->getConjugate();
    // transform resQuat(a vector) by this quaternion
    resQuat = (*this) * resQuat;
    // resQuat *= (*this); // might work, but: QuatA*QuatB != QuatB*QuatA, so maby not

    // return the transformed vector
    return resQuat.getVector();
}
