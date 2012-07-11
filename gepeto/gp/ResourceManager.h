//
//  manager.h
//  gepeto
//
//  Created by Celso Dantas on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __gp_resource_manager_h
#define __gp_resource_manager_h

#include "render/WindowManager.h"

class Core;
class Render;
class Gepeto;

class ResourceManager {
public:
    ResourceManager() {}
    ~ResourceManager();
    int  init();
    void start();
    
    void swapBuffers();
    
    WindowManager* windowManager()           { return _windowManager; }
    void setWindowManager(WindowManager *w)  { _windowManager = w; }
    
private:
    WindowManager *_windowManager;
    Core *_core;
    Render *_render;
};


#endif
