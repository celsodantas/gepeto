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
    _red    = 0.0f;
    _green  = 0.0f;
    _blue   = 0.0f;
    _alpha  = 0.0f;
}

void Render::draw() 
{
    clearScreen();
    clearScreenColor(_red, _green, _blue, _alpha);
    
    glLoadIdentity();
    
    glColor3f(1.0f,0.1f,0.0f);
    
    glBegin(GL_TRIANGLES); // Drawing Using Triangles
        glVertex3f( 0.0f, 1.0f, 0.0f);              // Top
        glVertex3f(-1.0f,-1.0f, 0.0f);              // Bottom Left
        glVertex3f( 1.0f,-1.0f, 0.0f);              // Bottom Right
    glEnd();                            // Finished Drawing The Triangle
}

void Render::clearScreen()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Render::clearScreenColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}