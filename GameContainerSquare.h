#pragma once
#ifndef GameContainerSquareFILE
#define GameContainerSquareFILE

#include <vector>
#include <iostream>
#include "SDL.h"
#include "Square.h"

class GameContainerSquare 
{
public:
	GameContainerSquare();
	~GameContainerSquare();

	void Init(int eX, int eY, int eDirX, int eDirY, int eNum);
	void Add(int x, int y);
	void Update();
	void Render(SDL_Renderer* aRenderer);


	std::vector<Square*> aListOfSquares;
	int x, y, num;
	float dirX, dirY;
};
#endif
