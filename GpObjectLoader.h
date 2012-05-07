/*
 *  objExtensionExtractor.h
 *  openGLaTry
 *
 *  Created by Celso Dantas on 15/08/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <OpenGL/OpenGL.h>


class GpObjectLoader {
	
private:
	std::ifstream *infile;
	
	// STRUCT Temporaria, será usada apenas para a leitura do arquivo.
	// depois disso, servirar de auxiliar na criação do array unidimencional.
	typedef struct _VECTOR3 {
		GLfloat x, y, z;
		long index;
		long *count;
		_VECTOR3 *prev, *next;
		
	} VECTOR3;
	
	// STRUCT Temporaria
	typedef struct _INDEX {
		long vertexIndex, textureIndex, normalIndex;
		long *count;
		_INDEX *prev, *next;
	} INDEX;

public:
	
	typedef struct _VERTEX {
		GLfloat x, y, z;
	} VERTEX;
	
	typedef struct _VERTEX_ARRAY {
		VERTEX position;
		VERTEX normal;
	} VERTEX_ARRAY;	
	
private:
	
	// STRUCT AUXILIAR
	typedef struct _VERTEX_LIST_AUX {
		VERTEX position;
		VERTEX normal;
		
		bool empty;
		long index;
		
		long normalIndex;
		long *count;
		
		_VERTEX_LIST_AUX *prev, *next;
	} VERTEX_LIST_AUX;
	
	
	
public:	
	
	
	GpObjectLoader() {	};
	~GpObjectLoader() { };
	
	void setFile(std::string filename);
	void loadElement(VERTEX_ARRAY **vertexVector,
					 int *pSize,
					 GLushort **indexVector,
					 int *iSize);

private:
	GLfloat getFloatValueBySpace(std::string line, int pos);
	GLint getFloatValueByDoubleSlash(std::string line, int pos);
	
	
	_VERTEX_ARRAY *buildFriendlyArray(VECTOR3 *listPosition,
							VECTOR3 *listNormal,
							INDEX *listIndex,
							long *vertexCount);
	_VERTEX_ARRAY *allocateVertexInMemory(VERTEX_LIST_AUX *vertex);
	GLushort *allocateIndexInMemory(INDEX *index);
	
	void linkedListOfElements(VECTOR3 **listPosition,
							  VECTOR3 **listNormal,
							  INDEX **listIndex);
	template <class T>
	void fillArrayUsinglinkedListOfElements(T **positionVector, VECTOR3 *list, int vectorSize, short correction);
	
};

#endif 



