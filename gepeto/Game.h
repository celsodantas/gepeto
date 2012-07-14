//
//  Game.h
//  gepeto
//
//  Created by Celso Dantas on 08/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_Game_h
#define gepeto_Game_h

#include <iostream>
#include "gp/Gepeto.h" 

#define GAMECLASS Game

///////////////
//
// TODO: Move this to an external project
//
///////////////

class Game
{
public:
    Game(Gepeto *gepeto);

    void setup();    
    void frame(double delta);
    
private:
    Gepeto *_gepeto;
};



#endif
