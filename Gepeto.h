/*
 *  Gepeto.h
 *  SDL Project
 *
 *  Created by Celso Dantas on 01/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef GEPETO_FRAMEWORK
#define GEPETO_FRAMEWORK

// #####################
#include <stdlib.h>
#include <list>

#include <GLUT/glut.h>
#include "SDL.h"
#include <OpenGL/OpenGL.h>

#include "GpGlobal.h"

#include "GpObject3D.h"
#include "GpObjectLoader.h"

#include "GpDraw.h"
#include "GpPostShaderManager.h"
// #####################

#include <ctime>
#include <sys/time.h>

extern "C" {
	#include "GpWindow.h"
};

using namespace GepetoObjects;

class Gepeto {
	
public:

	void setResolution(int width, int height);
	void setWindowSize(int width, int heigth);

	GpObject3D * newObject3D();
	GpPostShaderManager* shaderManager();
	void activateShader(GPenum shaderId);
	void deactivateShader(GPenum shaderId);
	
	Gepeto();
	
	void setFullScreen(bool f) {
		fullscreen = f;
	}
	
	void setDisplayFunction(void (*func)()) {
		drawFunction = func;
	}
	
	void setInputFunction(int (*func)(SDL_Event event)) {
		inputFunction = func;
	}

	void start() {
		mainLoop(); // Entrando no loop principal da aplicacao
	}
	
	~Gepeto() {
		SDL_Quit();
	}
	
private:

	SDL_Surface *gScreen;
	GpDraw *_gepetoDraw;
	
	bool fullscreen;
	int widthResolution, heigthResolution;
	
	// Function pointers
	void (*drawFunction)();
	int (*inputFunction)(SDL_Event event);
	
	void createWindow();
	void mainLoop();
	
};

#endif