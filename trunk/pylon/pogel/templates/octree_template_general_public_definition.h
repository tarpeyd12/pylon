
~OCTREE();

void FORCEresizelist( unsigned int s );
void FORCEfastlist();

POGEL::POINT getposition() const;
POGEL::BOUNDING getbounding() const;

unsigned int numobjs() const;

unsigned int getlevel() const;

void add( T * s );
void add( T * s, unsigned int i );
void place( T * s, unsigned int i );

//void grow();
void regrow();

CLASSLIST< T * > * relevent( const POGEL::POINT& p, const POGEL::BOUNDING& b ) const;
CLASSLIST< T * > * relevent( const POGEL::BOUNDING& b ) const;

CLASSLIST<unsigned int> * releventIndicies( const POGEL::POINT& p, const POGEL::BOUNDING& b ) const;
CLASSLIST<unsigned int> * releventIndicies( const POGEL::BOUNDING& b ) const;

CLASSLIST<unsigned int> * closestIndicies( const POGEL::POINT& p, bool r, float* cur ) const;

CLASSLIST< OCTREE< T > * > * dencityReleventChildren( float dencity ) const;
unsigned int maxLevel() const;
CLASSLIST< OCTREE< T > * > * levelReleventChildren( unsigned int lvl_s, unsigned int lvl_e ) const;

unsigned int numchildren() const;

T * object( unsigned int o ) const;
OCTREE< T > * child( unsigned int c ) const;

void draw() const;

