//
//  window.h
//  cpp-project
//
//  Created by Celso Dantas on 12/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __gp_window_manager_h
#define __gp_window_manager_h

#include "WindowManagerAdapter.h"

class WindowManager {
public: 
    WindowManager(WindowManagerAdapter *adapter);
    ~WindowManager();
    void setWindowSize(int width, int height);
    int  openWindow();
    void setFullScreen(bool fullscreen);
    void swapBuffers();
private:
    void closeWindow();
    
    WindowManagerAdapter *_adapter;
    int _widthRes, _heightRes;
    int _mode;
};

#endif
