//
//  window.cpp
//  cpp-project
//
//  Created by Celso Dantas on 12/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include "WindowManager.h"

WindowManager::WindowManager(WindowManagerAdapter *adapter) 
{
    _adapter = adapter;
    
    /*
     * Default configurations
     */
    _widthRes   = 800;
    _heightRes  = 600;
}   

WindowManager::~WindowManager()
{
    delete _adapter;
    
    closeWindow();
}

void WindowManager::setWindowSize(int width, int height) 
{
    _widthRes   = width;
    _heightRes  = height;
}

int WindowManager::openWindow() 
{
    return _adapter->openWindow(_widthRes, _heightRes);
}

void WindowManager::setFullScreen(bool fullscreen) 
{
    _adapter->setFullScreen(fullscreen);
}

void WindowManager::swapBuffers() 
{
    _adapter->swapBuffers();
}

void WindowManager::closeWindow()
{
    _adapter->closeWindow();
}
