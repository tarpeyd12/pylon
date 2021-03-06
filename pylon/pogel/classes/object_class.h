#ifndef _OBJECT_CLASS_H
#define _OBJECT_CLASS_H

#include <stdlib.h>
#include <string.h>

namespace POGEL
{
    class OBJECT;
}

#include "point_class.h"
#include "triangle_class.h"
#include "matrix_class.h"
#include "../pogel_internals.h"
#include "physics/physics.h"

#include "../templates/classlist_template.h"

#define         OBJECT_DEBUG                            1
#define         OBJECT_DRAW_DISPLAYLIST                 2
#define         OBJECT_DRAW_COLORED_STRIP               4
#define         OBJECT_DRAW_CHILDREN                    8
#define         OBJECT_ROTATE_XYZ                       16
#define         OBJECT_ROTATE_ZYX                       32
#define         OBJECT_SORT_TRIANGLES                   64
#define         OBJECT_ROTATE_TOCAMERA                  128
#define         OBJECT_DRAW_NOFACES                     256

#define         OBJECT_USE_OPNEGL_MATRIX_RECURSION

#define         OBJECT_TRIAGLE_ALLOCATION_SKIP          1000

namespace POGEL
{

    class ANIMATIONLOOP
    {
        private:

            float start;
            float stop;

        protected:

            std::string name;

        public:

            ANIMATIONLOOP() : start( -2.0f ), stop( -1.0f ), name("") {  }

            ANIMATIONLOOP( float b, float s, const std::string& nm )
            {
                start = b;
                stop = s;
                name = nm;
            }

            ~ANIMATIONLOOP()
            {

            }

            void setName( const std::string& nm )
            {
                name = nm;
            }

            void setStart( float s )
            {
                start = s;
            }

            void setStop( float s )
            {
                stop = s;
            }

            std::string getName() const
            {
                return name;
            }

            float getStart() const
            {
                return start;
            }

            float getStop() const
            {
                return stop;
            }

            bool operator==( const std::string& nm )
            {
                return bool(!(name.compare(nm)));
            }
    };

    class OBJECT
    {
        private:

            unsigned int properties; // the mushed options

        protected:

            char* name; // the name of the object, used for identification in the tree of child objects

            POGEL::TRIANGLE * face; // the array of triangle faces
            unsigned long     numfaces; // the number of triangles in the triangle array
            unsigned long     triangle_allocation_total; // the total number of triangles allocated
            POGEL::OBJECT  ** children; // the array of pointers to child objects
            unsigned long     numchildren; // the number of children objects
            POGEL::OBJECT   * parent; // the parent of this object if it is a child object
            POGEL::OBJECT   * root; // the parent of the entire object tree

            // these CLASSLISTs are only used for animation:
            CLASSLIST < POGEL::VERTEX >    verticies; // the untransformed verticies
            CLASSLIST < POGEL::VERTEX >    verticiesTrans; // the transformed verticies, this is where stuff points
            CLASSLIST < POGEL::OBJECT * >  joints; // a linear list of all the decendant objects, for animation
            CLASSLIST < POGEL::KEY >       posKeys; // the position key values
            CLASSLIST < POGEL::KEY >       rotKeys; // the rotation key values
            CLASSLIST < POGEL::KEY >       scaleKeys; // the scalar key values
            CLASSLIST < POGEL::TANGENT >   tangents; // the list of tangents
            unsigned int numFrames; // the number of 'frames' in the animation
            float animationFPS; // the speed of the animation
            float currentAnimationFrame; // the current frame in the animation
            float previousAnimationFrame; // the current frame in the animation
            POGEL::MATRIX matLocal;
            POGEL::MATRIX matGlobal;
            POGEL::MATRIX matLocalSkeleton;
            POGEL::MATRIX matGlobalSkeleton;
            CLASSLIST < POGEL::ANIMATIONLOOP > animations;
            int currentAnimationLoopIndex;
            float currentAnimationLoopStartTime;

            BITLIST trisortfaces1;
            BITLIST trisortfaces2;
            int trisortfaces0_first;
            int trisortfaces0_last;
            int trisortfaces1_first;
            int trisortfaces1_last;
            int trisortfaces2_first;
            int trisortfaces2_last;
        public:

            POGEL::POINT position; // the center position of the object
            POGEL::POINT rotation; // the rotation arround the center of the object
            POGEL::VECTOR direction; // the movement vector
            POGEL::VECTOR spin; // the spin vector
            unsigned int base; // the pointer to the compiled display list
            POGEL::MATRIX matrix; // a uesless matrix, but do not mess with it
            bool visable; // the visibility flag for the object

            OBJECT();
            OBJECT( unsigned int );
            OBJECT( POGEL::TRIANGLE *, unsigned long, unsigned int );
            OBJECT( POGEL::TRIANGLE *, unsigned long, unsigned int, POGEL::POINT, POGEL::POINT );

            OBJECT( const char * );
            OBJECT( const char *, unsigned int );
            OBJECT( const char *, POGEL::TRIANGLE *, unsigned long, unsigned int );
            OBJECT( const char *, POGEL::TRIANGLE *, unsigned long, unsigned int, POGEL::POINT, POGEL::POINT );

            OBJECT( POGEL::OBJECT * );

            ~OBJECT();

            inline virtual int GetType() const { return POGEL_TYPE_OBJECT; }

            void killchildren();

            void derefference();

            PROPERTIES_METHODS;

            void setname( const char * );
            char * getname();
            std::string getsname() const;

            void translate( const POGEL::VECTOR& );
            void translate( const POGEL::VECTOR&, float );
            void moveto( const POGEL::POINT& );

            void rotate( const POGEL::VECTOR& );
            void rotate( const POGEL::VECTOR&, float );
            void turnto( const POGEL::POINT& );

            unsigned long addtriangle( const POGEL::TRIANGLE& );
            void addtriangles( POGEL::TRIANGLE *, unsigned long );
            void addtrianglespace( unsigned long );

            void cleartriangles();

            unsigned long addobject( POGEL::OBJECT * );
            void addobjects( POGEL::OBJECT **, unsigned long );

            void scroll_all_tex_values( float, float );

            POGEL::OBJECT * getchild( const char * );
            POGEL::OBJECT * getdecendant( const char * , bool );
            POGEL::OBJECT * getdecendant( const char * );

            POGEL::OBJECT * getancestor( const char * );
            POGEL::OBJECT * getprogenitor();
            char * getancestory();
            char * getancestoryhash();

            unsigned long getchildslot();

            POGEL::MATRIX getancestorialmatrix();
            POGEL::MATRIX getinternalancestorialmatrix();

            unsigned long getnumfaces();
            POGEL::TRIANGLE gettriangle( unsigned long );
            inline POGEL::TRIANGLE gettransformedtriangle( unsigned long );
            POGEL::TRIANGLE * gettrianglelist();

            void copytriangles( POGEL::OBJECT * );
            void referencetriangles( POGEL::OBJECT * );
            void stealtriangles( POGEL::OBJECT * );
            void settriangle( unsigned long, const POGEL::TRIANGLE& );
            void settriangle( unsigned long, POGEL::TRIANGLE * );

            unsigned int getNumChildren() const;
            POGEL::OBJECT* getChild( unsigned int ) const;
            void stealChildren( POGEL::OBJECT * );

            void setNumFrames( unsigned int );
            void setAnimationFPS( float );
            POGEL::VERTEX getTransformedVertex( const POGEL::VERTEX&, bool, bool );
            unsigned int addVertex( const POGEL::VERTEX& );
            POGEL::VERTEX * getVertexAddress( unsigned int ) const;
            POGEL::VERTEX * getVertexListAddress();
            unsigned int getNumVerticies();
            unsigned int addPosKey( const POGEL::KEY& );
            unsigned int addRotKey( const POGEL::KEY& );
            unsigned int addScaleKey( const POGEL::KEY& );
            unsigned int addTangent( const POGEL::TANGENT& );
            unsigned int addJoint( POGEL::OBJECT * , const char * );
            POGEL::OBJECT * getJoint( const char * );
            float getAnimationFPS() const;
            unsigned int getNumFrames();

            void copyAnimation( POGEL::OBJECT * );

            void increment();

            virtual void build();

            int setAnimationLoop( const std::string& );
            int setAnimationLoop( const std::string&, float );
            void setAnimationLoopStartTime( float );
            float getTimeSinceAnimationStart() const;
            float getAnimationLength( const std::string& ) const;
            std::string getCurrentAnimation() const;
            int addAnimationLoop( const POGEL::ANIMATIONLOOP&, const std::string& );
            bool hasAnimationLoop( const std::string& ) const;

            void playAnimation( float );

            void setAnimationTime( float );
            void updateSkeleton();
            void updateTriangles();

            virtual void draw();
            virtual void drawColored(const unsigned char *);

            virtual void stepFunc() { }

            virtual void step();

            virtual void create() { }
            virtual void destroy() { }

            friend bool POGEL::PHYSICS::solid_collision( POGEL::PHYSICS::SOLID *, POGEL::PHYSICS::SOLID *, POGEL::POINT *, POGEL::VECTOR *, POGEL::VECTOR *, float * );
    };
}

#include "object_class_inline.h"

#endif /* _OBJECT_CLASS_H */
