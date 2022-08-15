// CGP2015M Game Programming RESIT - Antony Scott.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"

//user created header files:
#include "GameWorld.h"

using namespace std;

GameWorld* gameWorld = nullptr;

int main(int argc, char *argv[] )
{
	gameWorld = new GameWorld();

	gameWorld->InitGameWorld("Antony Scott, CGP2015M Game Programming, Student ID: 25295522, Title: Brick Break", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    gameWorld->SplashScreen();
    SDL_Delay(3000);

    while (gameWorld->Running())
    {
        //looks for keyboard/mouse events
        gameWorld->Input();
        
        //Updates game state and variables
        gameWorld->Update();
        //draws game on screen
        gameWorld->Render();
    }

    //SDL_Delay(2000);

    gameWorld->CleanUp();
    SDL_Quit();
    return 0;
}
