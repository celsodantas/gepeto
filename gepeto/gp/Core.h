//
//  Core.h
//  gepeto
//
//  Created by Celso Dantas on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_Core_h
#define gepeto_Core_h

class ResourceManager;
class Render;

class Core
{
public:
    Core(ResourceManager *manager);
    void loop();
    
    void setRender(Render *render)                      { _render = render; }
private:
    void swapBuffers();
    
    ResourceManager *_manager;
    Render          *_render;
};

#endif
