//
//  GLFWAdapter.cpp
//  gepeto
//
//  Created by Celso Dantas on 06/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GLFWAdapter.h"

GLFWAdapter::GLFWAdapter()
{
    _mode = GLFW_WINDOW;
}

int  GLFWAdapter::openWindow(int width, int height)
{
    if ( glfwInit() < 0 ) 
    {
        std::cout << "Error initializing glfwInit() in " << __FILE__ << ":" << __LINE__ << std::endl;
        exit( EXIT_FAILURE );
    }
    
    if ( glfwOpenWindow(width, height, 0, 0, 0, 0, 16, 0, _mode) < 0) 
    {
        closeWindow();
        std::cout << "Error opening windows glfwOpenWindow() in " << __FILE__ << ":" << __LINE__ << std::endl;
        exit( EXIT_FAILURE );
    }
    
	glewInit();

    return 1;
}

void GLFWAdapter::setFullScreen(bool fullscreen)
{
    if (fullscreen) 
        _mode = GLFW_FULLSCREEN;
    else 
        _mode = GLFW_WINDOW;
}

void GLFWAdapter::swapBuffers() 
{
    glfwSwapBuffers();
}

void GLFWAdapter::closeWindow()
{
     glfwTerminate();
}