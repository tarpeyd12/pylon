#ifndef _OCTREE_TEMPLATE_H
#define _OCTREE_TEMPLATE_H

/*namespace POGEL {
//template < class T>
	class OCTREE<>;
}*/

//#include "hashlist_template.h"
#include "../classes/bounding_class.h"
#include "classlist_template.h"
//#include "../classes/physics/solid_class.h"
//#include "../classes/physics/singularity_class.h"

#define		maxchildren		8
#define		dimentions		3
#define		defleastobjs	1

#define 	maxlevels		50

#define TUR 0 // towards up right    +x +y +z
#define TBR 1 // towards botom right +x -y +z
#define TUL 2 // towards up left     -x +y +z
#define TBL 3 // towards botom left  -x -y +z
#define AUR 4 // away up right       +x +y -z
#define ABR 5 // away botom right    +x -y -z
#define AUL 6 // away up left        -x +y -z
#define ABL 7 // away botom left     -x -y -z

#define pxpypz TUR // +x +y +z
#define pxpynz AUR // +x +y -z
#define pxnypz TBR // +x -y +z
#define pxnynz ABR // +x -y -z
#define nxpypz TUL // -x +y +z
#define nxpynz AUL // -x +y -z
#define nxnypz TBL // -x -y +z
#define nxnynz ABL // -x -y -z

#define bin_pxpypz (7) // 111 +x +y +z
#define bin_pxpynz (6) // 110 +x +y -z
#define bin_pxnypz (5) // 101 +x -y +z
#define bin_pxnynz (4) // 100 +x -y -z
#define bin_nxpypz (3) // 011 -x +y +z
#define bin_nxpynz (2) // 010 -x +y -z
#define bin_nxnypz (1) // 001 -x -y +z
#define bin_nxnynz (0) // 000 -x -y -z

inline
unsigned char
bn( bool a, bool b, bool c )
{
    return a ? 4 : 0 | b ? 2 : 0 | c ? 1 : 0;
}

inline
unsigned int
bin_child_num( unsigned char c )
{
	switch( c )
	{
		case bin_pxpypz: return pxpypz; // 111
		case bin_pxpynz: return pxpynz; // 110
		case bin_pxnypz: return pxnypz; // 101
		case bin_pxnynz: return pxnynz; // 100
		case bin_nxpypz: return nxpypz; // 011
		case bin_nxpynz: return nxpynz; // 010
		case bin_nxnypz: return nxnypz; // 001
		case bin_nxnynz: return nxnynz; // 000
	}
	return pxpypz;
}

inline
unsigned int
bool_child_num( bool a, bool b, bool c )
{
	return bin_child_num( bn( a, b, c ) );
}

/* NOTE:
		the generic class T for the template must be like this:

		class T {
			public:
				POGEL::POINT getposition();
				POGEL::BOUNDING getbounding();
		}
*/

#include "octree_template_general_definition.h"
//#include "octree_template_solid_definition.h"

#endif /* _OCTREE_TEMPLATE_H */
