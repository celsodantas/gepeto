//
//  Render.cpp
//  cpp-project
//
//  Created by Celso Dantas on 12/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Render.h"
#include "opengl/gl.h"

Render::Render() 
{
    _red    = 0.1f;
    _green  = 0.5f;
    _blue   = 1.0f;
    _alpha  = 1.0f;
}

void Render::draw() 
{
    clearScreen();
    clearScreenColor(_red, _green, _blue, _alpha);
    
}

void Render::clearScreen()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Render::clearScreenColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}