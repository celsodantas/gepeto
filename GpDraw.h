/*
 *  GpDraw.h
 *  GEPETO
 *
 *  Created by Celso Dantas on 02/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GPDRAW_H
#define GPDRAW_H

#include <stdlib.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include "SDL.h"

#include <list>
#include "GpGlobal.h"

#include "GpNormalDepthShader.h"
#include "GpPostShaderManager.h"


using namespace GepetoObjects;

class GpDraw {
	
public:
	
	void draw();
	void initialize();
	void initViewport();
	
	void setRgbCleanColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	
	// DEBUG
	void createVBO();
	
	GpDraw(int w, int h);
	
private:
	
	typedef struct projAspects {
		GLfloat nearClipDist, farClipDist;
		GLfloat aspect;
		GLfloat fov;
	};
	
	projAspects projMatrixConfig;
	
	void drawElement(GpObject3D &o);
	
	void cleanWindow();
	void drawFullScreenSquare();
	
	void initFrameBuffer();
	void setViewport();
	void setPerspectiveView();
	void setOrthographicView(); 
	
	GLfloat _viewportSizeX, _viewportSizeY;
	
	GLfloat _red, _green, _blue, _alpha;
	
	GpPostShaderManager *_shaderManager;
	GpNormalDepthShader _normalDepthShader;
	GLuint _lastRenderedTexture;
	
	
	void genFBO();
	void enableFBO();
	void disableFBO();
	GLuint _fboId, _texturesId[2], _renderbufferId;
	
};




#endif