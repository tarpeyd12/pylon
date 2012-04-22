#ifndef _CALLBACKS_H
#define _CALLBACKS_H

class SOLID_CALLBACK
{
    public:
        SOLID_CALLBACK() { };
        virtual ~SOLID_CALLBACK() { };
        virtual void operator()( POGEL::PHYSICS::SOLID *, const char * ) = 0;
};

class SOLID_FUNCTION
{
    public:
        SOLID_FUNCTION() { };
        virtual ~SOLID_FUNCTION() { };
        virtual void operator()( POGEL::PHYSICS::SOLID * ) = 0;
};

class SOLID_HITFILTER
{
    public:
        SOLID_HITFILTER() { };
        virtual ~SOLID_HITFILTER() { };
        virtual bool operator()( POGEL::PHYSICS::SOLID *, POGEL::PHYSICS::SOLID * ) = 0;
};

#endif /* _CALLBACKS_H */
