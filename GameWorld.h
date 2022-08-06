#pragma once
//#define MAX_KEYS(256)
#ifndef Game_WorldFILE
#define Game_WorldFILE

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Timer.h"
#include "Square.h"
#include "GameContainerSquare.h"
#include "BallPaddleBrick.h"

#define MAX_KEYS (256)

//screen sizes
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

//text sizes
#define FONT_SIZE 32







class GameWorld {
public:
	
	Square globalSquare;
	GameContainerSquare aGameContainerSquare;
	BallPaddleBrick aBallPaddleBrick;
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
	int points = 0;

	//SDL_Rect paddle, ball, lives, brick, trail;
};
#endif
