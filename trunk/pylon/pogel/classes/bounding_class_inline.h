void
POGEL::BOUNDING::set( float maximum, float gx, float lx, float gy, float ly, float gz, float lz)
{
    maxdistance = maximum;
    max.x = gx;
    min.x = lx;
    max.y = gy;
    min.y = ly;
    max.z = gz;
    min.z = lz;
    numpoints = 1;
    isactual = true;
}

void
POGEL::BOUNDING::addpoint( const POGEL::POINT& middle, const POGEL::POINT& point )
{
    if( isactual )
    {
        float dist = middle.distancesquared( point );
        if( dist > maxdistance * maxdistance )
        {
            maxdistance = (float)sqrt( dist );
        }

        /*float dist = middle.distance( point );
        if( dist > maxdistance )
        {
            maxdistance = dist;
        }*/
    }

    if( ++numpoints == 1 )
    {
        min = max = middle;
    }

    if( point.x > max.x ) { max.x = point.x; }
    else if( point.x < min.x ) { min.x = point.x; }

    if( point.y > max.y ) { max.y = point.y; }
    else if( point.y < min.y ) { min.y = point.y; }

    if( point.z > max.z ) { max.z = point.z; }
    else if( point.z < min.z ) { min.z = point.z; }
}

void
POGEL::BOUNDING::addpoint( const POGEL::POINT& p )
{
    addpoint( POGEL::POINT(), p );
}

void
POGEL::BOUNDING::fin( float f )
{
    // as fast as this is going to get
    if( f > 0.0f )
    {
        max.x+=f;
        max.y+=f;
        max.z+=f;

        min.x-=f;
        min.y-=f;
        min.z-=f;
    }
}

void
POGEL::BOUNDING::offset( const POGEL::POINT& offs )
{
    max += offs;
    min += offs;
}

void
POGEL::BOUNDING::clear()
{
    // chain smoking!
    maxdistance = max.x = min.x = max.y = min.y = max.z = min.z = 0.0f;
    numpoints = 0;
    isactual = true;
}

void
POGEL::BOUNDING::finishactual()
{
    isactual = false;
}

void
POGEL::BOUNDING::unsetactual()
{
    isactual = true;
}

bool
POGEL::BOUNDING::checkbounding( const POGEL::POINT& tsc, const POGEL::POINT& ttc, const POGEL::BOUNDING& tb ) const
{
    if( (tb.min.x+ttc.x <= max.x+tsc.x) && (tb.max.x+ttc.x >= min.x+tsc.x) )
    {
        if( (tb.min.y+ttc.y <= max.y+tsc.y) && (tb.max.y+ttc.y >= min.y+tsc.y) )
        {
            return (tb.min.z+ttc.z <= max.z+tsc.z) && (tb.max.z+ttc.z >= min.z+tsc.z);
        }
    }
    return false;
}

bool
POGEL::BOUNDING::checkbounding( const POGEL::BOUNDING& b ) const
{
    if( (b.min.x <= max.x) && (b.max.x >= min.x) )
    {
        if( (b.min.y <= max.y) && (b.max.y >= min.y) )
        {
            return (b.min.z <= max.z) && (b.max.z >= min.z);
        }
    }
    return false;
}

bool
POGEL::BOUNDING::isinside( const POGEL::POINT & tsc, const POGEL::POINT & p ) const
{
    if( (p.x <= max.x + tsc.x) && (p.x >= min.x + tsc.x) )
    {
        if( (p.y <= max.y + tsc.y) && (p.y >= min.y + tsc.y) )
        {
            return (p.z <= max.z + tsc.z) && (p.z >= min.z + tsc.z);
        }
    }
    return false;
}

bool
POGEL::BOUNDING::isoutside( const POGEL::POINT& tsc, const POGEL::POINT& p ) const
{
    bool x( (p.x >= max.x+tsc.x) || (p.x <= min.x+tsc.x) );
    bool y( (p.y >= max.y+tsc.y) || (p.y <= min.y+tsc.y) );
    bool z( (p.z >= max.z+tsc.z) || (p.z <= min.z+tsc.z) );
    return x || y || z;
}

bool
POGEL::BOUNDING::surrounds( const POGEL::POINT& tsc, const POGEL::POINT& ttc, const POGEL::BOUNDING& tb ) const
{
    return isinside( tsc, tb.min+ttc ) && isinside( tsc, tb.max+ttc );
}

POGEL::BOUNDING&
POGEL::BOUNDING::operator = ( const POGEL::BOUNDING& b )
{
    /*numpoints = b.numpoints;
    isactual = b.isactual;
    maxdistance = b.maxdistance;
    max = b.max;
    min = b.min;
    color = b.color;*/
    memcpy( this, &b, sizeof( b ) );
    return *this;
}
