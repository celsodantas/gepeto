/*
 *  Object3D.cpp
 *  SDL Project
 *
 *  Created by Celso Dantas on 01/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GpObject3D.h"
#include "system_assets/filesystem.h"

namespace GepetoObjects {

	GpObject3D::GpObject3D() {
		
		_positionX = 0;
		_positionY = 0;
		_positionZ = 0;
		
		_rotationX = 0;
		_rotationY = 0;
		_rotationZ = 0;
		
		_scaleX = 1;
		_scaleY = 1;
		_scaleZ = 1;
		
		_rotationAngle = 0;
		
		_visible = false;
		
	}
	
	GpObject3D::~GpObject3D() {
		
		free(_vertexes.getArray());
		free(_indexes.getArray());
		free(_normals.getArray());
		
	}
	
	void GpObject3D::setPositionXYZ(GLfloat x, GLfloat y, GLfloat z) {
		_positionX = x;
		_positionY = y;
		_positionZ = z;
	}
	
	void GpObject3D::setRotationXYZ(GLfloat x, GLfloat y, GLfloat z) {
		_rotationX = x;
		_rotationY = y;
		_rotationZ = z;
	}
	
	void GpObject3D::setScaleXYZ(GLfloat x, GLfloat y, GLfloat z) {
		_scaleX = x;
		_scaleY = y;
		_scaleZ = z;
	}
	
	void GpObject3D::loadFromFile(std::string &file) {
		
		_file = Filesystem::resourcesPath() + file;
		
		GpObjectLoader loader;
		GLint vertexMemSize;
		//GLint normalMemSize;
		GLint indexMemSize;
		GpObjectLoader::VERTEX_ARRAY *verts;
		
		
		loader.setFile(_file);
		
		//printf("Carregando arquivo %s... \n", _file); //TODO::DEBUG
		loader.loadElement(&verts, 
						   &vertexMemSize, 
						   _indexes.getArray(), 
						   &indexMemSize);
		
		vs = verts;
		
		// Dentro do loadElement ele diz o tamanho alocado na memoria.
		// Passando esses valores para os objetos da classe.
		_vertexes.setMemSize(vertexMemSize);
		_indexes.setMemSize(indexMemSize);
		
		// Setando a quantidade de elementes de cada array
		_vertexes.setCount( vertexMemSize / (sizeof(GLfloat) ) );
		_indexes.setCount( indexMemSize / (sizeof(GLushort) ) );
		
	}

	
	void GpObject3D::setVisible(bool v) {
		
		//printf("Criando VBO do objeto: %s...", _file); //TODO::DEBUG
		
		GLuint bufPointer[2];
		glGenBuffers(2, bufPointer);
		
		// Colocando os atributos do objeto na memoria da placa de video.
		
		// VERTICES
		glBindBuffer(GL_ARRAY_BUFFER, bufPointer[0]);
		glBufferData(GL_ARRAY_BUFFER, *(_vertexes.getMemSize()), 
					 vs, GL_STATIC_DRAW);
		
		//glBufferData(GL_ARRAY_BUFFER, 16, vertexes, GL_STATIC_DRAW);
		
		_vertexes.setBufferId(bufPointer[0]);
		
		// INDICES
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufPointer[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, *(_indexes.getMemSize()), 
					 *(_indexes.getArray()), GL_STATIC_DRAW);

		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12, indexes, GL_STATIC_DRAW);
		_indexes.setBufferId(bufPointer[1]);
		
//		// NORMAL
//		glBindBuffer(GL_ARRAY_BUFFER, bufPointer[2]);
//		glBufferData(GL_ARRAY_BUFFER, *(_normals.getMemSize()), 
//					 *(_normals.getArray()), GL_STATIC_DRAW);
//		_normals.setBufferId(bufPointer[2]);
		
		//printf(" done!\n", _file); //TODO::DEBUG
		
		
	}

}