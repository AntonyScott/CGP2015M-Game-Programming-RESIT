#pragma once
#ifndef aSquareFile
#define aSquareFile
#include <iostream>
#include "SDL.h"
class Square
{
public:
	Square();
	~Square();
	void Init();
	void Update();
	void Input(int whichKey);
	void Render(SDL_Renderer* aRenderer);
	SDL_Rect rect;
	int x, y, height, width, R, G, B;
};
#endif