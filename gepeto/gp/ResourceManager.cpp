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

#include "render/adapters/GLFWAdapter.h"

#include "Gepeto.h"
#include "../Game.h"

ResourceManager::~ResourceManager()
{
    delete _windowManager;
    delete _render;
    delete _core;
}

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