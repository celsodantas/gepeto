/*
 *  GpRadialBlur.h
 *  GEPETO
 *
 *  Created by Celso Dantas on 12/4/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __GPRADIALBLURSHADER__
#define __GPRADIALBLURSHADER__

#include "GpBasePostShader.h"

#include "Texture.h"

class GpRadialBlurShader : public GpBasePostShader {

public:
	
	GpRadialBlurShader() : GpBasePostShader("v-radblur.vs", "f-radblur.fs") { }
	
	GLuint execute(GLuint colorMapId, float sampleStrength)
	{
		glUseProgram(_programId);
		setUniforms(colorMapId, sampleStrength);
		
		return renderedTexture();
	}
	
	inline void setUniforms(GLuint colorMapId, float sampleStrength)
	{
		GLuint aux;
		
		aux = glGetUniformLocation(_programId, "sampleStrength");
		glUniform1f(aux, sampleStrength);
		
		aux = glGetUniformLocation(_programId, "tex");
		glUniform1i(aux, 3);	// Texture 0
		
		// ----
		
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, colorMapId);
		
		glActiveTexture(GL_TEXTURE0);
	}
	
};

#endif