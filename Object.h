#pragma once
#include<iostream>
#include <SDL.h>

struct Position
{
	float x;
	float y;
};

class Object
{
protected:
	bool createdTex;
	bool changed;
	bool moveFinish;

	Position* pos = NULL;
	Position position;

	Position* tarPos = NULL;
	Position tarPosition;

	Position* movePos = NULL;
	Position movePosition;

	float length;
	int count = 0;

public:
	Object();
	
	void setPos(float px, float py);
	void setMove(float px, float py);
	void actMove();

	virtual void drawObjects(SDL_Renderer* gRenderer);
};