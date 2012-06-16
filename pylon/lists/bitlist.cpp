#include "bitlist.h"

BitList::BitList() : numbytes( 0 ), len( 0 ), bits( NULL )
{

}

BitList::BitList( unsigned int l ) : numbytes( ( l >> 3 ) + 1 ), len( l )
{
    bits = new unsigned char[ numbytes ];

    memset( bits, 0, numbytes );
}

BitList::BitList( unsigned int l, bool v ) : numbytes( ( l >> 3 ) + 1 ), len( l )
{
    bits = new unsigned char[ numbytes ];

    if( v )
    {
        memset( bits, 0xff, numbytes );
    }
    else
    {
        memset( bits, 0x00, numbytes );
    }
}

BitList::~BitList()
{
    if( bits )
    {
        delete [] bits;
    }
    bits = NULL;
    numbytes = 0;
    len = 0;
}

unsigned int
BitList::length() const
{
    return len;
}

void
BitList::init( unsigned int l )
{
	if( bits )
	{
		delete [] bits;
	}
	bits = NULL;

	len = l;
	numbytes = ( len >> 3 ) + 1;

	bits = new unsigned char[ numbytes ];

	memset( bits, 0x00, numbytes );
}

void
BitList::clear()
{
	memset( bits, 0x00, numbytes );
}

void
BitList::setAllTo( bool v )
{
	if( v )
    {
        memset( bits, 0xff, numbytes );
    }
    else
    {
        memset( bits, 0x00, numbytes );
    }
}

void
BitList::set( unsigned int b, bool v )
{
    if(b>>3>=length())
    {
        throw int(-1);
    }
    if( v )
    {
        bits[ b >> 3 ] |= 1 << ( b & 7 );
    }
    else
    {
        bits[ b >> 3 ] &= ~( 1 << ( b & 7 ) );
    }
}

bool
BitList::get( unsigned int b ) const
{
    if(b>>3>=length())
    {
        throw int(-1);
    }
    return (bool)bits[ b >> 3 ] & 1 << ( b & 7 );
}

bool
BitList::operator [] ( unsigned int b ) const
{
    if(b>>3>=length())
    {
        throw int(-1);
    }
    return (bool)bits[ b >> 3 ] & 1 << ( b & 7 );
}

BitList&
BitList::operator += ( unsigned int b )
{
    if(b>>3>=length())
    {
        throw int(-1);
    }
    bits[ b >> 3 ] |= 1 << ( b & 7 );
    return *this;
}

BitList&
BitList::operator -= ( unsigned int b )
{
    if(b>>3>=length())
    {
        throw int(-1);
    }
    bits[ b >> 3 ] &= ~( 1 << ( b & 7 ) );
    return *this;
}

