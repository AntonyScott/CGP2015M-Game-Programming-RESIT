//#define MAX_KEYS(256)
#ifndef Game_WorldFILE
#define Game_WorldFILE

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Timer.h"
#include "BallPaddleBrick.h"
#include "SimpleSprite.h"

#define MAX_KEYS (256)

class GameWorld {
public:
	//instances
	BallPaddleBrick aBallPaddleBrick;
	SimpleSprite* spaceBG;
	SimpleSprite* splashScreen;

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

	void SplashScreen();

	Timer aTimer;
	bool fullscreen = false;
	bool isRunning = false;
	const int DELTA_TIME = 60;
	SDL_Window* window;
};
#endif
