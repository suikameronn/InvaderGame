#pragma once
#include<iostream>
#include <SDL2/SDL.h>

struct Position
{
	int x;
	int y;
};

class Object
{
protected:
	Position* pos;
	Position position;
public:
	Object();
	void setPos(int px, int py);
	virtual void draw(SDL_Renderer* gRenderer);
};