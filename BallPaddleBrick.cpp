#include "BallPaddleBrick.h"

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
	ball.y = paddle.y - (paddle.h * 4);
	velocityY = ballSpeed / 2;
	velocityX = 0;
	ball.x = SCREEN_WIDTH / 2 - (ballSize / 2);
}

void BallPaddleBrick::InitVariables() 
{
	colour.r = colour.g = colour.b = 255;
	brickColour.r = 30; brickColour.g = brickColour.b = 100;
	paddle.h = 22; 
	paddle.w = SCREEN_HEIGHT / 4;
	paddle.h = 12;
	ball.w = ball.h = ballSize;
	trail.w = trail.h = ballSize;
	paddle.y = SCREEN_HEIGHT - paddle.h - 32;

	brick.w = (SCREEN_WIDTH - (SPACING * columns)) / columns;
	brick.h = 22;

	//ResetLevel(true);
}

//sets postion of bricks on screen
void BallPaddleBrick::setBrickPosition(int i) 
{
	brick.x = ((((i % columns) + 1) * SPACING) + ((i % columns) * brick.w) - (SPACING / 2));
	brick.y = (brick.h * 3 + (((i % rows) + 1) * SPACING) + ((i % rows) * brick.h) - (SPACING / 2)) + 30 * level;
}

void BallPaddleBrick::WriteFont(std::string text, int x, int y) 
{
	SDL_Surface* surf;
	SDL_Texture* tex;

	const char* t = text.c_str();

	surf = TTF_RenderText_Solid(font, t, colour);
	tex = SDL_CreateTextureFromSurface(aRenderer, surf);

	/*lives.w = surf->w;
	lives.h = surf->h;
	lives.x = x - lives.w;
	lives.y = y - lives.h;*/

	SDL_FreeSurface(surf);
	SDL_RenderCopy(aRenderer, tex, NULL, &lives);
	SDL_DestroyTexture(tex);
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

	if (ball.y <= 0) { velocityY = -velocityY; }
	if (ball.y + ballSize >= SCREEN_HEIGHT) { velocityY = -velocityY; lifeCount--; }
	if (ball.x <= 0 || ball.x + ballSize >= SCREEN_WIDTH) { velocityX = -velocityX; }
	ball.y += velocityY;
	ball.x += velocityX;
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

			if(ball.x >= brick.x) { velocityX = velocityX * -1; ball.x = ball.x - 20; }
			if (ball.x <= brick.x) { velocityX = velocityX * -1; ball.x = ball.x + 20; }
			if (ball.y <= brick.y) { velocityY = velocityY * -1; ball.y = ball.y - 20; }
			if (ball.y >= brick.y) { velocityY = velocityY * -1; ball.y = ball.y + 20; }

			if (points == 5 * level) 
			{
				ResetLevel(false);
			}
		}
	}
}

void BallPaddleBrick::RenderBallPaddleBrick()
{
	//white paddles
	SDL_SetRenderDrawColor(aRenderer, colour.r, colour.g, colour.g, 255);
	SDL_RenderFillRect(aRenderer, &paddle);
	SDL_SetRenderDrawColor(aRenderer, 255, 255, 0, 255);
	SDL_RenderFillRect(aRenderer, &ball);

	WriteFont("Level " + std::to_string(level), 20 + FONT_SIZE / 2 * 6, FONT_SIZE * 1.5);
	WriteFont(std::to_string(lifeCount), SCREEN_WIDTH / 2 + FONT_SIZE / 2, FONT_SIZE * 1.5);
	WriteFont(std::to_string(points), SCREEN_WIDTH - 40, FONT_SIZE * 1.5);


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