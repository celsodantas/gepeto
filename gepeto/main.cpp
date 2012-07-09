//
//  main.m
//  gepeto
//
//  Created by Celso Dantas on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "gp/Gepeto.h"

int main(int argc, char **argv)
{    
    using namespace std;
    
    Gepeto gepeto(argc, argv);
    gepeto.start(); 
    
    return 0;
}
