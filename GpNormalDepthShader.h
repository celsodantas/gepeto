/*
 *  GpNormalDepthShader.h
 *  GEPETO
 *
 *  Created by Celso Dantas on 11/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GPNORMALDEPTHSHADER
#define	GPNORMALDEPTHSHADER

#include "GpBaseShader.h"

class GpNormalDepthShader : public GpBaseShader {
	
public:
	
	GpNormalDepthShader(char* vertexFile, char* fragmentFile)
	: GpBaseShader(vertexFile, fragmentFile) {	}
	
	GpNormalDepthShader()
	: GpBaseShader("v-normal-depth.vs", 
				   "f-normal-depth.fs") {	}
	
	
	
	inline void setUniforms(float near, float far)
	{
		GLuint aux;
		
		aux = glGetUniformLocation(_programId,"near");
		glUniform1f(aux, near);
		
		aux = glGetUniformLocation(_programId,"far");
		glUniform1f(aux, far);
	}

private:
	char _vertexShaderFile[30];
	char _fragmentShaderFile[30];
};

#endif