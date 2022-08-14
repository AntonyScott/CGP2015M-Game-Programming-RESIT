#include "SDL.h"
#include "SDL_ttf.h"
//#include "GameWorld.h"
#include <list>
#include <string>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

//ball and paddle
#define BALL_SPEED 10
#define PADDLE_SPEED 10
#define BALL_SIZE 15
#define TRAIL_SIZE 6

//bricks
#define COLUMN 13
#define ROW 8
#define SPACING 15

//pi
#define PI 3.14159265358979323846

//text sizes
#define FONT_SIZE 32

class BallPaddleBrick 
{
public:
	int ballSpeed = BALL_SPEED;
	int paddleSpeed = PADDLE_SPEED;
	int ballSize = BALL_SIZE;
	int trailSize = TRAIL_SIZE;

	int columns = COLUMN;
	int rows = ROW;
	int spaces = SPACING;

	int level = 1;
	SDL_Rect paddle, ball, lives, brick, trail;

	int points = 0;

	float velocityX = 0;
	float velocityY = 0;
	int lifeCount = 3;

	int bricks[ROW * COLUMN];

	std::list<float> trailCacheX;
	std::list<float> trailCacheY;

	TTF_Font* font;
	SDL_Color colour, brickColour;

	SDL_Renderer* aRenderer;

	void InitVariables();
	void ResetLevel(bool resetGame);
	void setBrickPosition(int i);
	void WriteFont(std::string text, int x, int y);
	void UpdateBallAndPaddle();
	void RenderBallPaddleBrick();
};
