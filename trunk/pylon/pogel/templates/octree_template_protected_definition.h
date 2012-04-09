
void setpos( const POGEL::POINT& p );
POGEL::OCTREE< T > * bool_child( bool a, bool b, bool c ) const;
POGEL::OCTREE< T > * bin_child( unsigned char c ) const;
POGEL::OCTREE< T > * relevent_child( const POGEL::POINT& reff, const POGEL::POINT& pos ) const;
POGEL::POINT corner( unsigned int c ) const;
POGEL::POINT bin_corner( unsigned char c ) const;
POGEL::OCTREE< T > * progen() const;
