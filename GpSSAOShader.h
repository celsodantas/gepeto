/*
 *  GpSSAOShader.h
 *  GEPETO
 *
 *  Created by Celso Dantas on 11/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef GPSSAOSHADER
#define GPSSAOSHADER

#include "GpBasePostShader.h"
#include "Texture.h"

class GpSSAOShader : public GpBasePostShader {
	
private:
	class SsaoPassOne : public GpBasePostShader {
		
	public:
		SsaoPassOne(): GpBasePostShader("v-ssao.vs","f-ssao.fs")
		{
			char rndMap[100] = "noise.tga";
			_randomTextureId = loadTexture(rndMap);
			
		}
		
		GLuint _randomTextureId;
		inline void setUniform(GLuint normalDepthMapId);
	};
	
	class SsaoPassTwo : public GpBasePostShader {
		
	public:
		SsaoPassTwo(): GpBasePostShader("v-ssao-post.vs","f-ssao-post.fs") { }
		inline void setUniform(GLuint shadowMapId, GLuint colorMapId);
	};

	SsaoPassOne _passOne;
	SsaoPassTwo _passTwo;
	
public:
	
	GpSSAOShader() : GpBasePostShader(NULL, NULL) { }
	
	inline void setUniformsPass1(GLuint normalDepthMapId);
	inline void setUniformsPass2(GLuint colorMapId);
	
	GLuint execute(GLuint normalDepthMapId, GLuint colorMapId);
	
	inline GLuint renderedTexture()
	{
		return _passTwo.renderedTexture();
	}
	
};

#endif