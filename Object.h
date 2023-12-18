#pragma once
#include<iostream>
#include <SDL.h>

#include"Mouse.h"

using namespace std;

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

	Position* pos;
	Position position;

	Position* tarPos;
	Position tarPosition;

	Position* movePos;
	Position movePosition;

	float length;
	int count = 0;

public:
	Object();
	
	void setPos(float px, float py);
	void setMove(float px, float py);
	void actMove();

	virtual void drawObjects(SDL_Renderer* gRenderer);
	virtual bool hitCheck(Mouse* mouse);
};