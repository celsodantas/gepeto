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

#include "opengl/gl.h"
#include "../../GL/glfw.h"

WindowManager::WindowManager() 
{
    /*
     * Default configurations
     */
    _widthRes   = 800;
    _heightRes  = 600;
    
    _mode       = GLFW_WINDOW;
}   

WindowManager::~WindowManager()
{
    closeWindow();
}

void WindowManager::setWindowSize(int width, int height) 
{
    _widthRes   = width;
    _heightRes  = height;
}

int WindowManager::openWindow() 
{
    if ( glfwInit() < 0 ) 
    {
        std::cout << "Error initializing glfwInit() in " << __FILE__ << ":" << __LINE__ << std::endl;
        exit( EXIT_FAILURE );
    }
    
    if ( glfwOpenWindow(_widthRes, _heightRes, 0, 0, 0, 0, 0, 0, GLFW_WINDOW) < 0) 
    {
        closeWindow();
        std::cout << "Error opening windows glfwOpenWindow() in " << __FILE__ << ":" << __LINE__ << std::endl;
        exit( EXIT_FAILURE );
    }
    
    return 1;
}

void WindowManager::setFullScreen(bool fullscreen) 
{
    if (fullscreen) 
        _mode = GLFW_FULLSCREEN;
    else 
        _mode = GLFW_WINDOW;
}

void WindowManager::swapBuffers() 
{
    glfwSwapBuffers();
}

void WindowManager::closeWindow()
{
    glfwTerminate();
}
