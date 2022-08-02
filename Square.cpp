#include "Square.h"

Square::Square() 
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square Constructed with Param(%p)", this);
}

Square::~Square()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Square Destroyed with Param(%p)", this);
}

void Square::Init(int x, int y, int width, int height)
{
	rect.x = x;
	rect.y = y;
	rect.h = height;
	rect.w = width;

	R = 255;
	G = 0;
	B = 0;

	for (int i = 0; i < 10; i++) 
	{
		Square* aSquare = new Square();
		aSquare->Init(20 * i, 20 * i, 10, 10);
		aSquareList.push_back(aSquare);
	}
}

void Square::Update() 
{

}

void Square::Input(int whichKey) 
{
	switch (whichKey)
	{
	case 'w':
	{
		printf ("Square: W is pressed \n"); 
		break;
	}
	}
}

void Square::Render(SDL_Renderer* aRenderer) 
{
	SDL_SetRenderDrawColor (aRenderer, R, G, B, 255);
	SDL_RenderDrawRect (aRenderer, &rect);
	SDL_RenderFillRect(aRenderer, &rect);

	for (auto& aSquareIterator : aSquareList) 
	{
		aSquareIterator->Render(aRenderer);
	}
}