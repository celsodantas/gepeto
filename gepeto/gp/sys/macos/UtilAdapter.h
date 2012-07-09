//
//  Util.h
//  gepeto
//
//  Created by Celso Dantas on 08/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_UtilAdapter_h
#define gepeto_UtilAdapter_h

#include <sys/time.h>

///////////////////
//
// This it not a full adapter but it is working like one. =D
//
///////////////////

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
        
        elapsed = ((seconds) * 1000 + useconds/1000.0);
        
        return elapsed/1000.0;
    }
};

#endif
