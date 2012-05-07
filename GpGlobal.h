/*
 *  GpGlobal.h
 *  GEPETO
 *
 *  Created by Celso Dantas on 03/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __GPGLOBAL_H__
#define __GPGLOBAL_H__

#include "GpObject3D.h"
#include <list>

// ## 
// Enums
typedef unsigned int GPenum;


// ##
// Global objects
namespace GpGlobal {
	
	using namespace GepetoObjects;
	
	extern std::list<GpObject3D *> gpObjsToRender;	

}

#endif 