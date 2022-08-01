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
	void Init(int x, int y, int width, int height);
	void Update();
	void Input(int whichKey);
	void Render(SDL_Renderer* aRenderer);
	SDL_Rect rect;
	int R, G, B;
};
#endif