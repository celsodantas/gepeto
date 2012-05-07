/*
 *  GpDraw.c
 *  GEPETO
 *
 *  Created by Celso Dantas on 02/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GpDraw.h"
#include <math.h>

// TODO:: Escrever a importancia de utilizar 
//		  MACROS ao invés de definir função!

#define BUFFER_OFFSET(offset) ((GLvoid *) offset)

GpDraw::GpDraw(int w, int h)
{
	// Passando por parâmetro o tamanho da área a ser renderizada.
	// Por padrão, será a tela toda.
	_viewportSizeX = w;
	_viewportSizeY = h;
	
	// ####
	// Black
	_red = 0.0;
	_green = 0.0;
	_blue = 0.0;
	_alpha = 1.0;
	
	projMatrixConfig.nearClipDist = 1;
	projMatrixConfig.farClipDist = 10;
	projMatrixConfig.aspect = 1.77777;
	projMatrixConfig.fov = 50;
	
	_shaderManager = GpPostShaderManager::getInstance();
	
	initialize();
	
}


void GpDraw::initialize()
{	
	initViewport();
	
	glShadeModel(GL_SMOOTH);	
	
	/////// ANTIALIZING
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);			// Set Line Antialiasing
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LEQUAL); 
	
	glMatrixMode(GL_MODELVIEW);
	
	// Habilitando o teste de profundidade 
	glEnable(GL_DEPTH_TEST);
	
	// Habilitando o uso do Vertex Buffer Object
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);	// TO BE IMPLEMENTED (em interação futura)
	
	// Inicializando/Gerando FBO
	
	// TODO:: Refatorando codigo... tirando essas chamadas
	//_shaders.loadNormalAndDepthShader();
	//_shaders.loadSSAOShader();
	genFBO();
	
	/////////////////////////////
	
	GLfloat global_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	
	// Create light components
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat position[] = { -1.5f, 1.0f, 1.0f, 1.0f };
	
	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	/////////////////////////////
	

}	

// Global Objects
std::list<GpObject3D *>::iterator obj;

void GpDraw::draw() {

	glLoadIdentity();
	
	// TODO :: Terminar a implementação da camera.
	//gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	//gluLookAt(0, 0, 4, 0, 0, 0, 0, 1, 0);
	//polarView(4, 0, 5, 5);
	glTranslatef(0, 0, -4);
	
	if (GpGlobal::gpObjsToRender.size() > 0) {
		
		enableFBO();
		
		glDisable(GL_TEXTURE_2D);
		
		glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT);
			
			glClearColor(_red, _green, _blue, _alpha);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		
			glViewport(0, 0, 1024, 1024);       // set The Current Viewport to the fbo size
			
			GLenum attachs[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
			
			glDrawBuffers(2, attachs);
		
			for (obj = GpGlobal::gpObjsToRender.begin(); obj != GpGlobal::gpObjsToRender.end(); ++obj) 
			{
				drawElement(**obj);
			}
		
		glPopAttrib();
		
		disableFBO();
		
		// ####
		// Post Shaders
		
		// SSAO
//		_ssaoShader.execute(_texturesId[1], _texturesId[0]);		
//		lastRenderedTexture = _ssaoShader.renderedTexture();
//		
//		// Radial Blur
//		float blurStrenght = 5.1;
//		_radialBlurShader.execute(lastRenderedTexture, blurStrenght);
//		lastRenderedTexture = _radialBlurShader.renderedTexture();
		
		_lastRenderedTexture = _shaderManager->execute(_texturesId);
		
		
		setViewport();
		drawFullScreenSquare();
	}
}

void GpDraw::drawElement(GpObject3D &o)
{
	glPushMatrix();
	
		glScaled(o.getScaleX(),
				 o.getScaleY(),
				 o.getScaleZ());
		
		glRotated(o.getRotationAngle(), 
				  o.getRotationX(), 
				  o.getRotationY(),
				  o.getRotationZ());
		
		glTranslatef(o.getPositionX(), 
					 o.getPositionY(), 
					 o.getPositionZ());
		
		// Shader do objeto
		// TODO:: chamar o shader aqui!
		_normalDepthShader.activate();
		_normalDepthShader.setUniforms(10.0, 0.0);
		
		// Vertexes
		glBindBuffer(GL_ARRAY_BUFFER, o.getVertexes().getBufferId());
		glVertexPointer(3, GL_FLOAT, 24, 0);  
		// TODO:: Corrigir esse numero 24 - Colocar o sizeof(array)
		
		// Normals
		glNormalPointer(GL_FLOAT, 24, BUFFER_OFFSET(12));
		// TODO:: Corrigir esse numero 24 - Colocar o sizeof(array)
		
		// Indexes
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o.getIndexes().getBufferId());
		
		//glPolygonMode(GL_FRONT, GL_FILL);
		glDrawElements(GL_TRIANGLES, o.getIndexes().getCount(), GL_UNSIGNED_SHORT, 0);
		
		glUseProgram(0);
	
	glPopMatrix();
}

void GpDraw::initViewport() {
	
	setViewport();
	setPerspectiveView();

	cleanWindow();
}

void GpDraw::setViewport() 
{
	glViewport(0, 0, (GLdouble) _viewportSizeX, (GLdouble) _viewportSizeY); 
}

void GpDraw::setPerspectiveView() 
{
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	
	gluPerspective(projMatrixConfig.fov, 
				   projMatrixConfig.aspect, 
				   projMatrixConfig.nearClipDist, 
				   projMatrixConfig.farClipDist); 
	
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
}

void GpDraw::setOrthographicView() 
{
	glLoadIdentity(); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(-1, 1, -1, 1); 
	glMatrixMode(GL_MODELVIEW);
}

void GpDraw::cleanWindow()
{
	glClearColor(_red, _green, _blue, _alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

void GpDraw::setRgbCleanColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	
	_red = r;
	_green = g;
	_blue = b;
	_alpha = a;
	
}

void GpDraw::drawFullScreenSquare() {
	
	setOrthographicView();
	
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	
	glBindTexture(GL_TEXTURE_2D, _lastRenderedTexture);
	
	
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear Screen And Depth Buffer on the framebuffer to black
	
	glBegin(GL_QUADS);
		
		glColor3f(1, 1, 1);
		
		glTexCoord2f(0.0f, 0.0f); 	glVertex3f(-1, -1,  1);
		glTexCoord2f(1.0f, 0.0f); 	glVertex3f( 1, -1,  1);
		glTexCoord2f(1.0f, 1.0f); 	glVertex3f( 1,  1,  1);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1,  1,  1);
		
		
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	
	setPerspectiveView();
	
}

void GpDraw::genFBO() 
{
	glGenFramebuffers(1, &_fboId);												// create a new framebuffer
	
	if (_fboId == 0) printf("Falha em gerar o framebuffer.");
	
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, _fboId);								// switch to the new framebuffer
	
	////////////////////////////////
	// Inicializando Texturas que receberão a imagem renderizada
	
	glGenTextures(2, _texturesId);												// and a new texture used as a color buffer
	
	// initialize Color Texture (Color Buffer)
	glBindTexture(GL_TEXTURE_2D, _texturesId[0]);									// Bind the colorbuffer texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);				// make it linear filterd
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1024, 1024, 0,GL_RGBA, GL_INT, NULL);	// Create the texture data
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texturesId[0], 0); // attach it to the framebuffer
	
	// initialize Color Texture (Normal e Depth Buffer)
	glBindTexture(GL_TEXTURE_2D, _texturesId[1]);									// Bind the colorbuffer texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);				// make it linear filterd
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1024, 1024, 0,GL_RGBA, GL_INT, NULL);	// Create the texture data
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _texturesId[1], 0); // attach it to the framebuffer
	
	
	////////////////////////////////
	// initialize Renderbuffer
	glGenRenderbuffers(1, &_renderbufferId);											// And finaly a new depthbuffer
	
	glBindRenderbuffer(GL_RENDERBUFFER, _renderbufferId);								// bind the depth renderbuffer
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 1024, 1024);		// get the data space for it
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderbufferId); // bind it to the renderbuffer
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);	
}

void GpDraw::enableFBO()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, _fboId);
}

void GpDraw::disableFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}