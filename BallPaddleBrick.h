#pragma once
#include "SDL.h"

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
};
