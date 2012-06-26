//#include <GL/glut.h>

#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "pogel.h"
#include "pogel_internals.h"


#if defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)

#include <windows.h>

inline
LARGE_INTEGER
getFILETIMEoffset()
{
    SYSTEMTIME s;
    FILETIME f;
    LARGE_INTEGER t;

    s.wYear = 1970;
    s.wMonth = 1;
    s.wDay = 1;
    s.wHour = 0;
    s.wMinute = 0;
    s.wSecond = 0;
    s.wMilliseconds = 0;
    SystemTimeToFileTime( &s, &f );
    t.QuadPart = f.dwHighDateTime;
    t.QuadPart <<= 32;
    t.QuadPart |= f.dwLowDateTime;
    return t;
}

inline
int
clock_gettime( int X, struct timeval *tv )
{
    static LARGE_INTEGER    offset;
    static double           frequencyToMicroseconds;
    static bool             initialized = false;
    static bool             usePerformanceCounter = false;

    if( !initialized )
    {
        initialized = true;

        LARGE_INTEGER performanceFrequency;
        usePerformanceCounter = (bool)QueryPerformanceFrequency( &performanceFrequency );
        if( usePerformanceCounter )
        {
            QueryPerformanceCounter( &offset );
            frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.0;
        }
        else
        {
            offset = getFILETIMEoffset();
            frequencyToMicroseconds = 10.0;
        }
    }

    if( !tv )
    {
        return -1;
    }

    LARGE_INTEGER           t;
    FILETIME                f;
    double                  microseconds;

    if( usePerformanceCounter )
    {
        QueryPerformanceCounter( &t );
    }
    else
    {
        GetSystemTimeAsFileTime( &f );
        t.QuadPart = f.dwHighDateTime;
        t.QuadPart <<= 32;
        t.QuadPart |= f.dwLowDateTime;
    }

    t.QuadPart -= offset.QuadPart;
    microseconds = (double)t.QuadPart / frequencyToMicroseconds;
    t.QuadPart = microseconds;

    tv->tv_sec = t.QuadPart / 1000000;
    tv->tv_usec = t.QuadPart % 1000000;

    return 0;
}

#define CLOCK_MONOTONIC 0

#define timespec timeval

#endif

// pogel global variables
namespace POGEL
{
	volatile double start, finish, start_long, finish_long;
	volatile unsigned long frames;
	volatile float fps, fps_long;

    volatile double inittime, curtime;

	volatile double duration;
	volatile unsigned long inittmpst;

	volatile float framerate_throtling_correction = 1.0f;
}

void
POGEL::InitFps()
{
	POGEL::start =  POGEL::start_long = 0.0;
	POGEL::inittmpst = 0;
	POGEL::duration = 0.0;

	//
    struct timespec begin;
    clock_gettime( CLOCK_MONOTONIC, &begin );
    #if defined(LINUX) || defined(_LINUX) || defined(linux)
        POGEL::inittime = POGEL::curtime = double( begin.tv_sec ) + double( begin.tv_nsec ) / 1000000000.0;
    #elif defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)
        POGEL::inittime = POGEL::curtime = double( begin.tv_sec ) + double( begin.tv_usec ) / 1000000.0;
    #endif
    //

    /*#else
        POGEL::inittime = POGEL::curtime = double( clock() ) / double( CLOCKS_PER_SEC );
    #endif*/
}

void
POGEL::IncrementFps()
{
	float cur = POGEL::GetTimePassed();
	POGEL::finish = cur;
	if( frames % POGEL_FPS_UPDATE_AVERAGE == 0 )
	{
		POGEL::finish_long = cur;
		POGEL::fps_long = 1.0f / fabs(POGEL::finish_long - POGEL::start_long);
		POGEL::start_long = cur;
	}
	++POGEL::frames;
	POGEL::fps = 1.0f / fabs( POGEL::finish - POGEL::start );
	//POGEL::fps += POGEL::fps_long;
	//POGEL::fps /= 2.0f;
	POGEL::start = cur;
}

float
POGEL::GetFps()
{
	return ( POGEL::fps + POGEL::fps_long ) / 2.0f;
}

void
POGEL::PrintFps()
{
	float timepassed = POGEL::GetTimePassed();
	float gfps = POGEL::GetFps();
	POGEL::message("Frame:%u,Fps:%6.2f(%5.2favg),Spf:%7.5f,Duration:%0.4fs(%d:%02d:%05.2f)\n",
		POGEL::frames,
		(gfps>999.999?999.999:gfps),
		POGEL::GetAverageFps(),
		POGEL::GetSecondsPerFrame(),
		timepassed,
		(unsigned int)timepassed/3600, ((unsigned int)timepassed/60)%60, fmod(timepassed,60)
	);
}

void
POGEL::SetFramerateThrotle( float framerate )
{
	POGEL::framerate_throtling_correction = framerate;
}

float
POGEL::GetAverageFps()
{
	return float(POGEL::frames)/POGEL::GetTimePassed();
}

float
POGEL::GetSecondsPerFrame()
{
    return 1.0f / POGEL::GetFps();
}

double
POGEL::GetTimePassed()
{
    /*clock_t c = clock();
    float t = float( c - POGEL::curtime ) / float( CLOCKS_PER_SEC );
    if( t >= float( CLOCKS_PER_SEC ) )
    {
        POGEL::curtime = c;
        POGEL::duration += t;
        t = 0.0f;
    }
    return t + POGEL::duration;*/


    //
    struct timespec current;
    clock_gettime( CLOCK_MONOTONIC, &current );
    #if defined(LINUX) || defined(_LINUX) || defined(linux)
        double c = ( double( current.tv_sec ) + double( current.tv_nsec ) / 1000000000.0 );
    #elif defined(WINDOWS) || defined(_WIN32) || defined(_WIN64)
        double c = ( double( current.tv_sec ) + double( current.tv_usec ) / 1000000.0 );
    #endif
    double t = c - POGEL::curtime;
    POGEL::curtime = c;
    POGEL::duration += t;
    return POGEL::duration;
    //

    /*#else
        clock_t c = clock();
        double t = double( c - POGEL::curtime ) / double( CLOCKS_PER_SEC );
        POGEL::curtime = c;
        POGEL::duration += t;
        return POGEL::duration;
    #endif*/
}

void
POGEL::ThrotleFps( int desitredFramerate )
{
	float dfr = float(desitredFramerate) - ( POGEL::fps*2.0f - POGEL::fps_long );
	if( dfr < 0.0f )
	{
		dfr = 1.0f / dfr;
	}
	POGEL::SetFramerateThrotle( 1.0f / fabs( dfr ) );
}

void
POGEL::UnthrotleFps()
{
	POGEL::SetFramerateThrotle( 1.0f );
}
