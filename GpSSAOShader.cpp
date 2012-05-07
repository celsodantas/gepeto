/*
 *  GpSSAOShader.cpp
 *  GEPETO
 *
 *  Created by Celso Dantas on 11/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GpSSAOShader.h"

GLuint GpSSAOShader::execute(GLuint normalDepthMapId, GLuint colorMapId)
{
	_passOne.activate();
	_passOne.setUniform(normalDepthMapId);
	_passOne.draw();
	
	GLuint passOneTexturedId = _passOne.renderedTexture();
	
	_passTwo.activate();
	_passTwo.setUniform(passOneTexturedId, colorMapId);
	_passTwo.draw();
	
	_passTwo.deactivate();
	
	return _passTwo.renderedTexture();
}


void GpSSAOShader::SsaoPassOne::setUniform(GLuint normalDepthMapId) 
{
	static GLuint aux1;
	
	aux1 = glGetUniformLocation(_programId, "rand");
	glUniform1i(aux1, 0);	// Texture 0
	
	aux1 = glGetUniformLocation(_programId, "normalMap");
	glUniform1i(aux1, 1);	// Texture 1
	
	// Normal and Depth
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalDepthMapId);
	
	// Noise
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _randomTextureId);
}

void GpSSAOShader::SsaoPassTwo::setUniform(GLuint shadowMapId, GLuint colorMapId) 
{
	static GLuint aux1;
	
	glEnable(GL_TEXTURE_2D);
	//
	aux1 = glGetUniformLocation(_programId, "ssaoMap");
	glUniform1i(aux1, 0);	// Texture 0
	
	aux1 = glGetUniformLocation(_programId, "realModel");
	glUniform1i(aux1, 1);	// Texture 1
	
	aux1 = glGetUniformLocation(_programId, "ssaoMap");
	glUniform1i(aux1, 2);	// Texture 1
	
	// ----
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, shadowMapId);
	
	// ----
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, colorMapId);
	
	// ----
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shadowMapId);
}