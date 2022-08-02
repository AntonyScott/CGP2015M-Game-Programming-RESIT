#pragma once
#ifndef aSquareFile
#define aSquareFile
#include <iostream>
#include <vector>
#include "SDL.h"
class Square
{
public:
	std::vector<Square*> aSquareList;
	Square();
	~Square();
	void Init(int x, int y, int width, int height);
	void Update();
	void Input(int whichKey);

	void Render(SDL_Renderer* aRenderer);
	SDL_Rect rect;
	int x, y, height, width, R, G, B;

	static int SquareCounterTotal;
	int SquareCounter;
};
#endif