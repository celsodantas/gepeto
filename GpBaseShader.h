/*
 *  GpShader.h
 *  GEPETO
 *
 *  Created by Celso Dantas on 11/8/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GPSHADER_H
#define GPSHADER_H

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include "GpIO.h"

class GpBaseShader {
	
private:
	bool _on;	// Define if it's on/off
	
protected:
	GLuint loadProgram(const char* vertexFile, const char* fragmentFile);
	
	void printShaderInfoLog(GLuint obj);
	void printProgramInfoLog(GLuint obj);
	
	GLuint _programId;
	
public:
	GpBaseShader(const char* vertexFile, const char* fragmentFile);
	inline void activate()		{ glUseProgram(_programId);	}
	inline void deactivate()	{ glUseProgram(0);			}
	inline GLuint program()		{ return _programId;		}

	inline bool on()
	{
		return _on;
	}
	
	inline void turnOn()
	{
		_on = true;
	}
	
	inline void turnOff()
	{
		_on = false;
	}
	
};

#endif