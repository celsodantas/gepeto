/*
 *  GpBasePostShader.h
 *  GEPETO
 *
 *  Created by Celso Dantas on 11/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef GPBASEPOSTSHADER
#define GPBASEPOSTSHADER

#include <GLUT/GLUT.h>
#include "GpBaseShader.h"


class GpBasePostShader : public GpBaseShader {

protected:
	GLuint _fboId, _renderBufferId, _textureId;
	
	GLuint genFramebuffer();
	GLuint genFboTexture();
	GLuint genRenderbuffer(); 
	GLuint genTexture();
	void finishFramebufferCreation();
	
public:
	GpBasePostShader(const char* vertexFile, const char* fragmentFile);
	
	inline GLuint renderedTexture()
	{
		return _textureId;
	}
	
	inline void draw()
	{
		// TODO:: Verificar isso. Passar para um parametro global?
		// Diz respeito à qualidade da imagem renderizada.
		static int windowHeight = 1024;
		static int windowWidth = 1024;
		
		glBindTexture(GL_TEXTURE_2D, 0);						// unlink textures because if we dont it all is gonna fail
		glBindFramebuffer(GL_FRAMEBUFFER, _fboId);				// switch to rendering on our FBO
		glDisable(GL_TEXTURE_2D);
		
		glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT);
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
			
			glViewport(0, 0, windowHeight, windowWidth);		// set The Current Viewport to the fbo size
			
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
			
			drawQuads();
		
		glPopAttrib();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);					// Unlink FBO
		
	}
	
	inline void drawQuads()
	{
		glBegin(GL_QUADS);
		
		glVertex3f(-1, -1,  1);
		glVertex3f( 1, -1,  1);
		glVertex3f( 1,  1,  1);
		glVertex3f(-1,  1,  1);
		
		glEnd();
	}
	
};

#endif