#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "object_class.h"
#include "../pogel_internals.h"

#include "../templates/classlist_template.h"
#include "../templates/bitlist.h"

POGEL::OBJECT::OBJECT()
{
    // allocate only one triangle
    face = new POGEL::TRIANGLE[1];
    // but say there are none
    numfaces = triangle_allocation_total = 0;
    // set the opengl display list to null
    base = (unsigned int)NULL;
    // set zero position and rotation
    position = rotation = POGEL::POINT();
    // set the list of children to null
    children = NULL;
    // thera are no children
    numchildren = 0;
    // no properties
    properties = 0;
    // no name
    name = (char*)NULL;
    // no parent
    root = parent = (POGEL::OBJECT*)NULL;
    // it can be seen, but there is nothing to be seen
    visable = true;
    currentAnimationLoopIndex = -1;
    currentAnimationLoopStartTime = -1.0f;

    numFrames = 0;

    // execute the 'overloaded' create() metho
    create();
}

POGEL::OBJECT::OBJECT(unsigned int prop)
{
    face = new POGEL::TRIANGLE[1];
    numfaces = triangle_allocation_total = 0;
    base = (unsigned int)NULL;
    position = rotation = POGEL::POINT();
    children = NULL;
    numchildren = 0;

    // set the properties to prop
    properties = prop;

    name = (char*)NULL;
    root = parent = (POGEL::OBJECT*)NULL;
    visable = true;
    currentAnimationLoopIndex = -1;
    currentAnimationLoopStartTime = -1.0f;
    create();
}

POGEL::OBJECT::OBJECT(POGEL::TRIANGLE *tri, unsigned long num, unsigned int prop)
{
    numfaces = triangle_allocation_total = 0;
    base = (unsigned int)NULL;
    position = rotation = POGEL::POINT();
    children = NULL;
    numchildren = 0;

    // set properties to prop
    properties = prop;

    // add the list of triangles
    addtriangles(tri,num);

    name = (char*)NULL;
    root = parent = (POGEL::OBJECT*)NULL;
    visable = true;
    currentAnimationLoopIndex = -1;
    currentAnimationLoopStartTime = -1.0f;
    create();
}

POGEL::OBJECT::OBJECT(POGEL::TRIANGLE *tri, unsigned long num, unsigned int prop, POGEL::POINT pos, POGEL::POINT rot)
{
    numfaces = triangle_allocation_total = 0;
    base = (unsigned int)NULL;

    // set the position to pos
    position = pos;
    // set the rotation to rot
    rotation = rot;

    children = NULL;
    numchildren = 0;

    // set the properties to prop
    properties = prop;

    // add the list of triangles
    addtriangles(tri,num);

    name = (char*)NULL;
    root = parent = (POGEL::OBJECT*)NULL;
    visable = true;
    currentAnimationLoopIndex = -1;
    currentAnimationLoopStartTime = -1.0f;
    create();
}

POGEL::OBJECT::OBJECT(const char* n)
{
    face=new POGEL::TRIANGLE[1];
    numfaces = triangle_allocation_total = 0;
    base=(unsigned int)NULL;
    position = rotation = POGEL::POINT();
    children = NULL;
    numchildren = 0;
    properties = (unsigned int)NULL;

    // set the name to n
    //name = (char*)n;
    name = strcpy( new char[ strlen(n) ], n );

    root = parent = (POGEL::OBJECT*)NULL;
    visable = true;
    currentAnimationLoopIndex = -1;
    currentAnimationLoopStartTime = -1.0f;
    create();
}

POGEL::OBJECT::OBJECT(const char* n, unsigned int prop)
{
    face=new POGEL::TRIANGLE[1];
    numfaces = triangle_allocation_total = 0;
    base=(unsigned int)NULL;
    position = rotation = POGEL::POINT();
    children = NULL;
    numchildren = 0;

    // set the properties to prop
    properties = prop;

    // set the name to n
    name = (char*)n;

    root = parent = (POGEL::OBJECT*)NULL;
    visable = true;
    currentAnimationLoopIndex = -1;
    currentAnimationLoopStartTime = -1.0f;
    create();
}

POGEL::OBJECT::OBJECT(const char* n, POGEL::TRIANGLE *tri, unsigned long num, unsigned int prop)
{
    numfaces = triangle_allocation_total = 0;
    base = (unsigned int)NULL;
    position = rotation = POGEL::POINT();
    children = NULL;
    numchildren = 0;

    // set properties to prop
    properties = prop;

    // add the triangle list
    addtriangles(tri,num);

    // set the name to n
    name = (char*)n;

    root = parent = (POGEL::OBJECT*)NULL;
    visable = true;
    currentAnimationLoopIndex = -1;
    currentAnimationLoopStartTime = -1.0f;
    create();
}

POGEL::OBJECT::OBJECT(const char* n, POGEL::TRIANGLE *tri, unsigned long num, unsigned int prop, POGEL::POINT pos, POGEL::POINT rot)
{

    numfaces = triangle_allocation_total = 0;
    base = (unsigned int)NULL;

    // set position to pos
    position = pos;

    // set rotation to rot
    rotation = rot;

    children = NULL;
    numchildren = 0;

    // set properties to prop
    properties = prop;

    // add the triangles
    addtriangles(tri,num);

    // set name to n
    name = (char*)n;

    root = parent = (POGEL::OBJECT*)NULL;
    visable = true;
    currentAnimationLoopIndex = -1;
    currentAnimationLoopStartTime = -1.0f;
    create();
}

POGEL::OBJECT::OBJECT(POGEL::OBJECT * obj)
{
    // copy everything from obj, kind of dangerous
    face=obj->face;
    numfaces=obj->numfaces;
    triangle_allocation_total=obj->triangle_allocation_total;
    children=obj->children;
    parent=obj->parent;
    numchildren=obj->numchildren;
    for( unsigned int i = 0; i < numchildren; i++ )
    {
        children[i]->parent = this;
    }
    name=obj->name;
    properties=obj->properties;
    position=obj->position;
    rotation=obj->rotation;
    base=obj->base;
    matrix=obj->matrix;
    visable=obj->visable;

    //root=obj->root; // is this safe?
}

POGEL::OBJECT::~OBJECT()
{
    // call the objects 'overloaded' destruction method
    destroy();

    // get the objects name as an ancestory
    char *n = getancestoryhash();

    // tell the user what you are doung
    POGEL::message("deconstructing %s\n", n);

    // check if the objects name is not its own, prevents crashes,
    // name will be deleted later

    if( n != getname() )
    {
        // free the ancestoral name
        delete [] n;
    }

    // if the list of triangles is not empty
    if( face != NULL )
    {
        // delete it
        delete [] face;
    }

    // and nullify it
    face = NULL;

    // if the list of child objects is not empth
    if( children != NULL )
    {
        // kill the children
        killchildren();

        // if the list of children is not null
        if( children )
        {
            // nullify it
            children = NULL;
        }
    }

    // nullify it
    children = NULL;

    // set the pointer to the parent as null
    root = parent = NULL;

    // if the name is not null
    if( name )
    {
        // delete it, told you
        delete [] name;

        // set it to null
        name = NULL;
    }

    verticies.clear();
    verticiesTrans.clear();

    // if the joints exist
    if( joints.length() )
    {
        // clear them
        joints.clear();
    }

    posKeys.clear();
    rotKeys.clear();
    scaleKeys.clear();
    tangents.clear();
    animations.clear();

    trisortfaces1.clear();
    trisortfaces2.clear();
}

void
POGEL::OBJECT::killchildren()
{
    // if this object has any children
    if( numchildren > 0 && children != NULL )
    {
        // loop through them
        for( unsigned long i = 0; i < numchildren; i++ )
        {
            // if the pointer is not null
            if( children[i] )
            {
                // kill their children
                children[i]->killchildren();

                // delete the current child
                //delete children[i];

                // nullify it
                children[i] = NULL;
            }
        }
    }

    numchildren = 0;

    // if the list is not null
    if(children)
    {
        // delete the list of children
        delete[] children;

        // nullify it
        children=NULL;
    }
}

void
POGEL::OBJECT::derefference()
{
    // if the list is not null
    if(children)
    {
        // nullify it
        children=NULL;
    }

    if( face )
    {
        face = NULL;
    }

    if( parent )
    {
        parent = NULL;
    }

    if( root )
    {
        root = NULL;
    }

    verticies.clear();
    verticiesTrans.clear();

    // if the joints exist
    if( joints.length() )
    {
        // clear them
        joints.clear();
    }

    posKeys.clear();
    rotKeys.clear();
    scaleKeys.clear();
    tangents.clear();
}

void
POGEL::OBJECT::setname(const char *n)
{
    // if the current name is non-null
    if( name != NULL )
    {
        // delete it
        delete [] name;
    }

    // allocate new space
    name = new char[strlen(n)];

    // copy the new name into the new space
    strcpy(name, n);
}

char*
POGEL::OBJECT::getname()
{
    // just return the name, why do i need this comment?
    return name;
}

std::string
POGEL::OBJECT::getsname()
{
    // return the name as a c++ string
    return std::string(name);
}

void
POGEL::OBJECT::translate( const POGEL::VECTOR& v )
{
    // ensure the given value is non-toxic
    if( !v.isbad() )
    {
        // add the value to the objects position
        position += v;
    }
}

void
POGEL::OBJECT::translate( const POGEL::VECTOR& v, float s )
{
    // translate by v scaled by s
    translate(v*s);
}

void
POGEL::OBJECT::moveto( const POGEL::POINT& p )
{
    // set the position to p
    position = p;
}

void
POGEL::OBJECT::rotate( const POGEL::VECTOR& v )
{
    // ensure the given value is non-toxic
    if(!v.isbad())
    {
        // add the value to the objects rotation
        rotation += v;
    }
}

void
POGEL::OBJECT::rotate( const POGEL::VECTOR& v, float s )
{
    // rotate by v scaled by s
    rotate(v*s);
}

void
POGEL::OBJECT::turnto( const POGEL::POINT& r )
{
    // set the rotation to r
    rotation = r;
}

unsigned long
POGEL::OBJECT::addtriangle( const POGEL::TRIANGLE& tri )
{
    // if the triangle has zero area
    if( (tri.vertex[0] == tri.vertex[1]) || (tri.vertex[0] == tri.vertex[2]) || (tri.vertex[1] == tri.vertex[2]) )
    {
        // do not add it, and return null, which is 0, not uesfull but somewhat required
        return (unsigned long)NULL;
    }

    // if the number of triangle faces exceeds that of the preallocated total
    if( numfaces >= triangle_allocation_total )
    {
        // add a predefined ammount of more space
        addtrianglespace(OBJECT_TRIAGLE_ALLOCATION_SKIP);
    }

    // set the new triangle as the last triangle in the list
    face[numfaces]=tri;

    // incriment the number of usable triangle faces
    // return the index of the newly added triangle
    return numfaces++;
}

void
POGEL::OBJECT::addtriangles(POGEL::TRIANGLE *tri, unsigned long num)
{
    // if pointer to triangles is null
    if( tri == (POGEL::TRIANGLE*)NULL )
    {
        // kill program
        POGEL::fatality(POGEL_FATALITY_NULL_ARRAY_POINTER_RETNUM,"%s to Triangle(s).",POGEL_FATALITY_NULL_ARRAY_POINTER_STRING);
    }

    // add space for the new triangles
    addtrianglespace( num );

    // go through the given list
    for( unsigned long i = 0; i < num; ++i )
    {
        // add each individual triangle
        addtriangle( tri[i] );
    }
}

void
POGEL::OBJECT::addtrianglespace(unsigned long num)
{
    // new list of faces with extra space
    POGEL::TRIANGLE * tmp = new POGEL::TRIANGLE[numfaces+num];

    // if current list of triangles exists
    if( face != NULL )
    {
        // copy the old list into the new list
        for( unsigned long i = 0; i < numfaces; i++ )
        {
            tmp[i] = face[i];
        }

        // if the list of triangles has data in it
        if( face != NULL && numfaces != 0 && triangle_allocation_total != 0 )
        {
            // delete the old list
            delete[] face;
        }

        // nullify the old list
        face = NULL;
    }

    // set the new list to the old list
    face = tmp;

    // add the number of new triangles to the total number of pre allocated faces
    triangle_allocation_total += num;
}

void
POGEL::OBJECT::cleartriangles()
{
    // delete the list of triangle faces
    if( face )
        delete[] face;
    // set the list to null
    face = NULL;
    // set the number of faces and the number of preallocated slots to zero
    numfaces = triangle_allocation_total = 0;
}

unsigned long
POGEL::OBJECT::addobject(POGEL::OBJECT *obj)
{
    // if given object pointer is null
    if( obj == (POGEL::OBJECT*)NULL )
    {
        // kill program
        POGEL::fatality(POGEL_FATALITY_NULL_OBJECT_POINTER_RETNUM,"%s to object.",POGEL_FATALITY_NULL_OBJECT_POINTER_STRING);
    }

    // create temporary object list
    POGEL::OBJECT **tmp = new POGEL::OBJECT*[numchildren+1];

    // go through all children
    for( unsigned long i = 0; i < numchildren; i++ )
    {
        // copy each child into the temporary list
        tmp[i]=children[i];
        // then nullify the child pointer
        children[i] = NULL;
    }

    // add the given object to the temporary child list
    tmp[numchildren]=obj;

    // set its parent to this object
    tmp[numchildren]->parent=this;

    // delete old list of child objects
    delete[] children;

    // set the temporary list as the list of children
    children = tmp;

    // add one to the number of child objects
    // return the newest child objects index in the list of children
    return numchildren++;
};

void
POGEL::OBJECT::addobjects(POGEL::OBJECT **obj, unsigned long num)
{
    // if the given pointer is null
    if( obj == (POGEL::OBJECT**)NULL )
    {
        // kill program
        POGEL::fatality(POGEL_FATALITY_NULL_ARRAY_POINTER_RETNUM,"%s to object(s).",POGEL_FATALITY_NULL_ARRAY_POINTER_STRING);
    }
    // loop through all the given object pointers
    for(unsigned long i=0;i<num;i++)
    {
        // add the object
        addobject( obj[i] );
    }
}

void
POGEL::OBJECT::scroll_all_tex_values(float s, float t)
{
    // loop through all the triangles
    for( unsigned long i = 0; i < numfaces; ++i )
    {
        // scroll thier texture values
        face[ i ].scroll_tex_values( s, t );
    }
}

POGEL::OBJECT*
POGEL::OBJECT::getchild(const char* n)
{
    // loop through all the children
    for( unsigned long i = 0; i < numchildren; i++ )
    {
        // if the childs name matches the desired one
        if( strlen(n) == strlen(children[i]->getname()) && strcmp(n,children[i]->getname()) == 0 )
        {
            // return it
            return children[i];
        }
    }
    // otherwise null
    return NULL;
}

POGEL::OBJECT*
POGEL::OBJECT::getdecendant( const char * n, bool self )
{
    POGEL::OBJECT * child = getchild(n);
    // if the decendant you are looking for is this object
    if( self && strlen(n) == strlen(getname()) && strcmp(getname(), n) == 0 )
    {
        // return this
        return this;
    }
    // if the decendant is an imediate child
    else if( child != NULL )
    {
        // return it
        return child;
    }
    // if the desired object is not an imediate child
    else if( child == NULL )
    {
        // loop throgh all the children
        for( unsigned long i = 0; i < numchildren; i++ )
        {
            POGEL::OBJECT * decendant = children[i]->getdecendant(n);
            // if the desired object is one of the childrens decendants
            if( decendant != NULL )
            {
                // return the childs decendant
                return decendant;
            }
        }
    }
    // otherwise null
    return NULL;
}

POGEL::OBJECT*
POGEL::OBJECT::getdecendant(const char* n)
{
    // same as above but it can always check for itself
    return getdecendant(n,true);
}

POGEL::OBJECT*
POGEL::OBJECT::getprogenitor()
{
    // if this object has no parent
    if( parent == NULL )
    {
        // return this object
        return this;
    }
    // if this object has a parent
    else if( parent != NULL )
    {
        // return the parents progenitor
        return parent->getprogenitor();
    }
    // otherwise null
    return NULL;
}

POGEL::OBJECT*
POGEL::OBJECT::getancestor(const char *n)
{
    // if this object is the object you are looking for
    if( strlen(getname()) == strlen(n) && strcmp(getname(), n) == 0 )
    {
        // return this object
        return this;
    }
    // if this object has a parent
    else if( parent != NULL )
    {
        // return the parents ancestor with name 'n'
        return parent->getancestor(n);
    }
    // otherwise null
    return NULL;
}

char*
POGEL::OBJECT::getancestory()
{
    // if this object has no parent
    if( parent == NULL )
    {
        // it is the first one, return its name
        return getname();
    }
    // if it has a parent
    else if( parent != NULL )
    {
        // get the parents ancestory
        char * n = parent->getancestory();
        // concatinate it with the current objects name
        char * ret = POGEL::string( "%s -> %s", n, getname() );
        // if the address of n does not equal the adress of the parents name string
        if( n != parent->getname() )
        {
            // free n (prevents manny memmory leaks)
            free(n);
        }
        // and return
        return ret;
    }
    POGEL::error("object: \"%s\" has corrupted pointer to parent object.", getname());
    POGEL::warning("nonfatal, continuing");
    // otherwise complain
    return (char*)"ERROR";
}

char*
POGEL::OBJECT::getancestoryhash()
{
    // if this object has no parent
    if( parent == NULL )
    {
        // it is the first one, return its name
        return getname();
    }
    // if it has a parent
    else if( parent != NULL )
    {
        // get the parents ancestory
        char * n = parent->getancestoryhash();
        // concatinate it with the current objects name
        char * ret = POGEL::string("%s:%x", n, getchildslot());
        // if the address of n does not equal the adress of the parents name string
        if( n != parent->getname() )
        {
            // free n (prevents many memmory leaks)
            delete [] n;
        }
        // and return
        return ret;
    }
    POGEL::error("object: \"%s\" has corrupted pointer to parent object.",getname());
    POGEL::warning("nonfatal, continuing");
    // otherwise complain
    return (char*)"ERROR";
}

unsigned long
POGEL::OBJECT::getchildslot()
{
    // if this object is a child
    if( parent != NULL )
    {
        // loop through all the children
        for( unsigned long i = 0; i < parent->numchildren; i++ )
        {
            // if the childs name matches the desired one
            if( parent->children[i] == this )
            {
                // return the relevent index
                return i;
            }
        }
    }
    // since this object has no parents it is the first child
    return 0;
}

POGEL::MATRIX
POGEL::OBJECT::getancestorialmatrix()
{
    // no parent
    if( parent == NULL )
    {
        // return this matrix
        return POGEL::MATRIX(position, rotation);
    }
    // otherwise multiply this objects matrix by its ancestors and return it
    return parent->getancestorialmatrix() * POGEL::MATRIX(position, rotation);
}

POGEL::MATRIX
POGEL::OBJECT::getinternalancestorialmatrix()
{
    // no parent
    if( parent == NULL )
    {
        // return this objects internal matrix
        return this->matrix;
    }
    // otherwise multiply this objects internal matrix by its ancestors and return it
    return parent->getinternalancestorialmatrix() * this->matrix;
}

unsigned long
POGEL::OBJECT::getnumfaces()
{
    // retrun the number of faces
    return numfaces;
}

POGEL::TRIANGLE
POGEL::OBJECT::gettriangle(unsigned long i)
{
    // retrun the triangle at the given index, no safety, not good
    return face[i];
}

POGEL::TRIANGLE*
POGEL::OBJECT::gettrianglelist()
{
    // return the pointer to the list of triangles,
    // dangerous but i don't care, 'cause it will not be my fault
    return face;
}

void
POGEL::OBJECT::copytriangles(POGEL::OBJECT* o)
{
    // copy the triangles from the other object
    this->addtriangles(o->gettrianglelist(), o->getnumfaces());
}

void
POGEL::OBJECT::referencetriangles(POGEL::OBJECT* o)
{
    // clear this object's triangle list
    cleartriangles();

    // make this object's list of triangles the same pointer as the other object
    // carefull when deleating this object or the other object
    face = o->gettrianglelist();

    // same with the number of faces
    numfaces = o->getnumfaces();

    // and again
    triangle_allocation_total = o->triangle_allocation_total;
}

void
POGEL::OBJECT::stealtriangles( POGEL::OBJECT * o )
{
    this->copytriangles(o);
    o->cleartriangles();
}

void
POGEL::OBJECT::settriangle(unsigned long i, const POGEL::TRIANGLE& t )
{
    // set the triagnle at index i, to the triangle t
    face[i] = t;
}

void
POGEL::OBJECT::settriangle(unsigned long i, POGEL::TRIANGLE * t)
{
    // set the triagnle at index i, to the triangle t
    face[i] = *t;
}

unsigned int
POGEL::OBJECT::getNumChildren() const
{
    return numchildren;
}

POGEL::OBJECT *
POGEL::OBJECT::getChild( unsigned int i ) const
{
    if( i >= numchildren )
    {
        return NULL;
    }
    return children[ i ];
}

void
POGEL::OBJECT::stealChildren( POGEL::OBJECT * other )
{
    this->addobjects( other->children, other->numchildren );
    other->numchildren = 0;
    if(other->children)
    delete [] other->children;
    other->children = NULL;
}

void
POGEL::OBJECT::setNumFrames( unsigned int f )
{
    numFrames = f;
}

void
POGEL::OBJECT::setAnimationFPS( float fps )
{
    animationFPS = fps;
}

unsigned int
POGEL::OBJECT::addVertex( const POGEL::VERTEX& vert )
{
    verticies += vert;
    verticiesTrans += vert;
    return verticies.length() - 1;
}

POGEL::VERTEX *
POGEL::OBJECT::getVertexAddress( unsigned int address ) const
{
    if( address >= verticiesTrans.length() )
    {
        return NULL;
    }

    return verticiesTrans.getaddress(address);
}

POGEL::VERTEX *
POGEL::OBJECT::getVertexListAddress()
{
    return verticiesTrans.getList();
}

unsigned int
POGEL::OBJECT::getNumVerticies()
{
    return verticies.length();
}

unsigned int
POGEL::OBJECT::addPosKey( const POGEL::KEY& key )
{
    posKeys += key;
    return posKeys.length() - 1;
}

unsigned int
POGEL::OBJECT::addRotKey( const POGEL::KEY& key )
{
    rotKeys += key;
    return rotKeys.length() - 1;
}

unsigned int
POGEL::OBJECT::addScaleKey( const POGEL::KEY& key )
{
    scaleKeys += key;
    return scaleKeys.length() - 1;
}

unsigned int
POGEL::OBJECT::addTangent( const POGEL::TANGENT& tan )
{
    tangents += tan;
    return tangents.length() - 1;
}

unsigned int
POGEL::OBJECT::addJoint( POGEL::OBJECT * j, const char * pname )
{
    POGEL::OBJECT * progen = this->getprogenitor();
    if( this != progen )
    {
        throw -1;
    }

    progen->joints += j;
    unsigned int len = progen->joints.length();

    if( pname != NULL)
    {
        POGEL::OBJECT * dec = progen->getdecendant(pname);
        if( dec == NULL )
        {
            for( unsigned int i = 0; i < len; i++)
            {
                if( std::string(pname).compare(joints[i]->getsname()) == 0 )
                {
                    dec = joints[i];
                }
            }

            if( dec == NULL )
            {
                cout << "ERR: " << pname << " not found!" << endl;
                throw -2;
            }
        }
        dec->addobject(j);
    }

    return len - 1;
}

POGEL::OBJECT *
POGEL::OBJECT::getJoint( const char * jointname )
{
    if( jointname == NULL )
    {
        return NULL;
    }

    for( unsigned int i = 0; i < joints.length(); ++i )
    {
        if( std::string( jointname ).compare( joints[ i ]->getsname() ) == 0 )
        {
            return joints[ i ];
        }
    }

    return NULL;
}

float
POGEL::OBJECT::getAnimationFPS() const
{
    return animationFPS;
}

unsigned int
POGEL::OBJECT::getNumFrames()
{
    return numFrames;
}

void
POGEL::OBJECT::copyAnimation( POGEL::OBJECT * other )
{
    this->joints.clear();
    this->posKeys.clear();
    this->rotKeys.clear();
    this->scaleKeys.clear();
    this->tangents.clear();
    this->verticies.clear();

    if( other == NULL )
    {
        return;
    }

    this->numFrames = other->numFrames;
    this->animationFPS = other->animationFPS;
    this->matLocal = other->matLocal;
    this->matGlobal = other->matGlobal;
    this->matLocalSkeleton = other->matLocalSkeleton;
    this->matGlobalSkeleton = other->matGlobalSkeleton;

    for( unsigned int i = 0; i < other->joints.length(); i++)
    {
        this->joints += other->joints[i];
        other->joints[i]->root = this->getprogenitor();
    }

    for( unsigned int i = 0; i < other->posKeys.length(); i++)
    {
        this->posKeys += other->posKeys[i];
    }

    for( unsigned int i = 0; i < other->rotKeys.length(); i++)
    {
        this->rotKeys += other->rotKeys[i];
    }

    for( unsigned int i = 0; i < other->scaleKeys.length(); i++)
    {
        this->scaleKeys += other->scaleKeys[i];
    }

    for( unsigned int i = 0; i < other->tangents.length(); i++)
    {
        this->tangents += other->tangents[i];
    }

    for( unsigned int i = 0; i < other->verticies.length(); i++)
    {
        this->verticies += other->verticies[i];
    }

    for( unsigned int i = 0; i < other->verticiesTrans.length(); i++)
    {
        this->verticiesTrans += other->verticiesTrans[i];
    }
}

void
POGEL::OBJECT::increment()
{
    // rotate by this objects spin
    rotate(spin);

    // translate by this objects direction vector
    translate(direction);

    //matrix = POGEL::MATRIX(position,rotation);
}

int
_sortTrianglesByPropertiesAndImage(POGEL::TRIANGLE* a, POGEL::TRIANGLE* b)
{
    // safties
    POGEL::TRIANGLE* triA = (POGEL::TRIANGLE*)a;
    POGEL::TRIANGLE* triB = (POGEL::TRIANGLE*)b;

    if( triA->getproperties() == triB->getproperties() )
    {
        // if triangle A is null or has a null texture, move forward
        if(triA == NULL || triA->texture == NULL)
        {
            return -1;
        }
        // same with B
        if(triB == NULL || triB->texture == NULL)
        {
            return 1;
        }
        if( triA->texture == triB->texture )
        {
            return 0;
        }
        return (int)triB->texture - (int)triA->texture;
    }
    return (int)triB->getproperties() - (int)triA->getproperties();
}

void
POGEL::OBJECT::build()
{
    // go through all triangles
    for( unsigned int i = 0; i < numfaces; ++i )
    {
        // if any are transparent or see through
        if( !face[ i ].isClear() )
        {
            continue;
        }

        // tell the object to sort its triangles
        addproperty(OBJECT_SORT_TRIANGLES);

        // remove the option to 'predraw' the object to a display list
        if( hasproperty(OBJECT_DRAW_DISPLAYLIST) )
        {
            removeproperty(OBJECT_DRAW_DISPLAYLIST);
        }

        // exit loop, only one is enough
        break;
    }

    // generate a temporary list pointing to the list of triangles
    CLASSLIST<POGEL::TRIANGLE> triList(face, numfaces);
    // sort the list by the triangles transparency
    triList.sort(_sortTrianglesByPropertiesAndImage);
    // set the temporary lists' internal pointer to null
    triList.nullify();

    if( hasproperty(OBJECT_SORT_TRIANGLES) )
    {
        trisortfaces1.init( numfaces );
        trisortfaces2.init( numfaces );

        for( unsigned int i = 0; i < numfaces; ++i )
        {
            trisortfaces1.set( i, face[ i ].hasproperty(TRIANGLE_DOUBLESIDED) || face[ i ].hasproperty(TRIANGLE_INVERT_NORMALS) );
            trisortfaces2.set( i, face[ i ].hasproperty(TRIANGLE_DOUBLESIDED) || !face[ i ].hasproperty(TRIANGLE_INVERT_NORMALS) );
        }

        trisortfaces0_first = -1;
        trisortfaces0_last = -1;
        trisortfaces1_first = -1;
        trisortfaces1_last = -1;
        trisortfaces2_first = -1;
        trisortfaces2_last = -1;
    }

    // if the object is to be drawn into a display list
    if( hasproperty(OBJECT_DRAW_DISPLAYLIST) )
    {
        #ifdef OPENGL

            // generate a new display list
            base = glGenLists( 1 );

            unsigned int prp = POGEL::getproperties();
            // if bounding to be drawn and object rotates to camera
            if( POGEL::hasproperty(POGEL_BOUNDING) )//&& hasproperty(OBJECT_ROTATE_TOCAMERA) )
            {
                // do not draw boundings for the triangles, it looks bad
                POGEL::removeproperty(POGEL_BOUNDING);
            }

            // start 'recording'
            glNewList( base, GL_COMPILE );

                if( hasproperty(OBJECT_SORT_TRIANGLES) )
                {
                    POGEL::drawTriangleListIsClear( face, numfaces, false, NULL, false, &trisortfaces0_first, &trisortfaces0_last );
                    //#if !(defined(WINDOWS) || defined(_WIN32) || defined(_WIN64))
                    POGEL::addproperty(POGEL_NODOUBLESIDEDTRIANGLES);
                    //#endif
                    glFrontFace(GL_CW);
                    POGEL::drawTriangleListIsClear( face, numfaces, true, &trisortfaces1, true, &trisortfaces1_first, &trisortfaces1_last );
                    glFrontFace(GL_CCW);
                    POGEL::drawTriangleListIsClear( face, numfaces, true, &trisortfaces2, true, &trisortfaces2_first, &trisortfaces2_last );
                    //#if !(defined(WINDOWS) || defined(_WIN32) || defined(_WIN64))
                    //POGEL::removeproperty(POGEL_NODOUBLESIDEDTRIANGLES);
                    //#endif
                }
                else
                {
                    POGEL::drawTriangleList( face, numfaces );
                }

            // finish the display list
            glEndList();

            // reset pogel's properties
            POGEL::setproperties(prp);

        #endif
    }

    // get the current opengl matrix transform, unnessicary
    //matrix.get();

    // check if this object is 'inbred' ( is one of its own children )
    // if this object has a decendant with the same name, does not check self
    if( getdecendant(this->getname(),false) != NULL )
    {
        // if the object with the same name as this object is this object, does not sheck self
        if( getdecendant(this->getname(),false) == this )
        {
            // kill program
            POGEL::fatality(POGEL_FATALITY_CIRCULAR_HIERARCHY_RETNUM,"%s of object: \"%s\"",POGEL_FATALITY_CIRCULAR_HIERARCHY_STRING,this->getname()); // BADDNESS, complain, and exit the program
        }
    }

    unsigned int posKeysLength = posKeys.length();

    // if there are more than 2 keys, we can calculate tangents, otherwise we use zero derivatives
    if( posKeysLength > 2 )
    {
        if( tangents.length() < posKeysLength )
        {
            for( unsigned int k = 0; k < posKeysLength; ++k )
            {
                // make the curve tangents looped
                int k0 = int(k) - 1;
                if( k0 < 0 )
                {
                    k0 = int(posKeysLength) - 1;
                }
                int k1 = int(k);
                int k2 = int(k) + 1;
                if( k2 >= int(posKeysLength) )
                {
                    k2 = 0;
                }

                // calculate the tangent, which is the vector from key[k - 1] to key[k + 1]
                POGEL::POINT tangent( posKeys[k2] - posKeys[k0] );

                // weight the incoming and outgoing tangent by their time to avoid changes in speed, if the keys are not within the same interval
                float dt1 = posKeys[k1].time - posKeys[k0].time;
                float dt2 = posKeys[k2].time - posKeys[k1].time;
                float dt = dt1 + dt2;
                tangents += POGEL::TANGENT( tangent * dt1 / dt, tangent * dt2 / dt );
            }
        }
    }
    else
    {
        while( tangents.length() < posKeysLength )
        {
            tangents += POGEL::TANGENT( POGEL::POINT(), POGEL::POINT() );
        }
    }

    if( parent != NULL )
    {
        matLocalSkeleton = POGEL::QUAT(rotation/180.0f*PI).tomatrix();
        matLocalSkeleton.setvalue(3,0,position.x);
        matLocalSkeleton.setvalue(3,1,position.y);
        matLocalSkeleton.setvalue(3,2,position.z);

        matGlobalSkeleton = matLocalSkeleton * parent->matGlobalSkeleton;
    }
    else
    {
        matLocalSkeleton = POGEL::MATRIX();

        matGlobalSkeleton = matLocalSkeleton;
    }

    matLocal = matLocalSkeleton;
    matGlobal = matGlobalSkeleton;

    // go through the children
    for( unsigned int i = 0; i < numchildren; ++i )
    {
        // make sure they know who is in charge
        children[i]->parent = this;
        // build them too
        children[i]->build();
    }

    // seup the pointer to the root object in the object tree
    root = this->getprogenitor();

    setAnimationTime(-1.0f);
}

int
POGEL::OBJECT::setAnimationLoop( const std::string& animationname )
{
    unsigned int numAnimations = animations.length();
    if( !numAnimations )
    {
        return -1;
    }
    for( unsigned int i = 0; i < numAnimations; ++i )
    {
        if( animations[ i ] == animationname )
        {
            currentAnimationLoopIndex = i;
            if( currentAnimationLoopStartTime < 0.0f )
            {
                currentAnimationLoopStartTime = (float)POGEL::GetTimePassed();
            }
            return 0;
        }
    }
    return -2;
}

int
POGEL::OBJECT::setAnimationLoop( const std::string& animationname, float startpercent )
{
    unsigned int numAnimations = animations.length();
    if( !numAnimations )
    {
        return -1;
    }
    for( unsigned int i = 0; i < numAnimations; ++i )
    {
        if( animations[ i ] == animationname )
        {
            currentAnimationLoopIndex = i;
            currentAnimationLoopStartTime = (float)POGEL::GetTimePassed();
            currentAnimationLoopStartTime += ( animations[ i ].getStop() - animations[ i ].getStart() ) * startpercent;
            return 0;
        }
    }
    return -2;
}

void
POGEL::OBJECT::setAnimationLoopStartTime( float stime )
{
    currentAnimationLoopStartTime = stime;
}

float
POGEL::OBJECT::getTimeSinceAnimationStart() const
{
    return POGEL::GetTimePassed() - currentAnimationLoopStartTime;
}

float
POGEL::OBJECT::getAnimationLength( const std::string& animationname ) const
{
     unsigned int numAnimations = animations.length();
    if( !numAnimations )
    {
        return -1.0f;
    }
    for( unsigned int i = 0; i < numAnimations; ++i )
    {
        if( animations[ i ] == animationname )
        {
            return fabs(animations[ i ].getStop() - animations[ i ].getStart()) / getAnimationFPS();
        }
    }
    return -2.0f;
}

std::string
POGEL::OBJECT::getCurrentAnimation() const
{
    if( currentAnimationLoopIndex < 0 || currentAnimationLoopIndex >= int(animations.length()) )
    {
        return std::string("");
    }
    return animations[ currentAnimationLoopIndex ].getName();
}

int
POGEL::OBJECT::addAnimationLoop( const POGEL::ANIMATIONLOOP& anim, const std::string& jointname )
{
    if( !jointname.length() || !jointname.compare( this->getsname() ) )
    {
        animations += anim;
        return 0;
    }

    unsigned int numJoints = joints.length();
    if( !numJoints )
    {
        return -1;
    }

    for( unsigned int i = 0; i < numJoints; ++i )
    {
        if( !joints[ i ]->getsname().compare(jointname) )
        {
            return joints[ i ]->addAnimationLoop( anim, "" );
        }
    }

    return -2;
}

bool
POGEL::OBJECT::hasAnimationLoop( const std::string& animname ) const
{
    unsigned int numAnimations = animations.length();
    if( !numAnimations || !animname.length() )
    {
        return false;
    }
    for( unsigned int i = 0; i < numAnimations; ++i )
    {
        if( animations[ i ] == animname )
        {
            return true;
        }
    }
    return false;
}

void
POGEL::OBJECT::playAnimation( float curtime )
{
    if( currentAnimationLoopIndex < 0 )
    {
        return;
    }
    POGEL::ANIMATIONLOOP loop = animations[ currentAnimationLoopIndex ];
    float start = loop.getStart();
    float stop = loop.getStop();
    float animlen = stop - start;
    float coefient = 1.0f;
    if( start > stop )
    {
        coefient = -1.0f;
    }
    if( currentAnimationLoopStartTime < 0.0f )
    {
        setAnimationTime( (fmod( ( curtime ) * getAnimationFPS(), animlen ) * coefient + start) );
    }
    else
    {
        setAnimationTime( (fmod( ( curtime - currentAnimationLoopStartTime ) * getAnimationFPS(), animlen ) * coefient + start) );
    }
}

void
POGEL::OBJECT::setAnimationTime( float frame )
{
    if( currentAnimationFrame == frame && previousAnimationFrame == currentAnimationFrame )
    {
        return;
    }

    previousAnimationFrame = currentAnimationFrame;
    currentAnimationFrame = frame;

    updateSkeleton();

    // go through the children
    for( unsigned int i = 0; i < numchildren; ++i )
    {
        // set all children to the same frame
        children[ i ]->setAnimationTime( frame );
    }

    updateTriangles();
}

void
POGEL::OBJECT::updateSkeleton()
{
    float frame( currentAnimationFrame );
    // apply the positional and rotational stuff to this object first
    if( frame < 0.0f )
    {
        matLocal = matLocalSkeleton;
        matGlobal = matGlobalSkeleton;
        return;
    }
    POGEL::POINT pos;
    if( posKeys.length() > 0 )
    {
        int i1 = -1;
        int i2 = -1;
        for( unsigned int i = 0; i < posKeys.length() - 1; ++i )
        {
            if( frame >= posKeys[i].time && frame < posKeys[i + 1].time )
            {
                i1 = i;
                i2 = i + 1;
                break;
            }
        }

        // if there are no such keys
        if(i1 == -1 || i2 == -1)
        {
            // either take the first
            if (frame < posKeys[0].time)
            {
                pos = posKeys[0];
            }

            // or the last key
            else if (frame >= posKeys[posKeys.length() - 1].time)
            {
                pos = posKeys[posKeys.length() - 1];
            }
        }

        // there are such keys, so interpolate using hermite interpolation
        else
        {
            POGEL::KEY p1( posKeys[i1] );
            POGEL::KEY p2( posKeys[i2] );
            POGEL::POINT m1( tangents[i1].out );
            POGEL::POINT m2( tangents[i2].in );

            // normalize the time between the keys into [0..1]
            float t = (frame - p1.time) / (p2.time - p1.time);
            float t2 = t * t;
            float t3 = t2 * t;

            // calculate hermite basis
            float h1 =  2.0f * t3 - 3.0f * t2 + 1.0f;
            float h2 = -2.0f * t3 + 3.0f * t2;
            float h3 =         t3 - 2.0f * t2 + t;
            float h4 =         t3 -        t2;

            // do hermite interpolation
            pos = p1 * h1 + p2 * h2 + m1 * h3 + m2 * h4;
        }

    }

    POGEL::QUAT rot;
    if( rotKeys.length() > 0 )
    {

        int i1 = -1;
        int i2 = -1;

        // find the two keys, where "frame" is in between for the rotation channel
        for( unsigned int i = 0; i < rotKeys.length() - 1; ++i )
        {
            if( frame >= rotKeys[ i ].time && frame < rotKeys[ i + 1 ].time )
            {
                i1 = i;
                i2 = i + 1;
                break;
            }
        }

        // if there are no such keys
        if( i1 == -1 || i2 == -1 )
        {
            // either take the first key
            if( frame < rotKeys[ 0 ].time )
            {
                rot = POGEL::QUAT( rotKeys[ 0 ] );
            }

            // or the last key
            else if( frame >= rotKeys[ rotKeys.length() - 1 ].time )
            {
                rot = POGEL::QUAT( rotKeys[ rotKeys.length() - 1 ] );
            }
        }

        // there are such keys, so do the quaternion slerp interpolation
        else
        {
            POGEL::QUAT q1( rotKeys[ i1 ] );
            POGEL::QUAT q2( rotKeys[ i2 ] );
            float t = ( frame - rotKeys[ i1 ].time ) / ( rotKeys[ i2 ].time - rotKeys[ i1 ].time );
            rot = q1.slerp( q2, t );
        }
    }

    // do not want a scale of zero, that would be bad
    POGEL::POINT scale( 1.0f );
    if( scaleKeys.length() > 0 )
    {
        int i1 = -1;
        int i2 = -1;
        for( unsigned int i = 0; i < scaleKeys.length() - 1; ++i )
        {
            if( frame >= scaleKeys[ i ].time && frame < scaleKeys[ i + 1 ].time )
            {
                i1 = i;
                i2 = i + 1;
                break;
            }
        }

        // if there are no such keys
        if( i1 == -1 || i2 == -1 )
        {
            // either take the first
            if( frame < scaleKeys[ 0 ].time )
            {
                scale = scaleKeys[ 0 ];
            }

            // or the last key
            else if( frame >= scaleKeys[ scaleKeys.length() - 1 ].time )
            {
                scale = scaleKeys[ scaleKeys.length() - 1 ];
            }
        }

        // there are such keys, so interpolate using linear interpolation,
        //  because I am lazy
        else
        {
            //scale = POGEL::POINT(1.0f);
            POGEL::POINT s1( scaleKeys[ i1 ] );
            POGEL::POINT s2( scaleKeys[ i2 ] - s1 );
            float t = ( frame - scaleKeys[ i1 ].time ) / ( scaleKeys[ i2 ].time - scaleKeys[ i1 ].time );
            scale = s1 + s2 * t;
        }
    }

    POGEL::MATRIX matAnimate( rot.tomatrix() );
    matAnimate = matAnimate * POGEL::MATRIX( scale, MATRIX_CONSTRUCT_SCALE );
    matAnimate.setvalue( 3, 0, pos.x );
    matAnimate.setvalue( 3, 1, pos.y );
    matAnimate.setvalue( 3, 2, pos.z );

    // animate the local joint matrix using: matLocal = matLocalSkeleton * matAnimate
    matLocal = matAnimate * matLocalSkeleton;

    // build up the hierarchy if joints
    if( parent == NULL )
    {
        matGlobal = matLocal;
        if( this == root && this->posKeys.length() )
        {
            position = matGlobal.getposition();
        }
    }
    else
    {
        // matGlobal = matGlobal(parent) * matLocal
        matGlobal = matLocal * parent->matGlobal;
        position = matGlobal.getposition() - parent->matGlobal.getposition();
    }
    if( root && POGEL::hasproperty( POGEL_LABEL ) )
    {
        ( root->position + matGlobal.getposition() ).draw();
    }
}

void
POGEL::OBJECT::updateTriangles()
{
    // only transform verticies if able
    if( !joints.length() || !verticies.length() || !numfaces || verticiesTrans.length() != verticies.length() )
    {
        return;
    }

    bool dpoint( POGEL::properties & POGEL_LABEL && POGEL::properties & POGEL_WIREFRAME );

    BITLIST hastransformed( verticies.length(), false );

    for( unsigned int i = 0; i < numfaces; ++i )
    {
        bool vertnorms( face[ i ].getproperties() & TRIANGLE_VERTEX_NORMALS );
        bool transformed( false );
        for( unsigned int a = 0; a < 3; ++a )
        {
            int index( face[ i ].ivertex[ a ] );
            if( index < 0 )
            {
                continue;
            }

            transformed = true;

            //if( hastransformed[ index ] )
            if( !vertnorms &&  hastransformed[ index ] )
            {
                face[ i ].vertex[ a ] = (POGEL::POINT)verticiesTrans[ index ];
                /*if( vertnorms )
                {
                    face[ i ].vertex[ a ].normal = verticiesTrans[ index ].normal;
                }*/
                continue;
            }

            POGEL::VERTEX vert( verticies[ index ] );

            if( vertnorms )
            {
                vert.normal = face[ i ].vertnormals[ a ];
            }

            POGEL::VERTEX transvert( this->getTransformedVertex( vert, !hastransformed[ index ], vertnorms ) );

            if( !hastransformed[ index ] )
            {
                if( currentAnimationFrame >= 0.0f )
                {
                    transvert /= 2.55f;
                }
                verticiesTrans.replace( index, transvert );
                if( dpoint )
                {
                    transvert.draw( 3, POGEL::COLOR( 1.0f, 0.5f, 0.25f, 1.0f ) );
                }
                hastransformed += index;
            }

            face[ i ].vertex[ a ] = (POGEL::POINT)verticiesTrans[ index ];

            if( vertnorms )
            {
                face[ i ].vertex[ a ].normal = transvert.normal;
            }
        }

        if( transformed )
        {
            face[ i ].updateVert();
        }
    }
}

inline
POGEL::VECTOR
transVect( const POGEL::VECTOR & in1, const POGEL::MATRIX & in2, const POGEL::MATRIX & in3 )
{
    return in3.transformPoint( in2.transformVector( in1 - in2.getposition() ) );
}

// rotate by the inverse of the matrix
inline
POGEL::VECTOR
VectorIRotate ( const POGEL::VECTOR & in1, const POGEL::MATRIX & in2 )
{
    return in2.transformVector( in1 );
}

inline
POGEL::VECTOR
VectorTransform ( const POGEL::VECTOR & in1, const POGEL::MATRIX & in2 )
{
    return in2.transformPoint( in1 );
}

inline
POGEL::VECTOR
VectorITransform ( const POGEL::VECTOR & in1, const POGEL::MATRIX & in2 )
{
    return in2.transformVector( in1 - in2.getposition() );
}

POGEL::VERTEX
POGEL::OBJECT::getTransformedVertex( const POGEL::VERTEX & invert, bool dovert, bool donorm )
{
    if( !(dovert || donorm) || !joints.length() || currentAnimationFrame < 0.0f || invert.boneID < 0 || invert.boneID >= (int)joints.length() )
    {
        return invert;
    }

    int jointIndices[4] = { invert.boneID, invert.boneIDs[ 0 ], invert.boneIDs[ 1 ], invert.boneIDs[ 2 ] };
    int jointWeights[4] = { 100, 0, 0, 0 };

    if( invert.weights[ 0 ] || invert.weights[ 1 ] || invert.weights[ 2 ] )
    {
        jointWeights[ 0 ] = invert.weights[ 0 ];
        jointWeights[ 1 ] = invert.weights[ 1 ];
        jointWeights[ 2 ] = invert.weights[ 2 ];
        jointWeights[ 3 ] = 100 - ( invert.weights[ 0 ] + invert.weights[ 1 ] + invert.weights[ 2 ] );
    }

    unsigned int numjoints( joints.length() );

    // count valid weights
    unsigned int numWeights = 0;
    for( unsigned int i = 0; i < 4; ++i )
    {
        if( !(jointWeights[ i ] > 0 && jointIndices[ i ] >= 0 && jointIndices[ i ] < (int)numjoints) )
        {
            break;
        }
        ++numWeights;
    }

    if( !numWeights )
    {
        POGEL::OBJECT * joint = joints[ invert.boneID ];
        POGEL::VERTEX vert;
        if( dovert )
        {
            //vert = VectorTransform( VectorITransform( invert, joint->matGlobalSkeleton ), joint->matGlobal );
            vert = transVect( invert, joint->matGlobalSkeleton, joint->matGlobal );
        }
        if( donorm )
        {
            vert.normal = joint->matGlobal.transformVector( VectorIRotate( invert.normal, joint->matGlobalSkeleton ) );
        }
        return vert;
    }

    float weight( (float) jointWeights[ 0 ] * 0.01f );

    // add weighted vertices
    if( dovert && !donorm )
    {
        POGEL::VERTEX vert;
        for( unsigned int i( 0 ); i < numWeights; weight = (float) jointWeights[ ++i ] * 0.01f )
        {
            POGEL::OBJECT * joint = joints[ jointIndices[ i ] ];
            //vert += VectorTransform( VectorITransform( invert, joint->matGlobalSkeleton ), joint->matGlobal ) * weight;
            vert += transVect( invert, joint->matGlobalSkeleton, joint->matGlobal ) * weight;
        }
        return vert;
    }

    if( !dovert && donorm )
    {
        POGEL::VERTEX vert;
        for( unsigned int i( 0 ); i < numWeights; weight = (float) jointWeights[ ++i ] * 0.01f )
        {
            POGEL::OBJECT * joint = joints[ jointIndices[ i ] ];
            vert.normal += joint->matGlobal.transformVector( VectorIRotate( invert.normal, joint->matGlobalSkeleton ) ) * weight;
        }
        return vert;
    }

    POGEL::VERTEX vert;
    for( unsigned int i( 0 ); i < numWeights; weight = (float) jointWeights[ ++i ] * 0.01f )
    {
        POGEL::OBJECT * joint = joints[ jointIndices[ i ] ];
        //vert += VectorTransform( VectorITransform( invert, joint->matGlobalSkeleton ), joint->matGlobal ) * weight;
        vert += transVect( invert, joint->matGlobalSkeleton, joint->matGlobal ) * weight;
        vert.normal += joint->matGlobal.transformVector( VectorIRotate( invert.normal, joint->matGlobalSkeleton ) ) * weight;
    }
    return vert;
}

void
POGEL::OBJECT::draw()
{
    #ifdef OPENGL
        matrix = POGEL::MATRIX(position,rotation);
        if( visable )
        {
            if( hasproperty(OBJECT_ROTATE_TOCAMERA) )
            {
                POGEL::MATRIX mat;
                mat.get();
                POGEL::POINT cam_pos = mat.getposition()*-1.0f;
                mat.invert();
                mat.transformPoint(&cam_pos);
                float radius = cam_pos.distance(POGEL::POINT());

                rotation.x = POGEL::RadiansToDegrees(acos(cam_pos.y/radius))+90.0f;
                rotation.y = -1.0f*(90.0f+POGEL::RadiansToDegrees(atan2(cam_pos.z, cam_pos.x)))+180.0f;
                rotation.z = 0.0f;
            }

            // if compiled to use opengl matrix recursion (limited stack size, but faster)
            #ifdef OBJECT_USE_OPNEGL_MATRIX_RECURSION
                // push new opengl matrix
                glPushMatrix();
            #endif /* OBJECT_USE_OPNEGL_MATRIX_RECURSION */

            // translate to objects position
            glTranslatef( position.x, position.y, position.z );

            // rotate transform
            if( hasproperty(OBJECT_ROTATE_XYZ) )
            {
                // rotate: x, y, z
                glRotatef( rotation.x, 1.0f, 0.0f, 0.0f );
                glRotatef( rotation.y, 0.0f, 1.0f, 0.0f );
                glRotatef( rotation.z, 0.0f, 0.0f, 1.0f );
            }
            else if( hasproperty(OBJECT_ROTATE_TOCAMERA) )
            {
                // rotate: y, x, z
                glRotatef( rotation.y, 0.0f, 1.0f, 0.0f );
                glRotatef( rotation.x, 1.0f, 0.0f, 0.0f );
                glRotatef( rotation.z, 0.0f, 0.0f, 1.0f );
            }
            else
            {
                // rotate: z, y, x
                glRotatef( rotation.z, 0.0f, 0.0f, 1.0f );
                glRotatef( rotation.y, 0.0f, 1.0f, 0.0f );
                glRotatef( rotation.x, 1.0f, 0.0f, 0.0f );
            }
            unsigned long i;

            // if can draw the objects children
            if( hasproperty(OBJECT_DRAW_CHILDREN) )
            {
                // go through the children
                for( i = 0; i < numchildren; ++i )
                {
                    // if to draw the ancestoral inheretance
                    if( POGEL::hasproperty(POGEL_ANCESTORY) )
                    {
                        // draw line from this object to current child object
                        POGEL::LINE(POGEL::POINT(), children[ i ]->position, 1, POGEL::COLOR(0,.5,1,1)).draw();
                    }
                    // draw the child object
                    children[ i ]->draw();
                }
            }

            // if to draw as a display list
            if( hasproperty(OBJECT_DRAW_DISPLAYLIST) )
            {
                // call the list
                glCallList( base );
            }
            // draw the faces if desired
            else if( !hasproperty(OBJECT_DRAW_NOFACES) )
            {
                unsigned int prp = POGEL::getproperties();
                // if bounding to be drawn and object rotates to camera
                if( POGEL::hasproperty(POGEL_BOUNDING) )//&& hasproperty(OBJECT_ROTATE_TOCAMERA) )
                {
                    // do not draw boundings for the triangles, it looks bad
                    POGEL::removeproperty(POGEL_BOUNDING);
                }

                if( hasproperty(OBJECT_SORT_TRIANGLES) )
                {
                    POGEL::drawTriangleListIsClear( face, numfaces, false, NULL, false, &trisortfaces0_first, &trisortfaces0_last );
                    //#if !(defined(WINDOWS) || defined(_WIN32) || defined(_WIN64))
                    POGEL::addproperty(POGEL_NODOUBLESIDEDTRIANGLES);
                    //#endif
                    glFrontFace(GL_CW);
                    POGEL::drawTriangleListIsClear( face, numfaces, true, &trisortfaces1, true, &trisortfaces1_first, &trisortfaces1_last );
                    glFrontFace(GL_CCW);
                    POGEL::drawTriangleListIsClear( face, numfaces, true, &trisortfaces2, true, &trisortfaces2_first, &trisortfaces2_last );
                    //#if !(defined(WINDOWS) || defined(_WIN32) || defined(_WIN64))
                    POGEL::removeproperty(POGEL_NODOUBLESIDEDTRIANGLES);
                    //#endif
                }
                else
                {
                    POGEL::drawTriangleList( face, numfaces );
                }

                // reset pogel's properties
                POGEL::setproperties(prp);
            }

            // if this object is to be debugged
            if( hasproperty(OBJECT_DEBUG) )
            {
                char * n = getancestory();
                POGEL::MATRIX mat;
                mat.get();
                POGEL::message("\nfor object: \"%s\":\n", n);
                if( n != NULL && parent != NULL )
                {
                    free(n);
                }
                POGEL::message("\nobject properties:  %ld", properties);
                POGEL::message("\nobject number of triangles:  %ld", numfaces);
                POGEL::message("\nobject number of allocated triangles:  %ld", triangle_allocation_total);
                POGEL::message("\nobject position:  ");
                position.print();
                POGEL::message("\nobject rotation:  ");
                rotation.print();
                POGEL::message("\nobject direction: ");
                direction.print();
                POGEL::message("\nobject spin:      ");
                spin.print();
                POGEL::message("\nposition from matrix: ");
                mat.getposition().print();
                POGEL::message("\nrotation from matrix: ");
                mat.getrotation().print();
                POGEL::message("\nthe matrix: ");
                mat.print();
                POGEL::message("as quaternion: ");
                mat.toquat().print();
                POGEL::message("\n\n");
            }

            // if using opengl matricies
            #ifdef OBJECT_USE_OPNEGL_MATRIX_RECURSION
                // pop the matrix
                glPopMatrix();
            // otherwise
            #else

                // rotate in reverse of above
                if( hasproperty(OBJECT_ROTATE_XYZ) )
                {
                    glRotatef( rotation.z, 0.0f, 0.0f, -1.0f );
                    glRotatef( rotation.y, 0.0f, -1.0f, 0.0f );
                    glRotatef( rotation.x, -1.0f, 0.0f, 0.0f );
                }
                else if( hasproperty(OBJECT_ROTATE_TOCAMERA) )
                {
                    glRotatef( rotation.z, 0.0f, 0.0f, -1.0f );
                    glRotatef( rotation.x, -1.0f, 0.0f, 0.0f );
                    glRotatef( rotation.y, 0.0f, -1.0f, 0.0f );
                }
                else
                {
                    glRotatef( rotation.x, -1.0f, 0.0f, 0.0f );
                    glRotatef( rotation.y, 0.0f, -1.0f, 0.0f );
                    glRotatef( rotation.z, 0.0f, 0.0f, -1.0f );
                }

                // translate back
                glTranslatef(-position.x, -position.y, -position.z);

            #endif /* OBJECT_USE_OPNEGL_MATRIX_RECURSION */
        }

        // if pogel wants to label all objects
        // even if the object is not visable
        if( POGEL::hasproperty(POGEL_LABEL) )
        {
            // draw a blue dot at this objects position
            position.draw( 2, POGEL::COLOR(0.2f,0.5f,1.0f,1.0f) );
        }
    #endif
}


void
POGEL::OBJECT::drawColored(const unsigned char * color)
{
    #ifdef OPENGL
        matrix = POGEL::MATRIX(position,rotation);
        if( visable )
        {
            if( hasproperty(OBJECT_ROTATE_TOCAMERA) )
            {
                POGEL::MATRIX mat;
                mat.get();
                POGEL::POINT cam_pos = mat.getposition()*-1.0f;
                mat.invert();
                mat.transformPoint(&cam_pos);
                float radius = cam_pos.distance(POGEL::POINT());

                rotation.x = POGEL::RadiansToDegrees(acos(cam_pos.y/radius))+90.0f;
                rotation.y = -1.0f*(90.0f+POGEL::RadiansToDegrees(atan2(cam_pos.z, cam_pos.x)))+180.0f;
                rotation.z = 0.0f;
            }

            // if compiled to use opengl matrix recursion (limited stack size, but faster)
            #ifdef OBJECT_USE_OPNEGL_MATRIX_RECURSION
                // push new opengl matrix
                glPushMatrix();
            #endif /* OBJECT_USE_OPNEGL_MATRIX_RECURSION */

            // translate to objects position
            glTranslatef( position.x, position.y, position.z );

            // rotate transform
            if( hasproperty(OBJECT_ROTATE_XYZ) )
            {
                // rotate: x, y, z
                glRotatef( rotation.x, 1.0f, 0.0f, 0.0f );
                glRotatef( rotation.y, 0.0f, 1.0f, 0.0f );
                glRotatef( rotation.z, 0.0f, 0.0f, 1.0f );
            }
            else if( hasproperty(OBJECT_ROTATE_TOCAMERA) )
            {
                // rotate: y, x, z
                glRotatef( rotation.y, 0.0f, 1.0f, 0.0f );
                glRotatef( rotation.x, 1.0f, 0.0f, 0.0f );
                glRotatef( rotation.z, 0.0f, 0.0f, 1.0f );
            }
            else
            {
                // rotate: z, y, x
                glRotatef( rotation.z, 0.0f, 0.0f, 1.0f );
                glRotatef( rotation.y, 0.0f, 1.0f, 0.0f );
                glRotatef( rotation.x, 1.0f, 0.0f, 0.0f );
            }
            unsigned long i;

            // if can draw the objects children
            if( hasproperty(OBJECT_DRAW_CHILDREN) )
            {
                // go through the children
                for( i = 0; i < numchildren; ++i )
                {
                    // draw the child object
                    children[ i ]->drawColored( color );
                }
            }

            /*glColor4ub( color[0], color[1], color[2], color[3] );
            if( POGEL::properties & POGEL_WIREFRAME )
            {
                glBegin( GL_LINES );
            }
            else
            {
                glBegin( GL_TRIANGLES );
            }
            for( i = 0; i < numfaces; ++i )
            {
                face[ i ].drawgeometryvertexonly();
            }
            glEnd();*/
            POGEL::drawTriangleListColored( face, numfaces, color );

            // if using opengl matricies
            #ifdef OBJECT_USE_OPNEGL_MATRIX_RECURSION
                // pop the matrix
                glPopMatrix();
            // otherwise
            #else

                // rotate in reverse of above
                if( hasproperty(OBJECT_ROTATE_XYZ) )
                {
                    glRotatef( rotation.z, 0.0f, 0.0f, -1.0f );
                    glRotatef( rotation.y, 0.0f, -1.0f, 0.0f );
                    glRotatef( rotation.x, -1.0f, 0.0f, 0.0f );
                }
                else if( hasproperty(OBJECT_ROTATE_TOCAMERA) )
                {
                    glRotatef( rotation.z, 0.0f, 0.0f, -1.0f );
                    glRotatef( rotation.x, -1.0f, 0.0f, 0.0f );
                    glRotatef( rotation.y, 0.0f, -1.0f, 0.0f );
                }
                else
                {
                    glRotatef( rotation.x, -1.0f, 0.0f, 0.0f );
                    glRotatef( rotation.y, 0.0f, -1.0f, 0.0f );
                    glRotatef( rotation.z, 0.0f, 0.0f, -1.0f );
                }

                // translate back
                glTranslatef(-position.x, -position.y, -position.z);

            #endif /* OBJECT_USE_OPNEGL_MATRIX_RECURSION */
        }
        //position.draw( 2, POGEL::COLOR(0.2f,0.5f,1.0f,1.0f) );
    #endif
}

void
POGEL::OBJECT::step()
{
    // incriment the object
    increment();

    // call the objects 'overloaded' step function
    stepFunc();
}
