//
//  Core.cpp
//  gepeto
//
//  Created by Celso Dantas on 12/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Core.h"
#include "ResourceManager.h"
#include "render/Render.h"

#include "Game.h"

#include "Util.h"

Core::Core(ResourceManager *manager)
{
    _manager = manager;
}

void Core::loop(Game &game)
{
    int running = 1;
    
    double elapsedSecs;
    
    elapsedSecs = Util::elapsedTimeSecs();
    
    while (running) {
        elapsedSecs = Util::elapsedTimeSecs();
        
        game.frame(elapsedSecs);
        
        _render->draw();
    
        swapBuffers();
    }
}

void Core::swapBuffers() 
{
    _manager->windowManager()->swapBuffers();
}