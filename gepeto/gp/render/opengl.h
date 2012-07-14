
#ifndef __gepeto_opengl
#define __gepeto_opengl

//#define GLEW_STATIC


#ifdef _WIN32
	#include <GL/glew.h>
#else
	#include <opengl/gl.h>
#endif

#   pragma comment (lib, "glew32d.lib")    /* link with Win32 GLUT lib */

#endif