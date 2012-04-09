
template < class T >
float 
POGEL::OCTREE< T >::avgside() const
{
	POGEL::VECTOR v( getbounding().max, getbounding().min );
	if( fabs(v.x) >= fabs(v.y) && fabs(v.x) >= fabs(v.z) )
	{
		return v.x;
	}
	else if( fabs(v.y) >= fabs(v.x) && fabs(v.y) >= fabs(v.z) )
	{
		return v.y;
	}
	else
	{
		return v.z;
	}
}

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
float
POGEL::OCTREE< T >::getMass()
{
	if( mass_good )
	{
		return mass;
	}
	float ret = 0.0f;
	if( numchildren() )
	{
		for( unsigned int i = 0; i < numchildren(); ++i )
		{
			ret += child( i )->getMass();
		}
	}
	else
	{
		for( unsigned int i = 0; i < numobjs(); ++i )
		{
			ret += object( i )->behavior.mass;
		}
	}
	mass = ret;
	mass_good = true;
	return ret;
}

template < class T >
float
POGEL::OCTREE< T >::getDencity() const
{
    if(getbounding().min != getbounding().max) 
    {
        POGEL::VECTOR v( getbounding().max, getbounding().min );
        return getMass() / ( (v.x?v.x:1.0f) * (v.y?v.y:1.0f) * (v.z?v.z:1.0f) );
    }
    return 0.0f;
}

template < class T >
void
POGEL::OCTREE< T >::boolgrvs( bool* b ) const
{
	for( unsigned int i = 0; i < objects.length(); ++i )
	{
		b[ indicies[ i ] ] = true;
	}
}

template < class T >
void
POGEL::OCTREE< T >::uintgrvs( unsigned int * b ) const
{
	for( unsigned int i = 0; i < objects.length(); ++i )
	{
		b[ indicies[ i ] ] = level;
	}
}

template < class T >
POGEL::POINT 
POGEL::OCTREE< T >::getmasscenter() 
{
	if( masscenter_good )
	{
		return masscenter;
	}
	if( numobjs() ) 
	{
		masscenter = object( 0 )->getposition() / float( numobjs() );
		for( unsigned int i = 1; i < numobjs(); ++i )
		{
			masscenter += object( i )->getposition() * (object( i )->behavior.mass / getMass() );
		}
	}
	for( unsigned int i = 0; i < numchildren(); ++i )
	{
		if(!child(i)->masscenter_good)
		{
			child(i)->getmasscenter();
		}
	}
	masscenter_good = true;
	return masscenter;
}

template < class T >
bool
POGEL::OCTREE< T >::objhaspos( const POGEL::POINT& p ) const
{
	for( unsigned int i = 0; i < objects.length(); ++i )
	{
		if( object( i )->position == p )
		{
			return true;
		}
	}
	return false;
}

template < class T >
POGEL::VECTOR 
POGEL::OCTREE< T >::getpull( const POGEL::POINT& p, float m ) const
{
	if( ( numobjs() <= leastobjs && !objhaspos( p ) ) || bounding.min.distance( getBounding().max ) / getmasscenter().distance( p ) < theta )
	{
		return POGEL::PHYSICS::SINGULARITY( getmasscenter(), getMass() ).getpull( p, m );
	}
	POGEL::VECTOR ret;
	for (unsigned int i = 0; i < numchildren(); ++i )
	{
		if( child( i )->numobjs() )
		{
			ret += child( i )->getpull( p, m );
		}
	}
	return ret;
}

template < class T >
POGEL::VECTOR 
POGEL::OCTREE< T >::drawgetpull( const POGEL::POINT& p, float m ) const
{
	if( numobjs() <= leastobjs || bounding.min.distance( bounding.max ) / getmasscenter().distance( p ) < theta ) 
	{
		bounding.color = POGEL::COLOR( 0.25f, 0.25f, 0.25f, getMass() / progen()->getMass() );
		bounding.draw( POGEL::POINT() );
		if( POGEL::hasproperty( POGEL_BOUNDING ) )
		{
			getmasscenter().draw( 3, bounding.color );
		}
		return POGEL::PHYSICS::SINGULARITY( getmasscenter(), getMass() ).getpull( p, m );
	}
	POGEL::VECTOR ret;
	for( unsigned int i = 0; i < numchildren(); ++i )
	{
		if( child( i )->numobjs() )
		{
			ret += child( i )->drawgetpull( p, m );
		}
	}
	return ret;
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
	masscenter = thispos;//POGEL::POINT(); 
	mass = 0.0f;
	mass_good = masscenter_good = false;
	for( unsigned int i = 0; i < objects.length(); ++i ) 
	{
		if( !masscenter_good )
		{
			masscenter += object(i)->getposition()*object(i)->behavior.mass;
		}
		if( !mass_good )
		{
			mass += object( i )->behavior.mass;
		}
		relevent_child( getposition(), objects[ i ]->getposition() )->place( objects[ i ], indicies[ i ] );
	}
	masscenter /= mass;
	mass_good = masscenter_good = true;
	/*for(unsigned int i = 0; i < children.length(); i++)
		if(child(i)->numobjs() > leastobjs)
			child(i)->grow();*/
}

