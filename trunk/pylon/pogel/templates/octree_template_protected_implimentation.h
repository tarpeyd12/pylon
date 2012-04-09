
#ifndef USESOLID
template < class T >
#else
template <  >
#endif
void
POGEL::OCTREE< T >::setpos( const POGEL::POINT& p )
{
	position = p;
}

#ifndef USESOLID
template < class T >
#else
template <  >
#endif
POGEL::OCTREE< T > *
POGEL::OCTREE< T >::bool_child( bool a, bool b, bool c ) const
{
	if( children.length() )
	{
		return children[ bool_child_num( a, b, c ) ];
	}
	return NULL;
}

#ifndef USESOLID
template < class T >
#else
template <  >
#endif
POGEL::OCTREE< T > *
POGEL::OCTREE< T >::bin_child(unsigned char c) const
{
	if( children.length() )
	{
		return children[ bin_child_num( c ) ];
	}
	return NULL;
}

#ifndef USESOLID
template < class T >
#else
template <  >
#endif
POGEL::OCTREE< T > *
POGEL::OCTREE< T >::relevent_child(const POGEL::POINT& reff, const POGEL::POINT& pos) const
{
	return bool_child( pos.x >= reff.x, pos.y >= reff.y, pos.z >= reff.z );
}

#ifndef USESOLID
template < class T >
#else
template <  >
#endif
POGEL::POINT
POGEL::OCTREE< T >::corner( unsigned int c ) const
{
	POGEL::BOUNDING b = getbounding();
	switch( c )
	{
		case TUR: return POGEL::POINT( b.max.x, b.max.y, b.max.z );
		case TBR: return POGEL::POINT( b.max.x, b.min.y, b.max.z );
		case TUL: return POGEL::POINT( b.min.x, b.max.y, b.max.z );
		case TBL: return POGEL::POINT( b.min.x, b.min.y, b.max.z );
		case AUR: return POGEL::POINT( b.max.x, b.max.y, b.min.z );
		case ABR: return POGEL::POINT( b.max.x, b.min.y, b.min.z );
		case AUL: return POGEL::POINT( b.min.x, b.max.y, b.min.z );
		case ABL: return POGEL::POINT( b.min.x, b.min.y, b.min.z );
	}
	return POGEL::POINT();
}

#ifndef USESOLID
template < class T >
#else
template <  >
#endif
POGEL::POINT
POGEL::OCTREE< T >::bin_corner( unsigned char c ) const
{
	return corner( bin_child_num( c ) );
}

#ifndef USESOLID
template < class T >
#else
template <  >
#endif
POGEL::OCTREE< T > *
POGEL::OCTREE< T >::progen() const
{
	if( parent == NULL )
	{
		return this;
	}
	return parent;
}

