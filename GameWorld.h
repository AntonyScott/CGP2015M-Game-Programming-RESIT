#pragma once
//#define MAX_KEYS(256)
#ifndef Game_WorldFILE
#define Game_WorldFILE
#define MAX_KEYS (256)
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Timer.h"
#include "Square.h"
#include "GameContainerSquare.h"



class GameWorld {
public:
	
	Square globalSquare;
	GameContainerSquare aGameContainerSquare;
	GameWorld();
	~GameWorld();

	//called to initialize SDL along with window parameters
	void InitGameWorld(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	//THE GAME LOOP
	void Input();
	void Update();
	void Render();

	//Keyboard handler
	bool globalKeys[MAX_KEYS];

	//checks to see if game is running or not
	bool Running() { return isRunning; }

	//cleans memory allocation
	void CleanUp();

	Timer aTimer;
	Square aSquare;
	bool fullscreen = false;
	bool isRunning = false;
	const int DELTA_TIME = 30;
	SDL_Renderer* renderer;
	SDL_Window* window;
	//SDL_Rect rect;
};
#endif
