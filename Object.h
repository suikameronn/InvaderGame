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

	bool createdTex;
	bool changed;

	Position* pos;
	Position position;
public:
	Object();
	void setPos(int px, int py);
	virtual void draw(SDL_Renderer* gRenderer);
};