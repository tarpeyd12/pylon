
template < class T >
POGEL::OCTREE< T >::OCTREE()
{
    leastobjs = defleastobjs;
    parent = NULL;
    allobjects = NULL;
    level = 0;
    addboundings = true;
}

template < class T >
POGEL::OCTREE< T >::OCTREE( OCTREE< T > * p, unsigned int lvl )
{
    leastobjs = p->leastobjs;
    allobjects = p->allobjects;
    parent = p;
    level = lvl;
    addboundings = true;
}

template < class T >
POGEL::OCTREE< T >::OCTREE( OCTREE< T > * p )
{
    leastobjs = p->leastobjs;
    allobjects = p->allobjects;
    addboundings = p->addboundings;
    parent = p;
    level = p->level + 1;
}

template < class T >
POGEL::OCTREE< T >::OCTREE( CLASSLIST< T * > * l, unsigned int lobj )
{
    addboundings = true;
    leastobjs = lobj > 1 ? lobj : 1;
    allobjects = l;
    parent = NULL;
    level = 0;
    objects.add( l );
    unsigned int numobjects = objects.length();
    if( numobjects )
    {
    	position = objects[ 0 ]->getposition();
    }
    for( unsigned int i = 0; i < numobjects; ++i )
    {
        if(addboundings)
        {
            bounding.addpoint( objects[ i ]->getbounding().max );
            bounding.addpoint( objects[ i ]->getbounding().min );
        }
        else
        {
            bounding.addpoint( getposition(), objects[ i ]->getposition() );
		}
        indicies += i;
    }
    position = ( getbounding().max + getbounding().min ) / 2.0f;
}

template < class T >
POGEL::OCTREE< T >::OCTREE( CLASSLIST< T * > * l, unsigned int lobj, bool addbounds )
{
    addboundings = addbounds;
    leastobjs = lobj > 1 ? lobj : 1;
    allobjects = l;
    parent = NULL;
    level = 0;
    objects.add( l );
    unsigned int numobjects = objects.length();
    if( numobjects )
    {
    	position = objects[ 0 ]->getposition();
    }
    if(addboundings)
    {
        for( unsigned int i = 0; i < numobjects; ++i )
        {
            POGEL::BOUNDING bound = objects[ i ]->getbounding();
            bounding.addpoint( bound.max );
            bounding.addpoint( bound.min );
            indicies += i;
        }
    }
    else
    {
        for( unsigned int i = 0; i < numobjects; ++i )
        {
            bounding.addpoint( getposition(), objects[ i ]->getposition() );
            indicies += i;
        }

    }
    position = ( getbounding().max + getbounding().min ) / 2.0f;
}

template < class T >
POGEL::OCTREE< T >::OCTREE(CLASSLIST< T * > * l)
{
    addboundings = true;
    leastobjs = defleastobjs;
    allobjects = l;
    parent = NULL;
    level = 0;
    objects.add( l );
    unsigned int numobjects = objects.length();
    if( numobjects )
    {
    	position = objects[ 0 ]->getposition();
    }
    if(addboundings)
    {
        for( unsigned int i = 0; i < numobjects; ++i )
        {
            POGEL::BOUNDING bound = objects[ i ]->getbounding();
            bounding.addpoint( bound.max );
            bounding.addpoint( bound.min );
            indicies += i;
        }
    }
    else
    {
        for( unsigned int i = 0; i < numobjects; ++i )
        {
            bounding.addpoint( getposition(), objects[ i ]->getposition() );
            indicies += i;
        }

    }
    position = ( getbounding().max + getbounding().min ) / 2.0f;
}

template < class T >
float
POGEL::OCTREE< T >::getDencity() const
{
    if( getbounding().min != getbounding().max )
    {
        POGEL::VECTOR v( getbounding().max, getbounding().min );
        return float( objects.length() ) / ( (v.x?v.x:1.0f) * (v.y?v.y:1.0f) * (v.z?v.z:1.0f) );
    }
    return 0.0f;
}

template < class T >
void
POGEL::OCTREE< T >::grow()
{
	if( !( objects.length() > leastobjs && level < maxlevels && children.length() < maxchildren ) )
	{
		return;
	}
	while( children.length() < maxchildren && level < maxlevels )
	{
		children += new POGEL::OCTREE< T >( this );
	}
	POGEL::POINT thispos = getposition();
	for( unsigned int i = 0; i < children.length(); ++i)
	{
		POGEL::POINT thiscorneri = corner( i );
		children[ i ]->setpos( ( thispos + thiscorneri )/2.0f );
		POGEL::POINT childpos = children[ i ]->getposition();
		children[ i ]->bounding.addpoint( childpos, thispos );
		children[ i ]->bounding.addpoint( childpos, thiscorneri );
	}
	for( unsigned int i = 0; i < objects.length(); ++i )
	{
		relevent_child( thispos, objects[ i ]->getposition() )->place( objects[ i ], indicies[ i ] );
	}
}


