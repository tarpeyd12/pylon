
template < class T >
POGEL::OCTREE< T >::~OCTREE()
{
	objects.clear();
	indicies.clear();
	if( allobjects )
	{
		if( allobjects->length() )
		{
			//allobjects->clear();
		}
		allobjects = NULL;
	}
	for( unsigned int i = 0; i < children.length(); ++i )
	{
		delete children[ i ];
	}
	children.clear();
	addboundings = true;
}

template < class T >
void
POGEL::OCTREE< T >::FORCEresizelist( unsigned int s )
{
	/*objects.FORCEresizeInternalList( s );
	indicies.FORCEresizeInternalList( s );
	children.FORCEresizeInternalList( s );
	for( unsigned int i = 0; i < children.length(); ++i )
	{
		children[ i ]->FORCEresizelist( s );
	}*/
}

template < class T >
void
POGEL::OCTREE< T >::FORCEfastlist()
{
	//FORCEresizelist( 1 );
}

template < class T >
POGEL::POINT
POGEL::OCTREE< T >::getposition() const
{
	return position;
}

template < class T >
POGEL::BOUNDING
POGEL::OCTREE< T >::getbounding() const
{
	return bounding;
}

template < class T >
unsigned int
POGEL::OCTREE< T >::numobjs() const
{
	return objects.length();
}

template < class T >
unsigned int
POGEL::OCTREE< T >::getlevel() const
{
	return level;
}

template < class T >
void
POGEL::OCTREE< T >::add( T* s )
{
	objects += s;
	if( addboundings )
	{
		bounding.addpoint( getposition(), s->getbounding().max );
		bounding.addpoint( getposition(), s->getbounding().min );
	}
	else
	{
		bounding.addpoint( getposition(), s->getposition() );
	}
}

template < class T >
void
POGEL::OCTREE< T >::add( T* s, unsigned int i )
{
	objects += s;
	indicies += i;
	if( addboundings )
	{
		bounding.addpoint( getposition(), s->getbounding().max );
		bounding.addpoint( getposition(), s->getbounding().min );
	}
	else
	{
		bounding.addpoint( getposition(), s->getposition() );
	}
}

template < class T >
void
POGEL::OCTREE< T >::place(T* s, unsigned int i)
{
	objects += s;
	indicies += i;
	if( addboundings )
	{
		bounding.addpoint( getposition(), s->getbounding().max );
		bounding.addpoint( getposition(), s->getbounding().min );
	}
	else
	{
		bounding.addpoint( getposition(), s->getposition() );
	}
	if( objects.length() > leastobjs && level < maxlevels )
	{
		if( children.length() >= maxchildren )
		{
			relevent_child( getposition(), s->getposition() )->place( s, i );
		}
		else
		{
			grow();
		}
	}
}

/*
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
*/

template < class T >
void
POGEL::OCTREE< T >::regrow()
{
	unsigned int numchildren = children.length();
	if( numchildren )
	{
		for( unsigned int i = 0; i < numchildren; ++i )
		{
			delete children[ i ];
		}
		children.clear();
	}
	grow();
}

template < class T >
CLASSLIST< T * > *
POGEL::OCTREE< T >::relevent( const POGEL::POINT& p, const POGEL::BOUNDING& b ) const
{
	CLASSLIST< T * > * ret = new CLASSLIST< T * > ();
	if( b.surrounds( p, POGEL::POINT(), getbounding() ) )
	{
		ret->add( &objects );
		return ret;
	}
	unsigned int numobjects = objects.length();
	unsigned int numchildren = children.length();
	if( numchildren < maxchildren || ( numobjects <= leastobjs && getbounding().checkbounding( POGEL::POINT(), p, b ) ) )
	{
		for( unsigned int i = 0; i < numobjects; ++i )
		{
			#if defined( USESOLID )
			if( objects[ i ]->getbounding().checkbounding( POGEL::POINT(), p, b ) || objects[ i ]->hasOption( PHYSICS_SOLID_CONCAVE ) )
			#else
			if( objects[ i ]->getbounding().checkbounding( POGEL::POINT(), p, b ) )
			#endif
			{
				ret->add( objects[ i ] );
			}
		}
		return ret;
	}
	for( unsigned int i = 0; i < numchildren; ++i )
	{
		if( children[ i ]->getbounding().checkbounding( POGEL::POINT(), p, b ) )
		{
			ret->pillage( children[ i ]->relevent( p, b ) );
		}
	}
	return ret;
}

template < class T >
CLASSLIST< T * > *
POGEL::OCTREE< T >::relevent( const POGEL::BOUNDING& b ) const
{
	return relevent( POGEL::POINT(), b );
}

template < class T >
CLASSLIST< unsigned int > *
POGEL::OCTREE< T >::releventIndicies( const POGEL::POINT& p, const POGEL::BOUNDING& b ) const
{
	CLASSLIST< unsigned int > * ret = new CLASSLIST< unsigned int > ( indicies.length() );
	if( b.surrounds( p, POGEL::POINT(), getbounding() ) )
	{
		ret->add( indicies );
		return ret;
	}
	unsigned int numobjects = objects.length();
	unsigned int numchildren = children.length();
	if( numchildren < maxchildren || ( numobjects <= leastobjs && getbounding().checkbounding( POGEL::POINT(), p, b ) ) )
	{
		for( unsigned int i = 0; i < numobjects; ++i )
		{
			#if defined( USESOLID )
			if( objects[ i ]->getbounding().checkbounding( POGEL::POINT(), p, b ) || objects[ i ]->hasOption( PHYSICS_SOLID_CONCAVE ) )
			#else
			if( objects[ i ]->getbounding().checkbounding( POGEL::POINT(), p, b ) )
			#endif
			{
				ret->add( indicies[ i ] );
			}
		}
		return ret;
	}
	for( unsigned int i = 0; i < numchildren; ++i )
	{
		if( children[ i ]->getbounding().checkbounding( POGEL::POINT(), p, b ) )
		{
			ret->pillage( children[ i ]->releventIndicies( p, b ) );
		}
	}
	return ret;
}

template < class T >
CLASSLIST< unsigned int > *
POGEL::OCTREE< T >::releventIndicies( const POGEL::BOUNDING& b ) const
{
	return releventIndicies( POGEL::POINT(), b );
}

template < class T >
CLASSLIST<unsigned int> *
POGEL::OCTREE< T >::closestIndicies( const POGEL::POINT& p, bool r, float* cur ) const
{
    CLASSLIST< unsigned int > * ret = new CLASSLIST< unsigned int > ( indicies.length() );
	unsigned int numobjects = objects.length();
	unsigned int numchildren = children.length();
	float dcalc;
	if( numobjects && ( numchildren < maxchildren || numobjects <= leastobjs ) && getposition().distance( p ) - r ? getbounding().maxdistance : 0.0f < *cur )
	{
	    unsigned int bestind = 0;
	    bool hit = false;
		for( unsigned int i = 0; i < numobjects; ++i )
		{
		    dcalc = objects[ i ]->getposition().distance( p ) - r ? objects[ i ]->getbounding().maxdistance : 0.0f;
			if( dcalc < *cur )
			{
			    bestind = i;
			    *cur = dcalc;
				hit = true;
			}
		}
		if( hit )
		{
		    ret->add( indicies[ bestind ] );
		}
	}
    else if( numchildren == maxchildren )
    {
        for( unsigned int i = 0; i < numchildren; ++i )
        {
            dcalc = children[ i ]->getposition().distance( p ) - r ? children[ i ]->getbounding().maxdistance : 0.0f;
            if( dcalc < *cur )
            {
                *cur = dcalc;
                ret->pillage( children[ i ]->closestIndicies( p, r, cur ) );
            }
        }
    }
	return ret;
}

template < class T >
CLASSLIST< POGEL::OCTREE< T > * > *
POGEL::OCTREE< T >::dencityReleventChildren( float dencity ) const
{
	CLASSLIST< POGEL::OCTREE< T > * > * ret = new CLASSLIST< POGEL::OCTREE< T > * > ();
	unsigned int numchildren = children.length();
	float thisdencity = getDencity();
	if( thisdencity >= dencity )
	{
		int chlddncecnt = 0, chlddncecnt_wo = 0;
		for( unsigned int i = 0; i < numchildren; ++i )
		{
			if( children[ i ]->numobjs() )
			{
				++chlddncecnt_wo;
			}
			if( children[ i ]->getDencity() >= thisdencity * 1.5f )
			{
				++chlddncecnt;
			}
		}
		if( !chlddncecnt || chlddncecnt >= maxchildren || chlddncecnt >= chlddncecnt_wo )
		{
			ret->add( this );
		}
		else
		{
			for( unsigned int i = 0; i < numchildren; ++i )
			{
				if( children[ i ]->getDencity() >= thisdencity * 1.5f )
				{
					ret->pillage( children[ i ]->dencityReleventChildren( dencity ) );
				}
			}
		}
	}
	else
	{
		for( unsigned int i = 0; i < numchildren; ++i )
		{
			ret->pillage( children[ i ]->dencityReleventChildren( dencity ) );
		}
	}
	return ret;
}

template < class T >
unsigned int
POGEL::OCTREE< T >::maxLevel() const
{
	unsigned int max = level;
	unsigned int numchildren = children.length();
	if( numchildren )
	{
		for( unsigned int i = 0; i < numchildren; ++i )
		{
			unsigned int chml = children[ i ]->maxLevel();
			if( chml > max )
			{
				max = chml;
			}
		}
	}
	return max;
}

template < class T >
CLASSLIST< POGEL::OCTREE< T > * > *
POGEL::OCTREE< T >::levelReleventChildren(unsigned int lvl_s, unsigned int lvl_e) const
{
	CLASSLIST< POGEL::OCTREE< T > * > * ret = new CLASSLIST< POGEL::OCTREE< T > * > ();
	if( level > lvl_e )
	{
		return ret;
	}
	unsigned int numchildren = children.length();
	if( numchildren && level < lvl_e )
	{
		for( unsigned int i = 0; i < numchildren; ++i )
		{
			ret->pillage( children[ i ]->levelReleventChildren( lvl_s, lvl_e ) );
		}
	}
	if( level == lvl_e || ( level >= lvl_s && !numchildren && objects.length() ) )
	{
		ret->add( this );
	}
	return ret;
}

template < class T >
unsigned int
POGEL::OCTREE< T >::numchildren() const
{
	return children.length();
}

template < class T >
T *
POGEL::OCTREE< T >::object(unsigned int o) const
{
	return objects[ o ];
}

template < class T >
POGEL::OCTREE< T > *
POGEL::OCTREE< T >::child(unsigned int c) const
{
	return children[ c ];
}

template < class T >
void
POGEL::OCTREE< T >::draw() const
{
	//bounding.color = POGEL::COLOR(.05,.125,1,(float)getlevel()/(float)maxlevels);
	unsigned int numchildren = children.length();
	if( numchildren )
	{
		for( unsigned int i = 0; i < numchildren; ++i )
		{
			if( children[ i ]->numobjs() )
			{
				children[ i ]->draw();
			}
		}
	}
	else
	{
		getbounding().draw( POGEL::POINT() );
	}
}
