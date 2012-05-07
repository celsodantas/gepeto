/*
 *  GpBasePostShader.cpp
 *  GEPETO
 *
 *  Created by Celso Dantas on 11/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GpBasePostShader.h"


GpBasePostShader::GpBasePostShader(const char* vertexFile, const char* fragmentFile)
: GpBaseShader(vertexFile, fragmentFile)
{
	_fboId = genFramebuffer();
	_textureId = genTexture();
	_renderBufferId = genRenderbuffer();
}

GLuint GpBasePostShader::genFramebuffer() 
{
	GLuint buff = 0;
	
	glGenFramebuffers(1, &buff);												// create a new framebuffer
	
	if (buff == 0) printf("Falha em gerar o framebuffer.");
	
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, buff);	
	
	return buff;	
}

GLuint GpBasePostShader::genTexture() 
{
	GLuint tex = 0;
	
	glGenTextures(1, &tex);																		// and a new texture used as a color buffer
	
	// initialize Color Texture (Color Buffer)
	glBindTexture(GL_TEXTURE_2D, tex);															// Bind the colorbuffer texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);							// make it linear filterd
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1024, 1024, 0,GL_RGBA, GL_INT, NULL);				// Create the texture data
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);	// attach it to the framebuffer
	
	return tex;
}

GLuint GpBasePostShader::genRenderbuffer() 
{
	GLuint rendbuff;
	
	glGenRenderbuffers(1, &rendbuff);											// And finaly a new depthbuffer
	
	glBindRenderbuffer(GL_RENDERBUFFER, rendbuff);								// bind the depth renderbuffer
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 1024, 1024);		// get the data space for it
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rendbuff); // bind it to the renderbuffer
	
	
	return rendbuff;
}

void GpBasePostShader::finishFramebufferCreation()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);	
}