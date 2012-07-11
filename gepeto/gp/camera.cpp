//
//  camera.cpp
//  gepeto
//
//  Created by Celso Dantas on 08/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Camera.h"

void Camera::resize()
{
    double fov   = 45, 
    aspect       = 1.333333, 
    farClipDist  = 500, 
    nearClipDist = 0.1;
    
    glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
    
    gluPerspective(fov, 
				   aspect, 
				   nearClipDist, 
				   farClipDist);
}

void Camera::lookAt(double x, double y, double z)
{
    _lookX = x;
    _lookY = y;
    _lookZ = z;
}

void Camera::setPosition(double x, double y, double z)
{
    _posX = x;
    _posY = y;
    _posZ = z;
}

void Camera::addPosX(double v)
{
    _posX += v;
}

void Camera::addPosY(double v)
{
    _posY += v;
}

void Camera::addPosZ(double v)
{
    _posZ += v;
}