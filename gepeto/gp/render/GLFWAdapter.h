//
//  GLFWAdapter.h
//  gepeto
//
//  Created by Celso Dantas on 06/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_GLFWAdapter_h
#define gepeto_GLFWAdapter_h

#include "WindowManagerAdapter.h"
#include "opengl/gl.h"
#include "../../GL/glfw.h"

class GLFWAdapter: public WindowManagerAdapter
{
public:
    GLFWAdapter();    
    virtual int  openWindow(int width, int height);
    virtual void setFullScreen(bool fullscreen);
    virtual void swapBuffers();
    virtual void closeWindow();
private:
    
    // window/fullscreen
    int _mode;  
};

#endif
