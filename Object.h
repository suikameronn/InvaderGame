#pragma once
#include<iostream>
#include <SDL.h>
#include <assert.h>
#include<functional>

#include"Mouse.h"

using namespace std;

extern int fps;

struct Position
{
	float x;
	float y;
};

enum OBJECT
{
	EMPTY,
	TEXT,
	BUTTON,
	SCROLL
};

class Object
{
protected:
	OBJECT type;

	bool createdTex;
	bool changed;

	Position* pos;
	Position position;

	Position* tarPos;
	Position tarPosition;

	int moveCount;
	int moveCountList;
	double length;
	double onceMoveX;
	double onceMoveY;
	vector<Position> moveList;

public:
	bool actSet;
	bool actSetList;

	Object();
	virtual ~Object();

	OBJECT getType() { return type; }

	float currentPosX() const;
	float currentPosY() const;
	virtual float getBottom();

	virtual void setPos(float px, float py);
	virtual void setOffSet(float x, float y) {};

	void setMoveList(float px, float py);
	void clearMoveList();
	void actMoveList();
	void setMove(float px, float py);
	void setMove(Position p);
	void setMove(float px, float py, int fps);
	void actMove();

	virtual void drawObjects(SDL_Renderer* gRenderer);
	virtual void drawObjectsScroll(SDL_Renderer* gRenderer, Position* scrollPos,Position* offset);
	virtual bool hitCheck();
	virtual bool hitCheckScroll(Position* scrollPos, Position* scrollOffSet);
};