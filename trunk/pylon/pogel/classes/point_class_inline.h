
void
POGEL::POINT::get_values( float * a, float * b, float * c ) const
{
    *a = x;
    *b = y;
    *c = z;
}

void
POGEL::POINT::set_values( float a, float b, float c )
{
    x = a;
    y = b;
    z = c;
}

void
POGEL::POINT::print() const
{
    POGEL::message( " %7.3f, %7.3f, %7.3f", x, y, z );
}

std::string
POGEL::POINT::toString() const
{
    char * sx = POGEL::string( "%0.27f", x );
    char * sy = POGEL::string( "%0.27f", y );
    char * sz = POGEL::string( "%0.27f", z );
    std::string s = "{[" + std::string( sx ) + "],[" + std::string( sy ) + "],[" + std::string( sz ) + "]}";
    delete [] sx;
    delete [] sy;
    delete [] sz;
    return s;
}

void
POGEL::POINT::draw() const
{
    #ifdef OPENGL
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_LIGHTING );
    glPointSize( 5 );
    POGEL::COLOR( 0.0f, 1.75f, 0.75f, 1.0f ).set();
    glBegin( GL_POINTS );
        glVertex3f( x, y, z );
    glEnd();
    glPointSize( 1 );
    POGEL::COLOR( 1.0f, 1.0f, 1.0f, 1.0f ).set();
    glEnable( GL_LIGHTING );
    glEnable( GL_TEXTURE_2D );
    #endif
}

void
POGEL::POINT::draw( unsigned int a ) const
{
    #ifdef OPENGL
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glPointSize(a);
    glBegin(GL_POINTS);
        glVertex3f(x,y,z);
    glEnd();
    glPointSize(1);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    #endif
}

void
POGEL::POINT::draw( unsigned int a, const POGEL::COLOR & color ) const
{
    #ifdef OPENGL
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glPointSize(a);
    color.set();
    glBegin(GL_POINTS);
        glVertex3f(x,y,z);
    glEnd();
    glPointSize(1);
    POGEL::COLOR(1,1,1,1).set();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    #endif
}

void
POGEL::POINT::drawto( const POGEL::POINT & p ) const
{
    #ifdef OPENGL
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    POGEL::COLOR(0,1.75,.75,1).set();
    glBegin(GL_LINES);
        glVertex3f(x,y,z);
        glVertex3f(p.x,p.y,p.z);
    glEnd();
    POGEL::COLOR(1,1,1,1).set();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    #endif
}

void
POGEL::POINT::translate() const
{
    glTranslatef( x, y, z );
}

float
POGEL::POINT::distance( const POGEL::POINT& p ) const
{
    float _x( p.x - x ), _y( p.y - y ), _z( p.z - z );
    return (float)sqrt( ( _x * _x ) + ( _y * _y ) + ( _z *_z ) );
}

float
POGEL::POINT::distancesquared( const POGEL::POINT& p ) const
{
    float _x( p.x - x ), _y( p.y - y ), _z( p.z - z );
    return ( _x * _x ) + ( _y * _y ) + ( _z *_z );
}

POGEL::POINT
POGEL::POINT::operator*( float a ) const
{
    return POGEL::POINT( x * a, y * a, z * a );
}

POGEL::POINT
POGEL::POINT::operator/( float a ) const
{
    return POGEL::POINT( x/a, y/a, z/a );
}

POGEL::POINT
POGEL::POINT::operator*( const POGEL::POINT& p ) const
{
    return POGEL::POINT( x*p.x, y*p.y, z*p.z );
}

POGEL::POINT
POGEL::POINT::operator/( const POGEL::POINT& p ) const
{
    return POGEL::POINT( x/p.x, y/p.y, z/p.z) ;
}

POGEL::POINT
POGEL::POINT::operator+( const POGEL::POINT& p ) const
{
    return POGEL::POINT( x+p.x, y+p.y, z+p.z );
}

POGEL::POINT
POGEL::POINT::operator-( const POGEL::POINT& p ) const
{
    return POGEL::POINT( x-p.x, y-p.y, z-p.z );
}

POGEL::POINT&
POGEL::POINT::operator=( const POGEL::POINT& p )
{
    /*x=p.x;
    y=p.y;
    z=p.z;*/
    memcpy( this, &p, sizeof( p ) );
    return *this;
}

POGEL::POINT&
POGEL::POINT::operator*=(const float& a)
{
    x*=a;
    y*=a;
    z*=a;
    return (*this);
}

POGEL::POINT&
POGEL::POINT::operator/=(const float& a)
{
    x/=a;
    y/=a;
    z/=a;
    return (*this);
}

POGEL::POINT&
POGEL::POINT::operator*=(const POGEL::POINT& p)
{
    x*=p.z;
    y*=p.y;
    z*=p.z;
    return (*this);
}

POGEL::POINT&
POGEL::POINT::operator/=(const POGEL::POINT& p)
{
    x/=p.x;
    y/=p.y;
    z/=p.z;
    return (*this);
}

POGEL::POINT&
POGEL::POINT::operator+=(const POGEL::POINT& p)
{
    x+=p.x;
    y+=p.y;
    z+=p.z;
    return (*this);
}

POGEL::POINT&
POGEL::POINT::operator-=(const POGEL::POINT& p)
{
    x-=p.x;
    y-=p.y;
    z-=p.z;
    return (*this);
}

bool
POGEL::POINT::operator==(const POGEL::POINT& p) const
{
    return (p.x==x && p.y==y && p.z==z);
}

bool
POGEL::POINT::operator!=(const POGEL::POINT& p) const
{
    return (p.x!=x || p.y!=y || p.z!=z);
}

bool
POGEL::POINT::isbad() const
{
    return (isnan(x) || isnan(y) || isnan(z)) || !(isfinite(x) && isfinite(y) && isfinite(z));
}



void POGEL::VECTOR::normalize()
{
    float len=getdistance();
    if(len != 0.0f)
    {
        len = 1.0f / len;
        x *= len;
        y *= len;
        z *= len;
    }
}

POGEL::VECTOR
POGEL::VECTOR::normal() const
{
    float d = getdistance();
    return POGEL::VECTOR( x/d, y/d, z/d );
}

void POGEL::VECTOR::anglenormalize()
{
    while(x >=  180.0)
        x -= 180.0;
    while(y >=  180.0)
        y -= 180.0;
    while(z >=  180.0)
        z -= 180.0;

    while(x <= -180.0)
        x += 180.0;
    while(y <= -180.0)
        y += 180.0;
    while(z <= -180.0)
        z += 180.0;
}

POGEL::VECTOR
POGEL::VECTOR::anglenormal() const
{
    POGEL::VECTOR ret(x,y,z);
    ret.anglenormalize();
    return ret;
}

float
POGEL::VECTOR::getdistance() const
{
    float r = (float)sqrt(x*x+y*y+z*z);
    if( isnan(r) || !isfinite(r) )
    {
        return 0.0f;
    }
    return r;
}

float
POGEL::VECTOR::getangle( const POGEL::VECTOR& other,  const POGEL::VECTOR& ref ) const
{
    ref.getdistance();
    // http://en.wikipedia.org/wiki/Inner_product_space
    return acos( this->dotproduct(other) / (this->getdistance() * other.getdistance()) );
}

float
POGEL::VECTOR::getangle( const POGEL::VECTOR& other ) const
{
    // http://en.wikipedia.org/wiki/Inner_product_space
    return acos( this->dotproduct(other) / (this->getdistance() * other.getdistance()) );
}

POGEL::VECTOR&
POGEL::VECTOR::dodotproduct( const POGEL::VECTOR& b )
{
    POGEL::VECTOR a(x,y,z);
    x = ((a.y*b.z) - (a.z*b.y));
    y = ((a.z*b.x) - (a.x*b.z));
    z = ((a.x*b.y) - (a.y*b.x));
    return *this;
}

float
POGEL::VECTOR::dotproduct( const POGEL::VECTOR& a ) const
{
    return (x*a.x)+(y*a.y)+(z*a.z);
}

void
POGEL::VECTOR::frompoints( const POGEL::POINT& a, const POGEL::POINT& b )
{
    x = b.x - a.x;
    y = b.y - a.y;
    z = b.z - a.z;
}

POGEL::POINT
POGEL::VECTOR::topoint() const
{
    POGEL::POINT p(x,y,z);
    return p;
}

POGEL::VECTOR POGEL::VECTOR::operator*(float a) const
{
    return POGEL::VECTOR(x*a, y*a, z*a);
}

POGEL::VECTOR POGEL::VECTOR::operator/(float a) const
{
    return POGEL::VECTOR(x/a, y/a, z/a);
}

POGEL::VECTOR
POGEL::VECTOR::operator*( const POGEL::VECTOR& p) const
{
    return POGEL::VECTOR(x*p.x, y*p.y, z*p.z);
}

POGEL::VECTOR
POGEL::VECTOR::operator/( const POGEL::VECTOR& p) const
{
    return POGEL::VECTOR(x/p.x, y/p.y, z/p.z);
}

POGEL::VECTOR
POGEL::VECTOR::operator+( const POGEL::VECTOR& p) const
{
    return POGEL::VECTOR(x+p.x, y+p.y, z+p.z);
}

POGEL::VECTOR
POGEL::VECTOR::operator-( const POGEL::VECTOR& p) const
{
    return POGEL::VECTOR(x-p.x, y-p.y, z-p.z);
}

POGEL::VECTOR& POGEL::VECTOR::operator=(const POGEL::VECTOR & p)
{
    /*x=p.x;
    y=p.y;
    z=p.z;*/
    memcpy(this,&p,sizeof(p));
    return *this;
}

POGEL::VECTOR& POGEL::VECTOR::operator*=(const float& a)
{
    x*=a;
    y*=a;
    z*=a;
    return (*this);
}

POGEL::VECTOR& POGEL::VECTOR::operator/=(const float& a)
{
    x/=a;
    y/=a;
    z/=a;
    return (*this);
}

POGEL::VECTOR& POGEL::VECTOR::operator*=(const POGEL::VECTOR& p)
{
    x*=p.z;
    y*=p.y;
    z*=p.z;
    return (*this);
}

POGEL::VECTOR& POGEL::VECTOR::operator/=(const POGEL::VECTOR& p)
{
    x/=p.x;
    y/=p.y;
    z/=p.z;
    return (*this);
}

POGEL::VECTOR& POGEL::VECTOR::operator+=(const POGEL::VECTOR& p)
{
    x+=p.x;
    y+=p.y;
    z+=p.z;
    return (*this);
}

POGEL::VECTOR& POGEL::VECTOR::operator-=(const POGEL::VECTOR& p)
{
    x-=p.x;
    y-=p.y;
    z-=p.z;
    return (*this);
}

bool
POGEL::VECTOR::operator==( const POGEL::VECTOR& p) const
{
    return (p.x==x && p.y==y && p.z==z);
}

bool
POGEL::VECTOR::operator!=( const POGEL::VECTOR& p) const
{
    return (p.x!=x || p.y!=y || p.z!=z);
}


std::string POGEL::VERTEX::toString()
{
    char *sx=POGEL::string("%0.27f",x);
    char *sy=POGEL::string("%0.27f",y);
    char *sz=POGEL::string("%0.27f",z);
    char *su=POGEL::string("%f",u);
    char *sv=POGEL::string("%f",v);
    std::string s = "{["+std::string(sx)+"],["+std::string(sy)+"],["+std::string(sz)+"],["+std::string(su)+"],["+std::string(sv)+"],"+normal.toString()+","+color.toString()+"}";
    free(sx);
    free(sy);
    free(sz);
    free(su);
    free(sv);
    return s;
}

void POGEL::VERTEX::get_values(float *a, float *b, float *c, float *s, float *t)
{
    *a=x;
    *b=y;
    *c=z;
    *s=u;
    *t=v;
}

void POGEL::VERTEX::set_values(float a, float b, float c, float s, float t)
{
    x=a;
    y=b;
    z=c;
    u=s;
    v=t;
}

void POGEL::VERTEX::get_point_values(float *a, float *b, float *c)
{
    *a=x;
    *b=y;
    *c=z;
}

void POGEL::VERTEX::set_point_values(float a, float b, float c)
{
    x=a;
    y=b;
    z=c;
}

void POGEL::VERTEX::get_tex_values(float *s, float *t)
{
    *s=u;
    *t=v;
}

void POGEL::VERTEX::set_tex_values(float s, float t)
{
    u=s;
    v=t;
}

void POGEL::VERTEX::scroll_tex_values(float s, float t)
{
    u+=s;
    v+=t;
}

POGEL::POINT POGEL::VERTEX::topoint()
{
    return POGEL::POINT(x,y,z);
}

POGEL::VERTEX
POGEL::VERTEX::operator*(float a) const
{
    return POGEL::VERTEX(x*a, y*a, z*a);
}

POGEL::VERTEX
POGEL::VERTEX::operator/(float a) const
{
    return POGEL::VERTEX(x/a, y/a, z/a);
}

POGEL::VERTEX
POGEL::VERTEX::operator*(POGEL::VERTEX p) const
{
    return POGEL::VERTEX(x*p.x, y*p.y, z*p.z);
}

POGEL::VERTEX
POGEL::VERTEX::operator/(POGEL::VERTEX p) const
{
    return POGEL::VERTEX(x/p.x, y/p.y, z/p.z);
}

POGEL::VERTEX
POGEL::VERTEX::operator+(POGEL::VERTEX p) const
{
    return POGEL::VERTEX(x+p.x, y+p.y, z+p.z);
}

POGEL::VERTEX
POGEL::VERTEX::operator-(POGEL::VERTEX p) const
{
    return POGEL::VERTEX(x-p.x, y-p.y, z-p.z);
}

POGEL::VERTEX&
POGEL::VERTEX::operator=(const POGEL::VERTEX & p)
{
    /*x=p.x;
    y=p.y;
    z=p.z;
    u=p.u;
    v=p.v;
    usable=p.usable;
    color=p.color;
    normal=p.normal;
    boneID = p.boneID;
    boneIDs[0] = p.boneIDs[0];
    boneIDs[1] = p.boneIDs[1];
    boneIDs[2] = p.boneIDs[2];
    weights[0] = p.weights[0];
    weights[1] = p.weights[1];
    weights[2] = p.weights[2];*/
    memcpy(this,&p,sizeof(p));
    return (*this);
}

POGEL::VERTEX& POGEL::VERTEX::operator=(const POGEL::POINT& p)
{
    x=p.x;
    y=p.y;
    z=p.z;
    return (*this);
}

POGEL::VERTEX& POGEL::VERTEX::operator*=(const float& a)
{
    x*=a;
    y*=a;
    z*=a;
    return (*this);
}

POGEL::VERTEX& POGEL::VERTEX::operator/=(const float& a)
{
    x/=a;
    y/=a;
    z/=a;
    return (*this);
}

POGEL::VERTEX& POGEL::VERTEX::operator*=(const POGEL::VERTEX& p)
{
    x*=p.z;
    y*=p.y;
    z*=p.z;
    return (*this);
}

POGEL::VERTEX& POGEL::VERTEX::operator/=(const POGEL::VERTEX& p)
{
    x/=p.x;
    y/=p.y;
    z/=p.z;
    return (*this);
}

POGEL::VERTEX& POGEL::VERTEX::operator+=(const POGEL::VERTEX& p)
{
    x+=p.x;
    y+=p.y;
    z+=p.z;
    usable=p.usable;
    color=p.color;
    normal=p.normal;
    return (*this);
}

POGEL::VERTEX& POGEL::VERTEX::operator-=(const POGEL::VERTEX& p)
{
    x-=p.x;
    y-=p.y;
    z-=p.z;
    usable=p.usable;
    color=p.color;
    normal=p.normal;
    return (*this);
}
