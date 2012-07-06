//
//  gepeto.h
//  Gepeto Game Engine
//
//  This class is just the facade to the Gepeto framework
//  if you need to add any configuration method the you
//  and the user to has access to, add it in here.
//
//  Created by Celso Dantas on 12/19/11.
//

#ifndef __gp_gepeto_h
#define __gp_gepeto_h

#include "ResourceManager.h"



class Gepeto {
    
public:
    Gepeto(int argc, char **argv) 
    {
        _argc = argc;
        _argv = argv;
    }
    
    void start();
    
    // =============
    // Configuration
    // =============
    void setResolution(int width, int height);
    void setFullScreen(bool fullscreen);
private:
    int _argc;
    char **_argv;
    ResourceManager _manager;
};

#endif
