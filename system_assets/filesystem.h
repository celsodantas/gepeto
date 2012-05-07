//
//  filesystem.h
//  GEPETO
//
//  Created by Celso Dantas on 5/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GP_FILESYSTEM
#define GP_FILESYSTEM

#include <iostream>

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

class Filesystem {
    
public:
    static std::string resourcesPath () {
        
        char path[PATH_MAX];
        
        // ----------------------------------------------------------------------------
        // This makes relative paths work in C++ in Xcode by changing directory to the 
        // Resources folder inside the .app bundle
        #ifdef __APPLE__    
            CFBundleRef mainBundle = CFBundleGetMainBundle();
            CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    
            if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
            {
                // error!
            }
            CFRelease(resourcesURL);
            
            chdir(path);
        #endif
        
        std::string stringPath(path);
        
        return stringPath + "/";
    }
    
};

#endif