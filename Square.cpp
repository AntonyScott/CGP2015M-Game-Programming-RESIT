#include "Square.h"

Square::Square() 
{

}

Square::~Square()
{

}

void Square::Init() 
{
	rect.x = 70;
	rect.y = 70;
	rect.w = 100;
	rect.h = 100;

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
}