//
//  WindowManagerAdapter.h
//  gepeto
//
//  Created by Celso Dantas on 06/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_WindowManagerAdapter_h
#define gepeto_WindowManagerAdapter_h

class WindowManagerAdapter
{
public:
    virtual ~WindowManagerAdapter() {};
    virtual int  openWindow(int width, int height) = 0;
    virtual void setFullScreen(bool fullscreen) = 0;
    virtual void swapBuffers() = 0;
    virtual void closeWindow() = 0;
};

#endif
