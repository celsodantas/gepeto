/*
 *  GpWindow.c
 *  GEPETO
 *
 *  Created by Celso Dantas on 02/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GpWindow.h"

void GpInitialize() {
	
	
	/////////////////////////
	// Inicializando o SDL
	// Init SDL video subsystem
	if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
		
        fprintf(stderr, "Gepeto Error -- Couldn't initialize SDL: %s\n",
				SDL_GetError());
		exit(1);
	}
	
	////////////////////////
	// Configurando atributos de buffer de profundidade e buffer duplo.
	
	// Setup attributes we want for the OpenGL context
    int value;
    
    // Don't set color bit sizes (SDL_GL_RED_SIZE, etc)
    //    Mac OS X will always use 8-8-8-8 ARGB for 32-bit screens and
    //    5-5-5 RGB for 16-bit screens
    
    // Request a 16-bit depth buffer (without this, there is no depth buffer)
    value = 16;
    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, value);
    
    
    // Request double-buffered OpenGL
    //     The fact that windows are double-buffered on Mac OS X has no effect
    //     on OpenGL double buffering.
    value = 1;
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, value);
	
}

SDL_Surface * GpCreateWindow(short int fullscreen, int widthResolution, int heigthResolution) {
	
	Uint32 flags = 0;
	SDL_Surface *gScreen = NULL;

    flags = SDL_OPENGL;
    if (fullscreen) {
		flags |= SDL_FULLSCREEN;
	}
	
	
    // Create window
	gScreen = SDL_SetVideoMode (widthResolution, heigthResolution, 0, flags);
    if (gScreen == NULL) {
		
        fprintf (stderr, "Gepeto Error -- Couldn't set %dx%d OpenGL video mode: %s\n",
				 widthResolution,
				 heigthResolution,
                 SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	
	return gScreen;
	
}