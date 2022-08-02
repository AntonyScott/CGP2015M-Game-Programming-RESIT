#include "GameContainerSquare.h"

GameContainerSquare::GameContainerSquare() 
{

}



void GameContainerSquare::Init(int eX, int eY, int eDirX, int eDirY, int eNum)
{
	x = eX;
	y = eY;
	dirX = eDirX;
	dirY = eDirY;
	num = eNum;

	for (int i = 0; i < num; i++) 
	{
		int posX = x + (i * (dirX * 10));
		int posY = y + (i * (dirY * 10));
		Add(posX, posY);
	}
}

void GameContainerSquare::Add(int x, int y) 
{
	Square* aSquare = new Square();
	aSquare->Init(x, y, 5, 5);
	this->aListOfSquares.push_back(aSquare);
}

void GameContainerSquare::Render(SDL_Renderer* aRenderer) 
{
	for (auto& element : aListOfSquares) 
	{
		element->Render(aRenderer);
	}
}

void GameContainerSquare::Update() 
{
	for (auto& element : aListOfSquares) 
	{
		element->rect.w++;
	}
}

GameContainerSquare::~GameContainerSquare()
{
	for (auto& element : aListOfSquares) 
	{
		delete element;
	}
}