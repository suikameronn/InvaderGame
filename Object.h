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

	Position* pos = NULL;
	Position position;

	Position* movePos = NULL;
	Position movePosition;

	int count = 0;
public:
	Object();
	
	void setPos(int px, int py);
	void setMove(int px, int py);
	void actMove();

	virtual void draw(SDL_Renderer* gRenderer);
};