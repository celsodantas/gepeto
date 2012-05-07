/*
 *  Object3D.h
 *  SDL Project
 *
 *  Created by Celso Dantas on 01/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GPOBJECT3D_H
#define GPOBJECT3D_H

#include <OpenGL/OpenGL.h>
#include <iostream>
#include "GpObjectLoader.h"

// GpObject3D define um objeto 3D em cena.
// É nele que fica as informações básicas de todo objeto 3D
// do motor.

// Caso seja necessário criar outros objetos 3D mais específicos,
// herde desse objeto.


// TODO REMOVER DEPOIS DO TESTE
extern float vertexes[10];
extern float normals[10];
extern GLuint indexes[12];

namespace GepetoObjects {

	class GpObject3D {
		
	private:
		
		//////////////////
		// Inner class Array
		template <class T>
		class GpArray {
			
		public:
			void setArray(T **a)		{ array = *a;		}
			T** getArray()				{ return &array;	}
			
			void setMemSize(GLint c)	{ size = c;			}
			GLint* getMemSize()			{ return &size;		}
			
			GLint getCount()			{ return count;		}
			void setCount(GLint c)		{ count = c;		}
			
			void setBufferId(GLuint id) { bufferId = id;	}
			GLuint getBufferId()		{ return bufferId;	}
			
		private:
			T *array;
			GLint size;
			GLint count;
			GLuint bufferId;
		};
		// Fim Inner class
		///////////////////
		
		
		GpObjectLoader::VERTEX_ARRAY *vs;
		

		
		
	public:
		
		GpObject3D();
		~GpObject3D();
		
		void setVisible(bool v);
		void loadFromFile(std::string &file);
		
		void setVertexes(GpArray<GLfloat> arrayf)	{ _vertexes = arrayf;	}
		GpArray<GLfloat>getVertexes()				{ return _vertexes;		}
		
		void setNormals(GpArray<GLfloat> arrayf)	{ _normals = arrayf;	}
		GpArray<GLfloat> getNormals()				{ return _normals;		}
		
		void setIndexes(GpArray<GLushort> arrayf)	{ _indexes = arrayf;	}
		GpArray<GLushort> getIndexes()				{ return _indexes;		}
		
		// Position
		void setPositionX(GLfloat x)		{ _positionX = x;		}
		void addToPositionX(GLfloat xplus)	{ _positionX += xplus;	}
		GLfloat getPositionX()				{ return _positionX;	}
		
		void setPositionY(GLfloat y)		{ _positionY = y;		}
		void addToPositionY(GLfloat yplus)	{ _positionY += yplus;  }
		GLfloat getPositionY()				{ return _positionY;	}
		
		void setPositionZ(GLfloat z)		{ _positionZ = z;		}
		void addToPositionZ(GLfloat zplus)	{ _positionZ += zplus;  }
		GLfloat getPositionZ()				{ return _positionZ;	}
		
		void setPositionXYZ(GLfloat x, GLfloat y, GLfloat z);
		
		// Rotation
		void setRotationX(GLfloat x)		{ _rotationX = x;		}
		void addToRotationX(GLfloat xplus)	{ _rotationX += xplus;	}
		GLfloat getRotationX()				{ return _rotationX;	}
		
		void setRotationY(GLfloat y)		{ _rotationY = y;		}
		void addToRotationY(GLfloat yplus)	{ _rotationY += yplus;	}
		GLfloat getRotationY()				{ return _rotationY;	}
		
		void setRotationZ(GLfloat z)		{ _rotationZ = z;		}
		void addToRotationZ(GLfloat zplus)	{ _rotationZ += zplus;	}
		GLfloat getRotationZ()				{ return _rotationZ;	}
		
		void setRotationAngle(GLfloat angle)	{ _rotationAngle = angle;	}
		GLfloat getRotationAngle()				{ return _rotationAngle;	}	
		void addToRotationAngle(GLfloat angle)	{ _rotationAngle += angle;	}
		
		void setRotationXYZ(GLfloat x, GLfloat y, GLfloat z);
		
		// Scale
		void setScaleX(GLfloat x)			{ _scaleX = x;			}
		GLfloat getScaleX()					{ return _scaleX;		}
		void setScaleY(GLfloat y)			{ _scaleY = y;			}
		GLfloat getScaleY()					{ return _scaleY;		}
		void setScaleZ(GLfloat z)			{ _scaleZ = z;			}
		GLfloat getScaleZ()					{ return _scaleZ;		}
		
		void setScaleXYZ(GLfloat x, GLfloat y, GLfloat z);
		
	private:
		
		bool			_visible;
		std::string		_file;
		
		GpArray<GLfloat>	_vertexes,
							_normals;
		GpArray<GLushort>	_indexes;
		
		// Vetores transformação do elemento
		GLfloat		_positionX,
					_positionY,
					_positionZ,
					_rotationX,
					_rotationY,
					_rotationZ,
					_rotationAngle,
					_scaleX,
					_scaleY,
					_scaleZ;
		
	};
	
}

#endif
