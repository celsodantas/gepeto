//
//  main.m
//  gepeto
//
//  Created by Celso Dantas on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include <iostream>
#include "gp/Gepeto.h"

#include "gp/loader/collada/ColladaLoader.h"

std::vector<geometry_asset> *assets;

int main(int argc, char **argv)
{    
    using namespace std;
    
    ColladaLoader loader;
    assets = loader.load("Z:/Desktop/cube.dae");
    
    Gepeto gepeto(argc, argv);
    gepeto.start(); 
    
    return 0;
}
