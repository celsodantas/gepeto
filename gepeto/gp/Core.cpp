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

// REMOVE ABOVE! IT SHOULD NOT BE HERE!!
#include "../GL/glfw.h"

Core::Core(ResourceManager *manager)
{
    _manager = manager;
}

void Core::loop()
{
    int running = 1;
    
    while (running) {
        _render->draw();
        
        swapBuffers();
    }
}

void Core::swapBuffers() 
{
    _manager->windowManager()->swapBuffers();
}