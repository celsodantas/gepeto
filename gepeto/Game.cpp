//
//  File.cpp
//  gepeto
//
//  Created by Celso Dantas on 08/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Game.h"

//Gepeto* Game::gepeto;

Game::Game(Gepeto *g)
{
    _gepeto = g;
}

void Game::setup()
{
    _gepeto->camera().resize();
    
    _gepeto->camera().setPosition(-1.0f, 2.0f, -7.0f);
    _gepeto->camera().lookAt(0.0f, 0.0f, 0.0f);
}

void Game::frame(double delta)
{
    _gepeto->camera().rotate(delta);
    _gepeto->camera().update();
}