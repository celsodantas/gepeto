//
//  Render.cpp
//  cpp-project
//
//  Created by Celso Dantas on 12/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "opengl.h"
#include "Render.h"

#include <gl/glut.h>
#include <vector>
#include "../loader/collada/ColladaLoader.h"
#define BUFFER_OFFSET(offset) ((GLvoid *) offset)
GLuint bufPointer[3];
extern std::vector<geometry_asset> *assets;

Render::Render()
{
    _red    = 0.0f;
    _green  = 0.0f;
    _blue   = 0.0f;
    _alpha  = 0.0f;
    
    glShadeModel(GL_SMOOTH);
	
    // Raw Antialiasing
    glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);             
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    // Configure culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    
    //////////////
    //  VBO test
    //////////////

    ////
    // This is temporary
    ////
    glGenBuffers(3, bufPointer);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    for (unsigned int i = 0; i < assets->size(); ++i) {
        geometry_asset asset = assets->at(i);
        
        // VERTICES
        glBindBuffer(GL_ARRAY_BUFFER, bufPointer[0]);
        glBufferData(GL_ARRAY_BUFFER, asset.map["POSITION"].size, asset.map["POSITION"].data, GL_STATIC_DRAW);
        
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        
        // NORMALS
        glBindBuffer(GL_ARRAY_BUFFER, bufPointer[1]);
        glBufferData(GL_ARRAY_BUFFER, asset.map["NORMAL"].size, asset.map["NORMAL"].data, GL_STATIC_DRAW);
        
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        
        // INDICES
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufPointer[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, asset.indices_qtd * sizeof(unsigned short), asset.indices, GL_STATIC_DRAW);
    }
    
    // This is temporary
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };
    GLfloat light_position[] = { -2.0f, 2.0f, -3.0f, 0.0f };
    GLfloat white_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lmodel_ambient[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
 
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void Render::draw() 
{
    clearScreen();
    clearScreenColor(_red, _green, _blue, _alpha);
        
    
    for (unsigned int i = 0; i < assets->size(); ++i) {
        glFrontFace(GL_CW);
        
        geometry_asset asset = assets->at(i);
        
        // Vertexes
        glBindBuffer(GL_ARRAY_BUFFER, bufPointer[0]);
        glVertexPointer(asset.map["POSITION"].stride, GL_FLOAT, 0, BUFFER_OFFSET(0));  
        
        // Normals    
        glBindBuffer(GL_ARRAY_BUFFER, bufPointer[1]);
        glNormalPointer(GL_FLOAT, asset.map["NORMAL"].stride, BUFFER_OFFSET(0));
        
        // Indexes
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufPointer[2]);
        
        glDrawElements(asset.primitive, asset.indices_qtd, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
    }
    
    
    glFrontFace(GL_CW);
    glTranslated(2.0, 0.0, 2.0);
	glutSolidCube(2.0);
}

void Render::clearScreen()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Render::clearScreenColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}