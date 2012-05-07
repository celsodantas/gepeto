/*
 *  GpShaderManager.h
 *  GEPETO
 *
 *	Essa classe tem como objetivo servir de gerenciador e centralizador
 *	do controle dos Post Shaders.
 *
 *  Created by Celso Dantas on 12/4/10.
 *
 */

#ifndef __GPPOSTSHADERMANAGER__
#define __GPPOSTSHADERMANAGER__

#include "GpGlobal.h"
#include "GpSSAOShader.h"
#include "GpRadialBlurShader.h"

#define GP_SHADER_SSAO			1
#define GP_SHADER_RADIALBLUR	2

// ##
// Singleton Class

class GpPostShaderManager {
	
private:
	GpPostShaderManager() 
	{
		_radialStrength = 1;
	}
	static GpPostShaderManager *_singleton;
	
	// ####
	
	GpSSAOShader		_ssaoShader;
	GpRadialBlurShader	_radialBlurShader;
	GLfloat _radialStrength;
		
	inline GLuint executeSSAO(GLuint _renderedTextures[])
	{
		return _ssaoShader.execute(_renderedTextures[1], _renderedTextures[0]);
	}
	
	inline GLuint executeRadialBlur(GLuint _renderedTexture, GLfloat radialStrength)
	{
		return _radialBlurShader.execute(_renderedTexture, radialStrength);
	}
	
public:
	
	static GpPostShaderManager* getInstance()
	{
		if (_singleton == NULL) {
			_singleton = new GpPostShaderManager();
		}
		
		return _singleton;
	}
	
	inline void activateShader(GLenum shadersIds)
	{
		if (1 & shadersIds) {
			_ssaoShader.turnOn();
		}
		
		if (2 & shadersIds) {
			_radialBlurShader.turnOn();
		}
	}
	
	inline void deactivateShader(GLenum shadersIds)
	{
		if (1 & shadersIds) {
			_ssaoShader.turnOff();
		}
		
		if (2 & shadersIds) {
			_radialBlurShader.turnOff();
		}
	}
	
	inline void setRadialBlurStrenght(GLfloat strenght) 
	{
		_radialStrength = strenght;
	}
	
	inline GLuint execute(GLuint _renderedTextures[]) 
	{	
		// ##
		// _renderedTextures[0]  -> Color rendered texture
		// _renderedTextures[1]  -> Normal+Depth rendered texture
		
		GLuint imageId = _renderedTextures[0];
		
		if(_ssaoShader.on())
		{
			imageId = executeSSAO(_renderedTextures);
		}
		
		if (_radialBlurShader.on()) 
		{
			imageId = executeRadialBlur(imageId, _radialStrength);
		}
	
		return imageId;
	}
	
};

#endif