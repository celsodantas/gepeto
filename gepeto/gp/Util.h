//
//  Util.h
//  gepeto
//
//  Created by Celso Dantas on 08/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_Util_h
#define gepeto_Util_h

#include "sys/UtilAdapter.h"

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
