#include "Square.h"

Square::Square() 
{

}

Square::~Square()
{

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
	SDL_Render1FillRect(aRenderer, &rect);
}