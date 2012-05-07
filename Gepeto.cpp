/*
 *  Gepeto.cpp
 *  SDL Project
 *
 *  Created by Celso Dantas on 01/09/10.
 *  Copyright 2010 NoApp. All rights reserved.
 *
 */

#include "Gepeto.h"



// Constructor
Gepeto::Gepeto() {
	
	// Default configurations...
	fullscreen = false;
	
	widthResolution = 800;
	heigthResolution = 500;
	
	// Criando a janela
	createWindow();
		
	GpInitialize();
	
	_gepetoDraw = new GpDraw(widthResolution, heigthResolution);
	
}


// Setters
void Gepeto::setResolution(int width, int height){
	widthResolution = width;
	heigthResolution = height;
}

// Methods

// Metodo que cria um objeto 3D
GpObject3D* Gepeto::newObject3D() 
{	
	// Vale criar que o objeto é inicializado com valores padrões
	// isso implica que ele fica invisível assim que é instanciado.
	
	// Instanciando objeto
	GpObject3D *obj3D = new GpObject3D();

	GpGlobal::gpObjsToRender.push_back(obj3D);
	
	return obj3D;
}

GpPostShaderManager* Gepeto::shaderManager()
{
	return GpPostShaderManager::getInstance();
}

void Gepeto::activateShader(GPenum shaderId) 
{
	GpPostShaderManager::getInstance()->activateShader(shaderId);
}

void Gepeto::deactivateShader(GPenum shaderId)
{
	GpPostShaderManager::getInstance()->deactivateShader(shaderId);
}

void Gepeto::createWindow() 
{	// C function ("GpWindow.h")
	gScreen = GpCreateWindow(fullscreen, widthResolution, heigthResolution);	
}

void Gepeto::mainLoop ()
{
    SDL_Event event;
    int done = 0;
    int hz = 30;
	int delay = 1000/hz;
    int thenTicks = -1;
    int nowTicks;
    
    unsigned long loop_count = 0; 
    float average = 0.0;
    
    timeval tBegin, tEnd;
    
    //tBegin = mach_absolute_time();
    gettimeofday(&tBegin, NULL);
    
    while ( !done ) {
        
		/* Check for events */
		while ( SDL_PollEvent (&event) ) 
        {
            done = (*inputFunction)(event);	// Keyboard function pointer	
		}
		
        // Draw at 30 hz
        //     This approach is not normally recommended - it is better to
        //     use time-based animation and run as fast as possible
		
		_gepetoDraw->draw();			// Funcao de desenho do GEPETO 
        (*drawFunction)();              // "Function pointer" p/ funcao do usuario
		
        SDL_GL_SwapBuffers ();
		
        // Time how long each draw-swap-delay cycle takes
        // and adjust delay to get closer to target framerate
//        if (thenTicks > 0) {
//            nowTicks = SDL_GetTicks ();
//            delay += (1000/hz - (nowTicks-thenTicks));
//            thenTicks = nowTicks;
//            if (delay < 0)
//                delay = 1000/hz;
//        }
//        else {
//            thenTicks = SDL_GetTicks ();
//        }
		
        //SDL_Delay (delay);
        
        // ##############
        

        gettimeofday(&tEnd, NULL);
        double elapsed = (tEnd.tv_sec - tBegin.tv_sec) * 1000.0;      // sec to ms
        elapsed += (tEnd.tv_usec - tBegin.tv_usec) / 1000.0;   // us to ms
        elapsed /= 1000;
        
        double aux = ((average * loop_count) + elapsed);        
        loop_count ++;  
        average = aux / loop_count;
        
        double fps = 1/elapsed;
        
        std::cout << "fps: " << fps << std::endl;
        
        tBegin = tEnd;
	}
}

