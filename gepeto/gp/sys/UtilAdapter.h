//
//  Util.h
//  gepeto
//
//  Created by Celso Dantas on 08/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_UtilAdapter_h
#define gepeto_UtilAdapter_h

#ifdef _WIN32
#include <Windows.h>
#include <time.h>
#else
#include <sys/time.h>
#endif

///////////////////
//
// This it not a full adapter but it is working like one. =D
//
///////////////////

#if defined(_MSC_VER) || defined(__MINGW32__)
int gettimeofday(struct timeval* tp, void* tzp) {
    DWORD t;
    t = timeGetTime();
    tp->tv_sec = t / 1000;
    tp->tv_usec = t % 1000;
    /* 0 indicates that the call succeeded. */
    return 0;
}
#endif


class UtilAdapter
{
public:
    
    static inline double elapsedTimeSecs()
    {
        static timeval now, prev;
        static long elapsed, seconds, useconds;    
        
        prev = now;
        gettimeofday(&now, NULL);
        
        seconds  = now.tv_sec  - prev.tv_sec;
        useconds = now.tv_usec - prev.tv_usec;
        
        elapsed = (long) ((seconds) * 1000 + useconds/1000.0);
        
        return elapsed/1000.0;
    }
};

#endif
