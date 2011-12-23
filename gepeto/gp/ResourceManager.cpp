//
//  ResourceManager.cpp
//  gepeto
//
//  Created by Celso Dantas on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "ResourceManager.h"
#include "Core.h"
#include "render/Render.h"



int ResourceManager::init()
{
    /*
     * Initializations
     */
    return 1;
}

void ResourceManager::start()
{
    _windowManager  = new WindowManager();
    _render         = new Render();
    _core           = new Core(this);
    
    _core->setResourceManager(this);
    _core->setRender         (_render);
    
    _windowManager->openWindow();
    _core->loop();
}

#include "../GL/glfw.h"
void ResourceManager::swapBuffers()
{
    glfwSwapBuffers();
}