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

#include "GLFWAdapter.h"

int ResourceManager::init()
{
    /*
     * Initializations
     */
    return 1;
}

void ResourceManager::start()
{
    GAMECLASS game(&Gepeto::instance());
    _windowManager  = new WindowManager(new GLFWAdapter);
    _windowManager->openWindow();
    
    _render         = new Render();
    _core           = new Core(this);
    
    _core->setRender(_render);

    game.setup();
    
    _core->loop(game);
}

void ResourceManager::swapBuffers()
{
    glfwSwapBuffers();
}