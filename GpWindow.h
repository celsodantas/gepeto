/*
 *  GpWindow.h
 *  GEPETO
 *
 *  Created by Celso Dantas on 02/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GPWINDOW_H
#define GPWINDOW_H

#include "SDL.h"
#include <OpenGL/OpenGL.h>
#include <stdlib.h>

//#include "GpGlobal.h"

void GpInitialize();
SDL_Surface * GpCreateWindow(short int fullscreen, int widthResolution, int heigthResolution);

#endif