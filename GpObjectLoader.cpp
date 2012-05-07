/*
 *  objExtensionExtractor.cpp
 *  openGLaTry
 *
 *  Created by Celso Dantas on 15/08/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GpObjectLoader.h"

// Setting internal variable to filename
// It will be reused in most of others methods, so, for performance,
// we will store it inside the class.
void GpObjectLoader::setFile(std::string filename) 
{	
    std::cout << "Lendo arquivo: " << filename << std::endl;
	infile = new std::ifstream(&filename[0], std::ios_base::in);	
}

void GpObjectLoader::loadElement(VERTEX_ARRAY **vertexVector,
								 int *pSize,
								 GLushort **indexVector,
								 int *iSize) {
	
	VECTOR3 *firstVertex, *firstNormal;	// Ponteiro pro primeiro item da lista. 
	INDEX *firstIndex;					// Ponteiro pro primeiro item da lista.
	
	printf("Criando lista de elementos..."); //TODO::DEBUG
	// Criando a lista encadeada de elementos
	linkedListOfElements(&firstVertex,
						 &firstNormal,
						 &firstIndex);
	printf(" done!\n"); //TODO::DEBUG
	
	long vertexCount = 0;
	
	printf("Construindo array de vertices/normais..."); //TODO::DEBUG
	*vertexVector = buildFriendlyArray(firstVertex, firstNormal, firstIndex, &vertexCount);
	*pSize = (vertexCount * 3) * sizeof(GLfloat) * 2;
	printf(" done!\n"); //TODO::DEBUG
	
	printf("Construindo array de indices..."); //TODO::DEBUG
	*indexVector = allocateIndexInMemory(firstIndex);
	*iSize = (*(firstIndex->count) * sizeof(GLushort));
	printf(" done!\n"); //TODO::DEBUG
	
	printf("Arquivo carregado!\n\n"); //TODO::DEBUG
}

////////////////////
// PRIVATE METHODS

template <class T>
void GpObjectLoader::fillArrayUsinglinkedListOfElements(T **pVector, 
														VECTOR3 *list, 
														int vectorSize,
														short correction) {

	*pVector = (T *) malloc( (sizeof(T) * (vectorSize * 3)) );
	//*pVector = (T *) calloc((vectorSize * 3), (sizeof(T)));

	
	// Loopando pela lista encadeada
	int i;
	for ( i = 0; i < (vectorSize * 3); i += 3) {
		(*pVector)[i+0] = list->x - correction;
		(*pVector)[i+1] = list->y - correction;
		(*pVector)[i+2] = list->z - correction;
		
		list = list->next;	
	}
	
}

 
GpObjectLoader::_VERTEX_ARRAY *
GpObjectLoader::buildFriendlyArray(VECTOR3 *listPosition,
								   VECTOR3 *listNormal,
								   INDEX *listIndex,
								   long *vertexCount) {
	
	#define INIT_VERTEX(v)	v->empty = true; \
							v->index = 0; \
							v->normalIndex = -1;
	
	#define	NEW_VERTEX(v)	v->next = (VERTEX_LIST_AUX *) malloc( sizeof(VERTEX_LIST_AUX) ); \
							(v->next)->prev = v; \
							v = v->next; \
							\
							INIT_VERTEX(v); \
							\
							v->next = NULL; \
							v->index = (v->prev)->index + 1; \
							v->count = (v->prev)->count; \
							*(v->count) += 1;
	
	#define ASSIGN_VALUES_TO_VERTEX(v)	v->position.x	= listPosition->x; \
										v->position.y	= listPosition->y; \
										v->position.z	= listPosition->z; \
										\
										v->normal.x	= listNormal->x;\
										v->normal.y	= listNormal->y;\
										v->normal.z	= listNormal->z;\
										\
										v->normalIndex = listNormal->index;\
										\
										v->empty		= false;
	
	
	
	
	// Helper Array
	VERTEX_LIST_AUX *vertex = (VERTEX_LIST_AUX *) malloc( sizeof(VERTEX_LIST_AUX) );
	vertex->count = (long *) malloc( sizeof(long) );
	
	// Inicializando
	INIT_VERTEX(vertex);
	vertex->prev = NULL; 
	vertex->next = NULL;
	*(vertex->count) = 1;
	
	// Criando a lista com pelo menos a quantidade de listPosition - 1 (o primeiro ja foi criado)
	for (int i = 0; i < *(listPosition->count) - 1; i++) {
		NEW_VERTEX(vertex);
	}
	
	
	// P/ cada elemento do INDEX eu insiro na lista de vertexes
	do {
		
		while (listIndex->vertexIndex != vertex->index) {	// Não é igual
			
			if (listIndex->vertexIndex > vertex->index) {	// Subindo!
				vertex = vertex->next;
			} else {										// Descendo!
				vertex = vertex->prev;
			}
			
		}
			
		while (listIndex->vertexIndex != listPosition->index) {
			
			if (listIndex->vertexIndex > listPosition->index) {
				listPosition = listPosition->next; 
			} else {
				listPosition = listPosition->prev;
			}
			
		}
				
		while (listIndex->normalIndex != listNormal->index) {
			
			if (listIndex->normalIndex > listNormal->index) {
				listNormal = listNormal->next;
			} else {
				listNormal = listNormal->prev;
			}	
		}
		
		///////
		// Tentando inserir no lugar correto
		
		if (vertex->empty) {
						
			ASSIGN_VALUES_TO_VERTEX(vertex);
			
			
		} else {
				
			// Assegurando que não é indice repetido
			if (vertex->normalIndex != listNormal->index) {	
			
				// Já que já esta ocupado! 
				// criando um novo vertex

				while (vertex->next != NULL) {	// Indo até o ultimo
					vertex = vertex->next;
				}
				
				NEW_VERTEX(vertex);
				
				ASSIGN_VALUES_TO_VERTEX(vertex);
				
				listIndex->vertexIndex = vertex->index;
				
			}
			
				
		}


		listIndex = listIndex->next;
		
	} while (listIndex != NULL);
	
	
	// Removendo os defines da memoria
	#undef INIT_VERTEX(v)
	#undef NEW_VERTEX(v)
	#undef ASSIGN_VALUES_TO_VERTEX(v)
	
	*vertexCount = *(vertex->count);
	return allocateVertexInMemory(vertex);
	
}

GpObjectLoader::_VERTEX_ARRAY * 
GpObjectLoader::allocateVertexInMemory(VERTEX_LIST_AUX *vertex) {
	
	// Indo até o inicio do *vertex
	while (vertex->prev != NULL) {
		vertex = vertex->prev;
	}
	
//	// #######################
//	//// printf position
//	while (vertex->next != NULL) {
//		printf("v %f %f %f\n", vertex->position.x, vertex->position.y, vertex->position.z);
//		vertex = vertex->next;
//	}
//	// Imprimindo o ultimo
//	printf("v %f %f %f\n", vertex->position.x, vertex->position.y, vertex->position.z);
//	//////////////////////////
//	
//	while (vertex->prev != NULL) {
//		vertex = vertex->prev;
//	}
//	//// desfazendo
//	// #######################
//	// #######################
//	//// printf normal
//	while (vertex->next != NULL) {
//		printf("vn %f %f %f\n", vertex->normal.x, vertex->normal.y, vertex->normal.z);
//		vertex = vertex->next;
//	}
//	// Imprimindo o ultimo
//	printf("vn %f %f %f\n", vertex->normal.x, vertex->normal.y, vertex->normal.z);
//	//////////////////////////
//	
//	while (vertex->prev != NULL) {
//		vertex = vertex->prev;
//	}
//	//// desfazendo
//	// #######################
	
	// Allocando toda a estrutura dos vertices de Position, Normal e Texture
	VERTEX_ARRAY *friendlyArray;
	
	friendlyArray = (VERTEX_ARRAY *) malloc( sizeof(VERTEX_ARRAY) * *(vertex->count) );
		
	for (int i = 0; vertex != NULL; i++) {
		
		friendlyArray[i].position.x = vertex->position.x;
		friendlyArray[i].position.y = vertex->position.y;
		friendlyArray[i].position.z = vertex->position.z;
		
		friendlyArray[i].normal.x = vertex->normal.x;
		friendlyArray[i].normal.y = vertex->normal.y;
		friendlyArray[i].normal.z = vertex->normal.z;
		
		vertex = vertex->next;
		
	}
	
	return friendlyArray;
	
}

GLushort * 
GpObjectLoader::allocateIndexInMemory(INDEX *vertex) {
	
	// Indo até o inicio do *vertex
	while (vertex->prev != NULL) {
		vertex = vertex->prev;
	}
	
	// Allocando toda a estrutura dos INDICES
	GLushort *indexArray = (GLushort *) malloc( sizeof(GLushort) * *(vertex->count) );
	
	for (int i = 0; vertex != NULL; i++) {
		indexArray[i] = vertex->vertexIndex;
		vertex = vertex->next;
	}
	
	return indexArray;
	
}


void GpObjectLoader::linkedListOfElements(VECTOR3 **listPosition,
										  VECTOR3 **listNormal,
										  INDEX **listIndex) {
	
	//##################################
	const std::string VECTOR_POSITION_SIGN	= "v ";
	const std::string VECTOR_NORMAL_SIGN	= "vn";
	const std::string VECTOR_INDEX_SIGN		= "f ";
	
	VECTOR3 *vPosition = NULL, *vNormal = NULL;
	INDEX *vIndex = NULL;
	
	char const *lineChar;
	std::string line;
	short int firstPosition = 1, firstNormal = 1, firstIndex = 1;

	int v1, n1, v2, n2, v3, n3;
	//##################################
	
	
	
	
	// Looping each line
	while (getline(*infile, line, '\n'))
	{
		
		// Vertex position
		if (line.find(VECTOR_POSITION_SIGN) == 0) { 
			
			if (firstPosition) {
				vPosition = (VECTOR3 *) malloc( sizeof(VECTOR3) );
				vPosition->count = (long *) malloc(sizeof(long));
				*(vPosition->count) = 0;
				*listPosition = vPosition;	// Apontando pro primeiro da lista!
				
				vPosition->prev = NULL;
				vPosition->next = NULL;
				
				firstPosition = 0;
			} else {				
				vPosition->next = (VECTOR3 *) malloc( sizeof(VECTOR3) );
				(vPosition->next)->count = vPosition->count;
				(vPosition->next)->prev = vPosition;
				vPosition = vPosition->next;
			}

			// Passando pra lista encadeada
			vPosition->x = getFloatValueBySpace(line, 1);
			vPosition->y = getFloatValueBySpace(line, 2);
			vPosition->z = getFloatValueBySpace(line, 3);
			vPosition->index = *(vPosition->count);
			vPosition->next = NULL;
			
			*(vPosition->count) += 1;
			
		} else 
			
		// Vertex Normal
		if (line.find(VECTOR_NORMAL_SIGN) == 0) { 
			
			if (firstNormal) {
				vNormal = (VECTOR3 *) malloc( sizeof(VECTOR3) );
				vNormal->count = (long *) malloc(sizeof(long));
				*(vNormal->count) = 0;
				*listNormal = vNormal;	// Apontando pro primeiro da lista!
				
				vNormal->prev = NULL;
				vNormal->next = NULL;
				
				firstNormal = 0;
			} else {				
				vNormal->next = (VECTOR3 *) malloc( sizeof(VECTOR3) );
				(vNormal->next)->count = vNormal->count;
				(vNormal->next)->prev = vNormal;
				vNormal = vNormal->next;
			}
			
			// Passando pra lista encadeada
			vNormal->x = getFloatValueBySpace(line, 1);
			vNormal->y = getFloatValueBySpace(line, 2);
			vNormal->z = getFloatValueBySpace(line, 3);
			vNormal->index = *(vNormal->count);
			vNormal->next = NULL;
			
			*(vNormal->count) += 1;
			
		} else
		
		// Vertex Index
		if (line.find(VECTOR_INDEX_SIGN) == 0) { 
			
			if (firstIndex) {
				vIndex = (INDEX *) malloc( sizeof(INDEX) );
				vIndex->count = (long *) malloc(sizeof(long));
				*(vIndex->count) = 0;
				*listIndex = vIndex;	// Apontando pro primeiro da lista!
				
				vIndex->next = NULL;
				vIndex->prev = NULL;
				
				firstIndex = 0;
			} else {				
				vIndex->next = (INDEX *) malloc( sizeof(INDEX) );
				(vIndex->next)->count = vIndex->count;
				(vIndex->next)->prev = vIndex;
				vIndex = vIndex->next;
			}
			
			lineChar = line.c_str();
			
			// Lendo do arquivo
			sscanf(lineChar, "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
			
			// ### NUMERO 1
			// Passando pra lista encadeada
			vIndex->vertexIndex = v1 - 1;
			vIndex->normalIndex = n1 - 1;
			vIndex->next = NULL;
			*(vIndex->count) += 1;
			
			// Passando pra outro elemento
			vIndex->next = (INDEX *) malloc( sizeof(INDEX) );
			(vIndex->next)->count = vIndex->count;
			(vIndex->next)->prev = vIndex;
			vIndex = vIndex->next;
			
			// ### NUMERO 2
			// Passando pra lista encadeada
			vIndex->vertexIndex = v2 - 1;
			vIndex->normalIndex = n2 - 1;
			vIndex->next = NULL;
			*(vIndex->count) += 1;
			
			// Passando pra outro elemento
			vIndex->next = (INDEX *) malloc( sizeof(INDEX) );
			(vIndex->next)->count = vIndex->count;
			(vIndex->next)->prev = vIndex;
			vIndex = vIndex->next;
			
			// ### NUMERO 3
			// Passando pra lista encadeada
			vIndex->vertexIndex = v3 - 1;
			vIndex->normalIndex = n3 - 1;
			vIndex->next = NULL;
			*(vIndex->count) += 1;
			
			
			
		}	
	}
	
}

GLint GpObjectLoader::getFloatValueByDoubleSlash(std::string line, int pos) {
	
	int whiteSpaceFound = 0;
	
	// Looping until find number of 'white space' passed int 'pos' param
	// pos = 1, first 'white space'
	// pos = 2, second 'white space'
	int index = 0;
	while (whiteSpaceFound != pos) {
		
		// Looping until find 'white space' character
		while (line[index] != ' ') {
			index++;
		}
		
		// 'White space' found
		whiteSpaceFound++;
		
		// Moving index to next char
		index++;
	}
	
	std::string value;
	
	// Diferent from 'white space' and 'end of line'
	while (line[index] != '/') {
		value += line[index];
		index++;
	}
	
	// Convertendo e retornando o valor;
	return atof(&value[0]);
	
}

// Accessing file...
// Kinda lexical/sintatic algorithm
GLfloat GpObjectLoader::getFloatValueBySpace(std::string line, int pos) {
	
	int whiteSpaceFound = 0;
	
	// Looping until find number of 'white space' passed int 'pos' param
	// pos = 1, first 'white space'
	// pos = 2, second 'white space'
	int index = 0;
	while (whiteSpaceFound != pos) {
		
		// Looping until find 'white space' character
		while (line[index] != ' ') {
			index++;
		}
		
		// 'White space' found
		whiteSpaceFound++;
		
		// Moving index to next char
		index++;
	}
	
	std::string value;
	
	// Diferent from 'white space' and 'end of line'
	while (line[index] != '\0' && line[index] != ' ' && line[index] != '\n') {
		value += line[index];
		index++;
	}
	
	// Convertendo e retornando o valor;
	return atof(&value[0]);
	
}
