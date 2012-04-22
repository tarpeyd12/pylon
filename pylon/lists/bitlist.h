#ifndef _BITLIST_H
#define _BITLIST_H

#include <string.h>

class BitList
{
    protected:
        unsigned int numbytes;
        unsigned int len;
        unsigned char * bits;

    public:
        BitList();
        BitList( unsigned int );
        BitList( unsigned int, bool );
        ~BitList();

        unsigned int length() const;

        void init( unsigned int );
        void clear();
        void setAllTo( bool );

        //void clear( unsigned int );
        //void set( unsigned int );

        void set( unsigned int, bool );

        bool get( unsigned int ) const;

        bool operator [] ( unsigned int ) const;

        BitList& operator += ( unsigned int );
        BitList& operator -= ( unsigned int );
};

#endif /* _BITLIST_H */
