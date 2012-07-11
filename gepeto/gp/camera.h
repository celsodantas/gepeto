//
//  camera.h
//  gepeto
//
//  Created by Celso Dantas on 08/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_camera_h
#define gepeto_camera_h

#include "glfw.h"

class Camera
{
public:
    Camera() {
        _upX = 0; 
        _upY = 1; 
        _upZ = 0;
        
    }
    
    void addPosX(double v);
    void addPosY(double v);
    void addPosZ(double v);
    
    void lookAt(double x, double y, double z);
    void setPosition(double x, double y, double z);
    void resize();
    
    inline void update() {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 
        
        gluLookAt(_posX,  _posY,  _posZ, 
                  _lookX, _lookY, _lookZ, 
                  _upX,   _upY,   _upZ);
    }
    
private:
    float _posX,
          _posY,
          _posZ;
    
    float _lookX, 
          _lookY, 
          _lookZ;
    
    float _upX, 
          _upY, 
          _upZ;
    
    int _matrix_mode;
};

#endif
