#include "BallPaddleBrick.h"

BallPaddleBrick::BallPaddleBrick()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "BallPaddleBrick constructed at (%p)", this);
}

//initalises brick variables and resets level, will be called in GameWorld Init function
void BallPaddleBrick::ResetLevel(bool reset) 
{
	if (reset) 
	{
		level = 1;
		ballSpeed = BALL_SPEED;
	}
	else 
	{
		level++;
		ballSpeed += 2;
	}

	for (int i = 0; i < columns * rows; i++) 
	{
		bricks[i] = level;
	}
	
	points = 0;
	lifeCount = 3;
	paddle.x = (SCREEN_WIDTH / 2) - (paddle.w / 2);
	ball1->y = paddle.y - (paddle.h * 4);
	velocityY = ballSpeed / 2;
	velocityX = 0;
	ball1->x = SCREEN_WIDTH / 2 - (ballSize / 2);
}

void BallPaddleBrick::InitVariables() 
{
	ball1 = new SimpleSprite(0, 0, 32, 32);
	ball1->load(aRenderer, "Content/Ball.png", false);
	colour.r = colour.g = colour.b = 255;
	brickColour.r = 30; brickColour.g = brickColour.b = 100;
	paddle.h = 22; 
	paddle.w = SCREEN_HEIGHT / 4;
	paddle.h = 12;
	ball1->w = ball1->h;
	ball1->h = ballSize;
	trail.w = trail.h = ballSize;
	paddle.y = SCREEN_HEIGHT - paddle.h - 32;

	brick.w = (SCREEN_WIDTH - (SPACING * columns)) / columns;
	brick.h = 22;

	ResetLevel(true);
}

//sets postion of bricks on screen
void BallPaddleBrick::setBrickPosition(int i) 
{
	brick.x = ((((i % columns) + 1) * SPACING) + ((i % columns) * brick.w) - (SPACING / 2));
	brick.y = (brick.h * 3 + (((i % rows) + 1) * SPACING) + ((i % rows) * brick.h) - (SPACING / 2)) + 30 * level;
}

void BallPaddleBrick::UpdateBallAndPaddle() 
{
	//if ball hits paddle...
	if (SDL_HasIntersection(&ball, &paddle)) 
	{
		float relative = (paddle.x + (paddle.w / 2)) - (ball.x + (ballSize / 2));
		float normal = relative / (paddle.w / 2);
		float bounceBall = normal * (5 * PI / 12);

		velocityY = -ballSpeed * cos(bounceBall);
		velocityX = ballSpeed * -sin(bounceBall);
	}

	if (ball1->y <= 0) { velocityY = -velocityY; }
	if (ball1->y + ballSize >= SCREEN_HEIGHT) { velocityY = -velocityY; lifeCount--; }
	if (ball1->x <= 0 || ball1->x + ballSize >= SCREEN_WIDTH) { velocityX = -velocityX; }
	ball1->y += velocityY;
	ball1->x += velocityX;
	if (paddle.x < 0) { paddle.x = 0; }
	if (paddle.x + paddle.w > SCREEN_WIDTH) { paddle.x = SCREEN_WIDTH - paddle.w; }
	if (lifeCount <= 0) { ResetLevel(true); }


	for (int i = 0; i < columns * rows; i++) 
	{
		setBrickPosition(i);
		
		if (SDL_HasIntersection(&ball, &brick) && bricks[i] > 0) 
		{
			points++;
			bricks[i]--;

			if(ball1->x >= brick.x) { velocityX = velocityX * -1; ball1->x = ball1->x - 20; }
			if (ball1->x <= brick.x) { velocityX = velocityX * -1; ball1->x = ball1->x + 20; }
			if (ball1->y <= brick.y) { velocityY = velocityY * -1; ball1->y = ball1->y - 20; }
			if (ball1->y >= brick.y) { velocityY = velocityY * -1; ball1->y = ball1->y + 20; }

			if (points == 5 * level) 
			{
				ResetLevel(false);
			}
		}
	}
}

void BallPaddleBrick::RenderBallPaddleBrick()
{
	ball1->render(aRenderer);
	//white paddles
	SDL_SetRenderDrawColor(aRenderer, colour.r, colour.g, colour.g, 255);
	SDL_RenderFillRect(aRenderer, &paddle);
	SDL_SetRenderDrawColor(aRenderer, 255, 255, 0, 255);
	SDL_RenderFillRect(aRenderer, &ball);
	//SDL_RenderClear(aRenderer);
	/*WriteFont("Level " + std::to_string(level), 20 + FONT_SIZE / 2 * 6, FONT_SIZE * 1.5);
	WriteFont(std::to_string(lifeCount), SCREEN_WIDTH / 2 + FONT_SIZE / 2, FONT_SIZE * 1.5);
	WriteFont(std::to_string(points), SCREEN_WIDTH - 40, FONT_SIZE * 1.5);*/


	//used for rendering bricks to screen
	for (int i = 0; i < columns * rows; i++) {
		SDL_SetRenderDrawColor(aRenderer, brickColour.r, brickColour.g, brickColour.b, 255 * bricks[i] / level);
		if (i % 2 == 0)SDL_SetRenderDrawColor(aRenderer, brickColour.g, brickColour.r, brickColour.b, 255 * bricks[i] / level);
		if (bricks[i] > 0) {
			setBrickPosition(i);
			SDL_RenderFillRect(aRenderer, &brick);
		}
	}

	SDL_RenderPresent(aRenderer);
}