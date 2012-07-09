//
//  Util.h
//  gepeto
//
//  Created by Celso Dantas on 08/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_Util_h
#define gepeto_Util_h

#ifdef DARWIN
    #include "sys/macos/UtilAdapter.h"
#else  // WINDOWS_OS
    // TODO :: implement OS dependant Util
    #include "sys/macos/UtilAdapter.h"
#endif

class Util
{
    UtilAdapter adapter;

public:
    
    static inline double elapsedTimeSecs()
    {
        return UtilAdapter::elapsedTimeSecs();
    }
};

#endif
