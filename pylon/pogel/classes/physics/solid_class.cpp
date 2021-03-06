#include "../../pogel.h"
#include "../../pogel_internals.h"
#include "solid_class.h"

POGEL::PHYSICS::SOLID::SOLID() : POGEL::OBJECT()
{
    behavior = POGEL::PHYSICS::SOLIDPHYSICALPROPERTIES();
    physproperties = 0;
    maximumdistance = 0.0f;
    stepstaken = objboundingskips = stepsatboundingcheck = 0;
    bounding = POGEL::BOUNDING(BOUNDING_OBJECT);
    trail = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
    rots = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
    trailsize = PHYSICS_SOLID_TRAILSIZE;
    for( int i = 0; i < PHYSICS_SOLID_TRAILSIZE; i++ )
    {
        trail[i] = rots[i] = POGEL::POINT();
    }
    container = NULL;
    callback = NULL;
    function = NULL;
    hitfilter = NULL;
    facetree = NULL;
    force = POGEL::VECTOR();
    sleeping = false;
    cantsleep = false;
}

POGEL::PHYSICS::SOLID::SOLID(const char * n) : POGEL::OBJECT(n)
{
	behavior = POGEL::PHYSICS::SOLIDPHYSICALPROPERTIES();
	physproperties = 0;
	maximumdistance = 0.0f;
	stepstaken = objboundingskips = stepsatboundingcheck = 0;
	bounding = POGEL::BOUNDING(BOUNDING_OBJECT);
	trail = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
	rots = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
	trailsize = PHYSICS_SOLID_TRAILSIZE;
	for( int i = 0; i < PHYSICS_SOLID_TRAILSIZE; i++ )
	{
	    trail[i] = rots[i] = POGEL::POINT();
	}
	container = NULL;
	callback = NULL;
	function = NULL;
	hitfilter = NULL;
	facetree = NULL;
	force = POGEL::VECTOR();
	sleeping = false;
	cantsleep = false;
}

POGEL::PHYSICS::SOLID::SOLID(POGEL::PHYSICS::SOLIDPHYSICALPROPERTIES attr, unsigned int prop) : POGEL::OBJECT()
{
	behavior = attr;
	physproperties = prop;
	maximumdistance = 0.0f;
	stepstaken = objboundingskips = stepsatboundingcheck = 0;
	bounding = POGEL::BOUNDING(BOUNDING_OBJECT);
	trail = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
	rots = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
	trailsize = PHYSICS_SOLID_TRAILSIZE;
	for( int i = 0; i < PHYSICS_SOLID_TRAILSIZE; i++ )
    {
        trail[i] = rots[i] = POGEL::POINT();
    }
	container = NULL;
	callback = NULL;
	function = NULL;
	hitfilter = NULL;
	facetree = NULL;
	force = POGEL::VECTOR();
	sleeping = false;
	cantsleep = false;
}

POGEL::PHYSICS::SOLID::SOLID(POGEL::OBJECT* obj, POGEL::PHYSICS::SOLIDPHYSICALPROPERTIES attr, unsigned int prop) : POGEL::OBJECT(obj)
{
	behavior = attr;
	physproperties = prop;
	maximumdistance = 0.0f;
	stepstaken = objboundingskips = stepsatboundingcheck = 0;
	bounding  = POGEL::BOUNDING(BOUNDING_OBJECT);
	trail = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
	rots  = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
	trailsize = PHYSICS_SOLID_TRAILSIZE;
	for( int i = 0; i < PHYSICS_SOLID_TRAILSIZE; i++ )
	{
	    trail[i] = rots[i] = POGEL::POINT();
    }
	container = NULL;
	callback = NULL;
	function = NULL;
	hitfilter = NULL;
	facetree = NULL;
	force     = POGEL::VECTOR();
	sleeping  = false;
	cantsleep = false;
};

POGEL::PHYSICS::SOLID::SOLID(std::string s)
{
	std::string s_name = POGEL::getStringSection('[',1,false,']',1,false, s);
	setname(POGEL::string("%s",s_name.c_str()));

	unsigned int physprp, prp, slping, cntslp, i, bpos, nbcs;

	sscanf(s.c_str(), std::string("{["+s_name+"],[%u],[%u],[%u],[%u]").c_str(), &physprp, &prp, &slping, &cntslp);

	setOptions(physprp);
	setproperties(prp);
	sleeping = (bool)slping;
	cantsleep = (bool)cntslp;

	position = POGEL::POINT(POGEL::getStringComponentLevel('{','}',s,"0 0"));
	rotation = POGEL::POINT(POGEL::getStringComponentLevel('{','}',s,"0 1"));
	direction = POGEL::VECTOR(POGEL::getStringComponentLevel('{','}',s,"0 2"));
	spin = POGEL::VECTOR(POGEL::getStringComponentLevel('{','}',s,"0 3"));
	behavior = POGEL::PHYSICS::SOLIDPHYSICALPROPERTIES(POGEL::getStringComponentLevel('{','}',s,"0 4"));

	std::string curtri = trianglestring = POGEL::getStringSection('<',1,false,'>',1,false, s);

	unsigned int numendintri = POGEL::getOccurrencesInString('}', POGEL::TRIANGLE().toString());

	addtrianglespace(POGEL::getOccurrencesInString('}', curtri)/numendintri);

	while( !curtri.empty() )
	{
		POGEL::message("\rLoading triangles: %0.2f%%",(((float)trianglestring.length()-(float)curtri.length())/(float)trianglestring.length())*100);
		addtriangle(POGEL::TRIANGLE(curtri));
		for( i = bpos = nbcs = 0; i < curtri.length(); i++ )
		{
		    if( curtri[i] == '}' && nbcs++ == numendintri-1 )
		    {
		        bpos = i;
		        break;
            }
        }
		std::string trtmp = curtri; curtri.clear();
		if( bpos+2 <= trtmp.length() )
		{
		    curtri = trtmp.substr( bpos+2 );
        }
	}
	POGEL::message("\n");
	maximumdistance = 0.0f;
	stepstaken = objboundingskips = stepsatboundingcheck = 0;
	bounding  = POGEL::BOUNDING(BOUNDING_OBJECT);
	trail = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
	rots  = new POGEL::POINT[PHYSICS_SOLID_TRAILSIZE];
	trailsize = PHYSICS_SOLID_TRAILSIZE;
	for( int i = 0; i < PHYSICS_SOLID_TRAILSIZE; i++ )
	{
	    trail[i] = rots[i] = POGEL::POINT();
	}
	container = NULL;
	callback = NULL;
	function = NULL;
	hitfilter = NULL;
	facetree = NULL;
	force     = POGEL::VECTOR();
}

POGEL::PHYSICS::SOLID::~SOLID()
{
	if( trail )
	{
	    delete [] trail;
	}

	if( rots )
	{
	    delete [] rots;
	}

	if( facetree )
	{
	    delete facetree;
	}

	if( callback )
	{
	    delete callback;
	}

	if( function )
	{
	    delete function;
	}

	if( hitfilter )
	{
	    delete hitfilter;
	}

	if( container )
	{
	    container = NULL;
	}
}

unsigned long
POGEL::PHYSICS::SOLID::getstepstaken()
{
    return stepstaken;
}

void
POGEL::PHYSICS::SOLID::setstepstaken(unsigned long s)
{
    stepstaken = s;
}

void
POGEL::PHYSICS::SOLID::setCallback(SOLID_CALLBACK *func)
{
    callback = func;
}

void
POGEL::PHYSICS::SOLID::setStepFunc(SOLID_FUNCTION *func)
{
    function = func;
}

void
POGEL::PHYSICS::SOLID::setHitFilter(SOLID_HITFILTER *func)
{
    hitfilter = func;
}

bool
POGEL::PHYSICS::SOLID::napping()
{
    return sleeping;
}

void
POGEL::PHYSICS::SOLID::sleep()
{
    if( !cantsleep )
    {
        sleeping =  true;
    }
}

void
POGEL::PHYSICS::SOLID::wake()
{
    if( !cantsleep )
    {
        sleeping = false;
    }
}

void
POGEL::PHYSICS::SOLID::forcesleep()
{
    sleeping  =  true;
}

void
POGEL::PHYSICS::SOLID::forcewake()
{
    sleeping  = false;
}

void
POGEL::PHYSICS::SOLID::zombify()
{
    cantsleep =  true;
}

void
POGEL::PHYSICS::SOLID::unzombify()
{
    cantsleep = false;
}

void
POGEL::PHYSICS::SOLID::resizetrail(unsigned long size)
{
	if( trail )
	{
	    delete [] trail;
	}

	if( rots )
	{
	    delete [] rots;
	}

	trailsize = size;
	trail = new POGEL::POINT[size];
	rots = new POGEL::POINT[size];

    POGEL::POINT prp(POGEL::FloatRand(1.0f));
    if( position.distance(POGEL::POINT()) > 0.0f )
    {
        prp *= position;
    }

	for( unsigned long i = 0; i < trailsize; i++ )
	{
		trail[i] = rots[i] = prp*PARTICLE_SLOWDOWN_RATIO;
	}
}

void
POGEL::PHYSICS::SOLID::steppostrail()
{
	trail[0] = position;
	for( unsigned long i = trailsize-1; i > 0; --i )
	{
	    trail[i] = trail[i-1];
	}
}

void
POGEL::PHYSICS::SOLID::steprottrail()
{
	rots[0] = rotation;
	for( unsigned long i = trailsize-1; i > 0; --i )
	{
	    rots[i] = rots[i-1];
	}
}

void
POGEL::PHYSICS::SOLID::steptrail()
{
	trail[0] = position;
	rots[0] = rotation;
	for( unsigned long i = trailsize-1; i > 0; --i )
	{
		trail[i] = trail[i-1];
		rots[i] = rots[i-1];
	}
}

bool
POGEL::PHYSICS::SOLID::sameposlegacy( float pres )
{
	bool ret = false;
	if( trailsize < PHYSICS_SOLID_TRAILINDEX )
	{
	    ret = POGEL::about(position.x, trail[trailsize-1].x, pres);
	    ret = ret && POGEL::about(position.y, trail[trailsize-1].y, pres);
	    ret = ret && POGEL::about(position.z, trail[trailsize-1].z, pres);
	    return ret;
	}

	if( stepstaken < (trailsize/PHYSICS_SOLID_TRAILINDEX) )
	{
	    return false;
	}

	for( unsigned long i = 0; i < trailsize && i < stepstaken + 1; i += (trailsize/PHYSICS_SOLID_TRAILINDEX) )
	{
	    bool test = POGEL::about(position.x, trail[i].x, pres);
	    test = test && POGEL::about(position.y, trail[i].y, pres);
	    test = test && POGEL::about(position.z, trail[i].z, pres);
	    if( test )
	    {
	        ret = true;
	    }
		else
		{
		    return false;
		}
	}

	return ret;
}

bool
POGEL::PHYSICS::SOLID::samerotlegacy( float pres )
{
	bool ret = false;
	if( trailsize < PHYSICS_SOLID_TRAILINDEX )
	{
	    ret = POGEL::about(rotation.x, rots[trailsize-1].x, pres);
	    ret = ret && POGEL::about(rotation.y, rots[trailsize-1].y, pres);
	    ret = ret && POGEL::about(rotation.z, rots[trailsize-1].z, pres);
	    return ret;
	}

	if( stepstaken < (trailsize/PHYSICS_SOLID_TRAILINDEX) )
	{
	    return false;
	}

	for( unsigned long i = 0; i < trailsize && i < stepstaken + 1; i += (trailsize/PHYSICS_SOLID_TRAILINDEX) )
	{
	    bool test = POGEL::about(rotation.x, rots[i].x, pres);
	    test = test && POGEL::about(rotation.y, rots[i].y, pres);
	    test = test && POGEL::about(rotation.z, rots[i].z, pres);
        if( test )
        {
            ret = true;
        }
		else
		{
		    return false;
		}
	}

	return ret;
}

bool
POGEL::PHYSICS::SOLID::samelegacy( float pres )
{
	bool ret = false;
	if(trailsize < PHYSICS_SOLID_TRAILINDEX)
	{
	    ret = POGEL::about(position.x, trail[trailsize-1].x, pres);
	    ret = ret && POGEL::about(position.y, trail[trailsize-1].y, pres);
	    ret = ret && POGEL::about(position.z, trail[trailsize-1].z, pres);
	    ret = ret && POGEL::about(rotation.x, rots[trailsize-1].x, pres);
	    ret = ret && POGEL::about(rotation.y, rots[trailsize-1].y, pres);
	    ret = ret && POGEL::about(rotation.z, rots[trailsize-1].z, pres);
	    return ret;
	}

	if( stepstaken < (trailsize/PHYSICS_SOLID_TRAILINDEX) )
	{
	    return false;
	}

	for( unsigned long i = 0; i < trailsize && i < stepstaken + 1; i += (trailsize/PHYSICS_SOLID_TRAILINDEX) )
	{
	    bool test = POGEL::about(position.x, trail[i].x, pres);
	    test = test && POGEL::about(position.y, trail[i].y, pres);
	    test = test && POGEL::about(position.z, trail[i].z, pres);
	    test = test && POGEL::about(rotation.x, rots[i].x, pres);
	    test = test && POGEL::about(rotation.y, rots[i].y, pres);
	    test = test && POGEL::about(rotation.z, rots[i].z, pres);
	    if( test )
	    {
	        ret = true;
	    }
		else
		{
		    return false;
		}
	}

	return ret;
}

bool
POGEL::PHYSICS::SOLID::sameposlegacy(float pres, unsigned long len)
{

    bool ret = false;
	if( trailsize < len )
	{
	    ret = POGEL::about(position.x, trail[trailsize-1].x, pres);
	    ret = ret && POGEL::about(position.y, trail[trailsize-1].y, pres);
	    ret = ret && POGEL::about(position.z, trail[trailsize-1].z, pres);
	    return ret;
	}

	if( stepstaken < len )
	{
	    return false;
	}

	for( unsigned long i = 0; i < len && i < stepstaken + 1; ++i )
	{
	    bool test = POGEL::about(position.x, trail[i].x, pres);
	    test = test && POGEL::about(position.y, trail[i].y, pres);
	    test = test && POGEL::about(position.z, trail[i].z, pres);
	    if( test )
	    {
	        ret = true;
	    }
		else
		{
		    return false;
		}
	}

	return ret;
}

bool
POGEL::PHYSICS::SOLID::samerotlegacy(float pres, unsigned long len)
{
	bool ret = false;
	if( trailsize < len )
	{
	    ret = POGEL::about(rotation.x, rots[trailsize-1].x, pres);
	    ret = ret && POGEL::about(rotation.y, rots[trailsize-1].y, pres);
	    ret = ret && POGEL::about(rotation.z, rots[trailsize-1].z, pres);
	    return ret;
	}

	if( stepstaken < len )
	{
	    return false;
	}

	for( unsigned long i = 0; i < len && i < stepstaken + 1; ++i )
	{
	    bool test = POGEL::about(rotation.x, rots[i].x, pres);
	    test = test && POGEL::about(rotation.y, rots[i].y, pres);
	    test = test && POGEL::about(rotation.z, rots[i].z, pres);
        if( test )
        {
            ret = true;
        }
		else
		{
		    return false;
		}
	}

	return ret;
}

bool
POGEL::PHYSICS::SOLID::samelegacy(float pres, unsigned long len)
{
	bool ret = false;
	if(trailsize < len)
	{
	    ret = POGEL::about(position.x, trail[trailsize-1].x, pres);
	    ret = ret && POGEL::about(position.y, trail[trailsize-1].y, pres);
	    ret = ret && POGEL::about(position.z, trail[trailsize-1].z, pres);
	    ret = ret && POGEL::about(rotation.x, rots[trailsize-1].x, pres);
	    ret = ret && POGEL::about(rotation.y, rots[trailsize-1].y, pres);
	    ret = ret && POGEL::about(rotation.z, rots[trailsize-1].z, pres);
	    return ret;
	}

	if( stepstaken < len )
	{
	    return false;
	}

	for( unsigned long i = 0; i < len && i < stepstaken + 1; ++i )
	{
	    bool test = POGEL::about(position.x, trail[i].x, pres);
	    test = test && POGEL::about(position.y, trail[i].y, pres);
	    test = test && POGEL::about(position.z, trail[i].z, pres);
	    test = test && POGEL::about(rotation.x, rots[i].x, pres);
	    test = test && POGEL::about(rotation.y, rots[i].y, pres);
	    test = test && POGEL::about(rotation.z, rots[i].z, pres);
	    if( test )
	    {
	        ret = true;
	    }
		else
		{
		    return false;
		}
	}

	return ret;
}

void
POGEL::PHYSICS::SOLID::offsettrail(POGEL::VECTOR v)
{
	for( unsigned long i = trailsize-1; i > 0; --i )
	{
	    trail[i] += v;
	}
}

void
POGEL::PHYSICS::SOLID::makebounding()
{
	setboundingskips();

	bool os = false;
	os = os || !bounding.surrounds(POGEL::POINT(),position,refbounding);
	//os = os || !bounding.surrounds(POGEL::POINT(),position+direction*r,refbounding);
	os = os || bounding.isoutside(POGEL::POINT(), position);

	if( stepstaken <= 1 || os || stepstaken == objboundingskips+stepsatboundingcheck )
	{
	    forcegetbounding();
	}
	refbounding.fin();
	bounding.fin();
}

void
POGEL::PHYSICS::SOLID::setboundingskips()
{
    if( getNumVerticies() )
    {
        objboundingskips = 1;
        return;
    }

	float r = ( POGEL::hasproperty(POGEL_TIMEBASIS) ? POGEL::GetSecondsPerFrame() : 1.0f );

	bool os = false;
	os = os || !bounding.surrounds(POGEL::POINT(),position,refbounding);
	os = os || !bounding.surrounds(POGEL::POINT(),position+direction*r,refbounding);
	os = os || bounding.isoutside(POGEL::POINT(), position);

	if( stepstaken >= objboundingskips + stepsatboundingcheck || stepstaken <= 1 || os )
	{
		if( container && container->boundingskips > 0 )
		{
		    objboundingskips = container->boundingskips;
		}
		else if( direction.getdistance() == 0.0f )
		{
		    objboundingskips = 1;
		}
		else
		{
		    objboundingskips = (unsigned long)(1.0f/(direction.getdistance()*r))*2;
		}
	}
	//POGEL::message("%s skps = %u\n",getname(),objboundingskips);
	if( objboundingskips < 1 )
	{
	    objboundingskips = 1;
	}
	//if(objboundingskips > 50) objboundingskips = 1;
}

void
POGEL::PHYSICS::SOLID::forcegetbounding()
{
	float r = (POGEL::hasproperty(POGEL_TIMEBASIS) ? POGEL::GetSecondsPerFrame() : 1.0f)*refbounding.maxdistance;

    unsigned int numverts = getNumVerticies();
    if( numverts )
    {
        POGEL::VERTEX * verts = getVertexListAddress();
        bounding.clear();
        refbounding.clear();
        POGEL::MATRIX mat1(rotation, MATRIX_CONSTRUCT_ROTATION);
        POGEL::MATRIX mat2(direction*(float)objboundingskips*r, rotation + spin*(float)objboundingskips*r);
        for( unsigned long t = 0 ; t < numverts ; ++t )
        {
            POGEL::POINT transpoint( mat1.transformPoint( verts[ t ] ) );
            bounding.addpoint( transpoint );
            refbounding.addpoint( transpoint );
            bounding.finishactual();
            bounding.addpoint( mat2.transformPoint( verts[ t ] ) );
            bounding.unsetactual();
        }
        //bounding.fin();
        bounding.offset(position);
        //refbounding.offset(POGEL::POINT());
        verts = NULL;
        stepsatboundingcheck = stepstaken;
        refbounding.fin();
        bounding.fin();
        return;
    }

    if(stepstaken > 0 && hasOption(PHYSICS_SOLID_SPHERE)) {
		float max = refbounding.maxdistance;
		bounding.clear();
		bounding.addpoint(POGEL::POINT( max, 0, 0));
		bounding.addpoint(POGEL::POINT( 0, max, 0));
		bounding.addpoint(POGEL::POINT( 0, 0, max));
		bounding.addpoint(POGEL::POINT(-max, 0, 0));
		bounding.addpoint(POGEL::POINT( 0,-max, 0));
		bounding.addpoint(POGEL::POINT( 0, 0,-max));

		refbounding.clear();
		refbounding = bounding;
		refbounding.color = BOUNDING_DEFAULT_COLOR;

        POGEL::VECTOR dirtmp = direction*(float)objboundingskips*r;
		bounding.addpoint(dirtmp + POGEL::POINT( max, 0, 0));
		bounding.addpoint(dirtmp + POGEL::POINT( 0, max, 0));
		bounding.addpoint(dirtmp + POGEL::POINT( 0, 0, max));
		bounding.addpoint(dirtmp + POGEL::POINT(-max, 0, 0));
		bounding.addpoint(dirtmp + POGEL::POINT( 0,-max, 0));
		bounding.addpoint(dirtmp + POGEL::POINT( 0, 0,-max));

		bounding.finishactual();
		//bounding.fin();

		bounding.offset(position);
		//refbounding.offset(POGEL::POINT());
		bounding.maxdistance = max;
		refbounding.maxdistance = max;

		stepsatboundingcheck = stepstaken;
		refbounding.fin();
		bounding.fin();
		return;
	}

	bounding.clear();
	refbounding.clear();
	POGEL::MATRIX mat1( rotation, MATRIX_CONSTRUCT_ROTATION );
	POGEL::MATRIX mat2( direction*(float)objboundingskips*r, rotation + spin.topoint()*(float)objboundingskips*r );
	for( unsigned long t = 0 ; t < getnumfaces() ; ++t )
	{
		/*for( unsigned int v = 0 ; v < 3 ; v++ )
		{
		    POGEL::POINT trans = mat1.transformPoint(gettriangle(t).vertex[v]);
			bounding.addpoint(POGEL::POINT(), trans);
			refbounding.addpoint(POGEL::POINT(), trans);
			bounding.finishactual();
			bounding.addpoint(POGEL::POINT(), mat2.transformPoint(gettriangle(t).vertex[v]));
			bounding.unsetactual();
		}*/
		POGEL::POINT mid( gettriangle( t ).middle() );
		POGEL::POINT trans( mat1.transformPoint( mid ) );
        bounding.addpoint( trans );
        refbounding.addpoint( trans );
        bounding.finishactual();
        bounding.addpoint( mat2.transformPoint( mid ) );
        bounding.unsetactual();
	}
	//bounding.fin();
	bounding.offset( position );
	//refbounding.offset( POGEL::POINT() );

	stepsatboundingcheck = stepstaken;
    refbounding.fin();
    bounding.fin();
}

POGEL::COLOR
POGEL::PHYSICS::SOLID::getLabelColor()
{
	if( behavior.magnetic && behavior.charge != 0.0f )
	{
			if( behavior.charge < 0.0f )
			{
			    return POGEL::COLOR( 1,.5,.2,1);
			}
			else
			{
			    return POGEL::COLOR(.5, 1,.2,1);
			}
    }
    else if( sleeping )
    {
        return POGEL::COLOR( 1, 0,.5,1);
    }
	return POGEL::COLOR(.2,.5, 1,1);
}

void
POGEL::PHYSICS::SOLID::build()
{
	POGEL::OBJECT::build();

	forcegetbounding();

	trianglestring.clear();

	for(unsigned long a = 0; a < getnumfaces(); a++)
	{
	    //trianglestring += gettriangle(a).toString()+(a<getnumfaces()-1 ? ",":"");
	}
}

void
POGEL::PHYSICS::SOLID::setAnimationTime( float time )
{
    POGEL::OBJECT::setAnimationTime( time );
}

void
POGEL::PHYSICS::SOLID::draw()
{
	#ifdef OPENGL
	unsigned int prp = POGEL::getproperties();
	if( POGEL::hasproperty(POGEL_LABEL) )
	{
	    POGEL::removeproperty(POGEL_LABEL);
	}

	POGEL::OBJECT::draw();

	POGEL::setproperties(prp);

	glLineWidth(2);
	bounding.draw(POGEL::POINT());
	glLineWidth(1);

	refbounding.draw(position);

	/*if(facetree&&getNumFrames())
	{
        glTranslatef(position.x, position.y, position.z);
        glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	    facetree->draw();
	    glRotatef(rotation.z, 0.0f, 0.0f, -1.0f);
        glRotatef(rotation.y, 0.0f, -1.0f, 0.0f);
        glRotatef(rotation.x, -1.0f, 0.0f, 0.0f);
        glTranslatef(-position.x, -position.y, -position.z);
	}*/

	if( POGEL::hasproperty(POGEL_LABEL) )
	{
		/*POGEL::LINE( position,
			position + (direction*2*(POGEL::hasproperty(POGEL_TIMEBASIS) ? POGEL::GetSecondsPerFrame() : 1) ),
			1, POGEL::COLOR( 1,.5, 0, 1) ).draw();*/
		position.draw(2, getLabelColor());
	}

	if( POGEL::hasproperty(POGEL_TRAILS) )
	{
		#ifdef SOLID_DISPLAY_ROTATION_TRAIL
			POGEL::MATRIX mat[2];
			mat[1] = POGEL::MATRIX(rots[0], MATRIX_CONSTRUCT_ROTATION);
			float len = bounding.maxdistance*1.1f;

			#ifdef SOLID_DISPLAY_STIPPLED_NEGATIVE_ROTATION_TRAIL
				glLineStipple(2, 0x1111);
			#endif /* SOLID_DISPLAY_STIPPLED_NEGATIVE_ROTATION_TRAIL */
		#endif /* SOLID_DISPLAY_ROTATION_TRAIL */
        unsigned trailSkip = PHYSICS_SOLID_TRAILSKIP;
		for(unsigned int i = 0 ; i < trailsize-1 && i < stepstaken && i < 64; i+=trailSkip) {
			float color = 1.0f;
			#ifdef SOLID_DISPLAY_TRAIL_FADING
				//if(trailsize - 1 < 64)
				if(trailsize - 1 < stepstaken)
					color = ((float)(( trailsize-1 )-i)/(float)( trailsize-1 ));
				//else
					//color = ((float)(( stepstaken-1 )-i)/(float)( stepstaken-1 ));
				else
					color = ((float)(( 64 )-i)/(float)( 64 ));
			#endif /* SOLID_DISPLAY_TRAIL_FADING */

			//if((stepstaken-i)%16==0) trail[i].draw(3, POGEL::COLOR(1,1,0,color));

			//if(trail[i].distance(trail[i+trailSkip]) > 1) continue;

			POGEL::LINE(trail[i], trail[i+trailSkip], 1, POGEL::COLOR(1,1,0,color)).draw(); // draw the position trail

			#ifdef SOLID_DISPLAY_ROTATION_TRAIL // draw the rotation trail
			if(!hasproperty(OBJECT_ROTATE_TOCAMERA)) {
				mat[0] = mat[1];
				mat[1] = POGEL::MATRIX(rots[i+trailSkip], MATRIX_CONSTRUCT_ROTATION);
				POGEL::POINT x[3], y[3], z[3];
				x[0] = y[0] = z[0] = POGEL::POINT();

				for(int a = 0; a < 2; a++) {
					x[a+1] = mat[a+0].transformPoint(POGEL::POINT(len,0,0));
					y[a+1] = mat[a+0].transformPoint(POGEL::POINT(0,len,0));
					z[a+1] = mat[a+0].transformPoint(POGEL::POINT(0,0,len));
				}

				for(int a = ((stepstaken-i)%16==0 ? 0 : 1); a < 2; a++) {
					POGEL::LINE(trail[i]+x[a], trail[i+a]+x[a+1], POGEL::COLOR(1,0,0,color)).draw(); // x axis positive
					POGEL::LINE(trail[i]+y[a], trail[i+a]+y[a+1], POGEL::COLOR(0,1,0,color)).draw(); // y axis positive
					POGEL::LINE(trail[i]+z[a], trail[i+a]+z[a+1], POGEL::COLOR(0,0,1,color)).draw(); // z axis positive

					#ifdef SOLID_DISPLAY_NEGATIVE_ROTATION_TRAIL // the negative rotation trail
						#ifdef SOLID_DISPLAY_STIPPLED_NEGATIVE_ROTATION_TRAIL
							glEnable(GL_LINE_STIPPLE);
						#endif

						POGEL::LINE(trail[i]-x[a], trail[i+a]-x[a+1], POGEL::COLOR( 1,.5,.5,color)).draw(); // x axis negative
						POGEL::LINE(trail[i]-y[a], trail[i+a]-y[a+1], POGEL::COLOR(.5, 1,.5,color)).draw(); // y axis negative
						POGEL::LINE(trail[i]-z[a], trail[i+a]-z[a+1], POGEL::COLOR(.5,.5, 1,color)).draw(); // z axis negative

						#ifdef SOLID_DISPLAY_STIPPLED_NEGATIVE_ROTATION_TRAIL
							glDisable(GL_LINE_STIPPLE);
						#endif /* SOLID_DISPLAY_STIPPLED_NEGATIVE_ROTATION_TRAIL */
					#endif /* SOLID_DISPLAY_NEGATIVE_ROTATION_TRAIL */

				}
			}
			#endif /* SOLID_DISPLAY_ROTATION_TRAIL */
		}

		POGEL::COLOR(1,1,1,1).set(); // catch any erronious coloration mistakes

		#ifdef SOLID_DISPLAY_STIPPLED_NEGATIVE_ROTATION_TRAIL
			glDisable(GL_LINE_STIPPLE);
			glLineStipple(1, 0xFFFF);
		#endif /* SOLID_DISPLAY_STIPPLED_NEGATIVE_ROTATION_TRAIL */
	}
	#endif
};

void
POGEL::PHYSICS::SOLID::increment()
{
	float r = PARTICLE_SLOWDOWN;
	rotate(spin*r);
	translate(direction*r);
	//matrix = POGEL::MATRIX(position,rotation);
	//force = POGEL::VECTOR();
	stepstaken++;

    /*if(getNumFrames())
    {
        while(facelist.length() < numfaces)
        {
            facelist += &face[facelist.length()];
        }
        if(facetree!=NULL)
        {
            delete facetree;
            //facetree = NULL;
        }
        //if(facetree==NULL)
        {
            facetree = new POGEL::OCTREE<POGEL::TRIANGLE>( &facelist, 16, true );
            facetree->grow();
            //POGEL::addproperty(POGEL_BOUNDING);
            //facetree->draw();
        }
    }*/
}

void
POGEL::PHYSICS::SOLID::clearForce()
{
    force = POGEL::VECTOR();
}

void
POGEL::PHYSICS::SOLID::addForce()
{
	if( !this->hasOption(PHYSICS_SOLID_STATIONARY) )
	{
	    direction += force;
	}
}

void
POGEL::PHYSICS::SOLID::step()
{
	increment();
	steptrail();
	makebounding();
	if( function )
	{
	    (*function)(this);
	}
}

void
POGEL::PHYSICS::SOLID::closest(POGEL::POINT point, POGEL::POINT* objpt, POGEL::TRIANGLE* tri)
{
    if( !objpt && !tri )
    {
        return;
    }

    unsigned int numfaces = getnumfaces();
    if( !numfaces )
    {
        *objpt = position;
        tri = NULL;
        return;
    }

    //POGEL::MATRIX mat( position, rotation );

    POGEL::TRIANGLE tritmp = matrix.transformTriangle( gettriangle(0) );

    float dist = point_triangle_distance( point, tritmp, objpt );
    if( tri )
    {
        *tri = tritmp;
    }

    POGEL::POINT p;
    float d = dist;

    if( false && facetree && point.distance( position ) < bounding.maxdistance )
    {
        POGEL::MATRIX mat = matrix;
        mat.invert();
        POGEL::BOUNDING bound;
        bound.max = bound.min = mat.transformPoint( point );
        bound.fin( bounding.maxdistance * 0.1f );
        /*bound.max += POGEL::POINT(bounding.maxdistance*0.01f);
        bound.min -= POGEL::POINT(bounding.maxdistance*0.01f);*/
        CLASSLIST<unsigned int> * indices = facetree->releventIndicies( bound );
        if( indices->length() )
        {
            for( unsigned long a = 0; a < indices->length(); ++a )
            {
                tritmp = matrix.transformTriangle( gettriangle( indices->get( a ) ) );
                if( tritmp.isinfront(point) || tritmp.middle().distance(point) - tritmp.bounding.maxdistance >= dist )
                {
                    continue;
                }
                d = point_triangle_distance( point, tritmp, &p );
                if( d < dist )
                {
                    dist = d;
                    if( objpt )
                    {
                        *objpt = p;
                    }
                    if( tri )
                    {
                        *tri = tritmp;
                    }
                }
            }
            /*delete indices;
            return;*/
        }
        delete indices;
        return;
    }

    POGEL::MATRIX mat( matrix );
    mat.invert();
    POGEL::POINT trp = mat.transformPoint( point );

    for( unsigned long a = 1; a < numfaces; ++a )
    {
        POGEL::TRIANGLE tri2 = gettriangle( a );
        float disttmp = tri2.bounding.maxdistance + dist;
        if( tri2.isinfront( trp ) || tri2.middle().distancesquared( trp ) >= disttmp * disttmp )
        {
            continue;
        }
        tritmp = matrix.transformTriangle( tri2 );
        d = point_triangle_distance( point, tritmp, &p );
        if( d < dist )
        {
            dist = d;
            if( objpt )
            {
                *objpt = p;
            }
            if( tri )
            {
                *tri = tritmp;
            }
        }
    }
}

void
POGEL::PHYSICS::SOLID::closest(POGEL::PHYSICS::SOLID* other, POGEL::POINT* obj1pt, POGEL::POINT* obj2pt, POGEL::TRIANGLE* tri1, POGEL::TRIANGLE* tri2)
{

	*obj1pt = this->position;
	*obj2pt = other->position;
	POGEL::POINT obj1ptold = *obj2pt, obj2ptold = *obj1pt;
	unsigned int c = 0;
	bool done = false;
	while(c++ < 5 && !done)
	{
		//POGEL::message("%f, %f\n", obj1ptold.distance(*obj1pt), obj2ptold.distance(*obj2pt));
		obj1ptold = *obj1pt; obj2ptold = *obj2pt;
		other->closest(*obj1pt, obj2pt, tri2);
		this->closest(*obj2pt, obj1pt, tri1);
		done = !(obj1ptold.distance(*obj1pt) > 0.0f && obj2ptold.distance(*obj2pt) > 0.0f && (obj1ptold != *obj1pt && obj2ptold != *obj2pt));
	}
	//POGEL::LINE(*obj1pt, *obj2pt, POGEL::COLOR(0,1,0,1)).draw();
}

void
POGEL::PHYSICS::SOLID::cleartriangles()
{
	trianglestring.clear();
	POGEL::OBJECT::cleartriangles();
}

std::string
POGEL::PHYSICS::SOLID::toString()
{
	char *pprp   = POGEL::string("%u",getOptions()),  *prp    = POGEL::string("%u",getproperties());
	char *slping = POGEL::string("%d",(int)sleeping), *cntslp = POGEL::string("%d",(int)cantsleep);
	std::string s =
		"{"
			"[" + getsname()           + "],"
			"[" + std::string(pprp)    + "],"
			"[" + std::string(prp)     + "],"
			"[" + std::string(slping)  + "],"
			"[" + std::string(cntslp)  + "],"
			""  + position.toString()  + ","
			""  + rotation.toString()  + ","
			""  + direction.toString() + ","
			""  + spin.toString()      + ","
			""  + behavior.toString()  + ","
			"<" + trianglestring       + ">"
		"}";
	free(pprp); free(prp); free(slping); free(cntslp);
	return s;
};

