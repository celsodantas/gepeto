//
//  Render.cpp
//  cpp-project
//
//  Created by Celso Dantas on 12/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "opengl/gl.h"
#include "Render.h"

#include "glfw.h"

#define BUFFER_OFFSET(offset) ((GLvoid *) offset)
GLuint bufPointer[2];

Render::Render()
{
    _red    = 0.0f;
    _green  = 0.0f;
    _blue   = 0.0f;
    _alpha  = 0.0f;
    
//  glEnable(GL_AUTO_NORMAL);
//	glEnable(GL_NORMALIZE);
    
    glShadeModel(GL_SMOOTH);
	
    // Raw Antialiasing
    glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);             
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    // Configure culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    
    //////////////
    //  VBO test
    //////////////
    
    glEnableClientState(GL_VERTEX_ARRAY);

    GLfloat vertices[24] = { 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1, 1, 1, 1, 1, -1, 1, -1, -1, 1, -1, 1, 1 };
    GLubyte indices[24] =  { 0, 1, 2, 3, 4, 7, 6, 5, 0, 4, 5, 1, 1, 5, 6, 2, 2, 6, 7, 3, 4, 0, 3, 7 };
    
    glGenBuffers(2, bufPointer);
    
    // VERTICES
    glBindBuffer(GL_ARRAY_BUFFER, bufPointer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
    
    // INDICES
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufPointer[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Render::draw() 
{
    clearScreen();
    clearScreenColor(_red, _green, _blue, _alpha);
        
    // Vertexes
    glBindBuffer(GL_ARRAY_BUFFER, bufPointer[0]);
    glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));  
    
    // Normals    
    //glNormalPointer(GL_FLOAT, 24, BUFFER_OFFSET(12));
    
    // Indexes
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufPointer[1]);
    
    glColor3f(1.0f, 0.0f, 0.0f);    // RED
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));

}

void Render::clearScreen()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Render::clearScreenColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}