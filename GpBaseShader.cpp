/*
 *  GpShader.cpp
 *  GEPETO
 *
 *  Created by Celso Dantas on 11/8/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GpBaseShader.h"

#include "system_assets/filesystem.h"

GpBaseShader::GpBaseShader(const char* vertexFile, const char* fragmentFile) 
{
	_on = false;
	
	if ( (vertexFile != NULL) && (fragmentFile != NULL)) {
		_programId = loadProgram(vertexFile, fragmentFile);
	}
}

GLuint GpBaseShader::loadProgram(const char* vertex, const char* fragment) 
{
    
	char vertexAux[500], fragmentAux[500];
    
    std::string sVertex = Filesystem().resourcesPath();
    std::string sFrag = Filesystem().resourcesPath();

    sVertex += vertex;
    sFrag += fragment;
    
    strcpy(vertexAux, (char*)sVertex.c_str());
    strcpy(fragmentAux, (char*)sFrag.c_str());
	
	char *vs,*fs;
	GpIO io;
	
	GLuint programId = 0;
	GLuint vPath, fPath;
	
	vPath = glCreateShader(GL_VERTEX_SHADER);
	fPath = glCreateShader(GL_FRAGMENT_SHADER);	
	
	vs = io.textFileRead(vertexAux);
	fs = io.textFileRead(fragmentAux);
	
	const char * vv = vs;
	const char * ff = fs;
	
	glShaderSource(vPath, 1, &vv, NULL);
	glShaderSource(fPath, 1, &ff, NULL);
	
	glCompileShader(vPath);
	glCompileShader(fPath);
	
	programId = glCreateProgram();
	
	glAttachShader(programId, vPath);
	glAttachShader(programId, fPath);
	
	glLinkProgram(programId);
	
	printProgramInfoLog(programId);
	
	printShaderInfoLog(vPath);
	printShaderInfoLog(fPath);
	
	free(vs); free(fs);
	
	return programId;
}

///////////////////////
// DEBUGUING printers

void GpBaseShader::printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	
	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
	
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}

void GpBaseShader::printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
	
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}