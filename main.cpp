
/* Simple program:  Create a blank window, wait for keypress, quit.

   Please see the SDL documentation for details on using the SDL API:
   /Developer/Documentation/SDL/docs.html
*/
   
#include "Gepeto.h"

static Gepeto *g;
static GpObject3D *obj[10];
static GpPostShaderManager *shaderManager;

static float rotation = 0;
static float blur = 1.0;

static bool ssaoOn = false;
static bool radialbluOn = false;

int keyinput(SDL_Event event) {
	//puts("inside keyinput...");
	
	if (event.type == SDL_KEYDOWN) {

		switch (event.key.keysym.sym) {
				
			case SDLK_RIGHT:
				rotation = 2;
				break;
			case SDLK_LEFT:
				rotation = -2;
				break;
			case '1':
				if (ssaoOn) {
					ssaoOn = false;
					g->deactivateShader(GP_SHADER_SSAO);
				} else {
					ssaoOn = true;
					g->activateShader(GP_SHADER_SSAO);
				}
				break;
			case '2':
				if (radialbluOn) {
					radialbluOn = false;
					g->deactivateShader(GP_SHADER_RADIALBLUR);
				} else {
					radialbluOn = true;
					g->activateShader(GP_SHADER_RADIALBLUR);
				}
				break;
			case '=':
				blur += 0.1;
				shaderManager->setRadialBlurStrenght(blur);
				break;
			case '-':
				blur -= 0.1;
				shaderManager->setRadialBlurStrenght(blur);
				break;
			case 'q':	// Quit
				return 1;
			break;
				
		}
		
	} else {
		
		switch (event.key.keysym.sym) {
				
			case SDLK_LEFT:
				rotation = 0;
				break;
			case SDLK_RIGHT:
				rotation = 0;
				break;
				
		}
		
	}
	
	return 0;

}

// Objects options:
// MONKEY
// MONKEY_SUBSURF
// MONKEY_SMOTH
// CUBE_TRIANGLE
// TORUS_SUPERSMOOTH
// RND_CUBES
// MONKEY_PLAN_SCENE
// HOUSE
// PLANE
// BEATTLE

static void initGL ()
{
	shaderManager = g->shaderManager();
	
	obj[0] = g->newObject3D();
	
    std::string file = "MONKEY.obj";    
	obj[0]->loadFromFile(file);
	obj[0]->setVisible(true);
	
	obj[0]->setScaleXYZ(0.7, 0.7, 0.7);
	obj[0]->setRotationAngle(70);
	obj[0]->setRotationX(10);
	obj[0]->setRotationY(5);
	
}

static void loop ()
{
	obj[0]->addToRotationAngle(rotation);
}


int main(int argc, char *argv[])
{
	g = new Gepeto();
	
	g->setInputFunction(keyinput);
	g->setDisplayFunction(loop);
	
	initGL();
	
	g->start();
	
    return 0;
}
