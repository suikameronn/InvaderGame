#pragma once
#include<iostream>
#include <SDL.h>

struct Position
{
	int x;
	int y;
};

class Object
{
protected:
	Position* pos;
public:
	Object();
	void setPos(int x, int y);
	virtual void draw(SDL_Renderer* gRenderer);
};