//
//  gepeto.cpp
//  cpp-project
//
//  Created by Celso Dantas on 12/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "gepeto.h"

// =======================
// Starts Gepeto framework  
// =======================
void Gepeto::start() {
    _manager.init();
    
    //
    // If in need to make any pre-star configuration, 
    // do it here! Just add it before _manager.init()
    //
    
    _manager.start();
}

void Gepeto::setResolution(int width, int height) 
{
    _manager.windowManager()->setWindowSize(width, height);
}

void Gepeto::setFullScreen(bool fullscreen) 
{
    _manager.windowManager()->setFullScreen(true);
}