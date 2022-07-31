#pragma once
#include "SDL.h"
#include "Timer.h"
#include <iostream>

class GameWorld {
public:
	Timer aTimer;
	GameWorld();
	~GameWorld();

	//called to initialize SDL along with window parameters
	void InitGameWorld(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	//THE GAME LOOP
	void Input();
	void Update();
	void Render();

	//Keyboard handler
	bool globalKeys[256];

	//checks to see if game is running or not
	bool Running() { return isRunning; }

	//cleans memory allocation
	void CleanUp();

private:
	bool fullscreen = false;
	bool isRunning = false;
	const int DELTA_TIME = 20;
	SDL_Renderer* renderer;
	SDL_Window* window;

};
