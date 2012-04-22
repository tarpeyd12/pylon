#ifndef BITLIST_H_INCLUDED
#define BITLIST_H_INCLUDED

#include "../../lists/bitlist.h"

class BITLIST : public BitList
{
    public:
        BITLIST() : BitList() { }
        BITLIST( unsigned int b ) : BitList( b ) { }
        BITLIST( unsigned int b, bool v ) : BitList( b, v ) { }
};

#endif /* BITLIST_H_INCLUDED */
