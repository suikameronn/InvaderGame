#pragma once
#include<iostream>
#include <SDL.h>
#include <assert.h>
#include<functional>

#include"lua.hpp"
#include"lualib.h"
#include"luaconf.h"
#include"lauxlib.h"

#include"Mouse.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

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
	SCROLL,
	PLAYER,
	ENEMY,
	BULLET
};

class Object
{
protected:
	bool visible;

	OBJECT type;

	bool createdTex;
	bool changed;

	Position* pos;
	Position position;

	Position* tarPos;
	Position tarPosition;

	float disappearTime;
	float disappearInterval;
	int disappearCount;

	int moveCount;
	int moveCountList;
	float length;
	float onceMoveX;
	float onceMoveY;
	vector<Position> moveList;

	void disappear();

public:
	bool actSet;
	bool actSetList;

	Object();
	virtual ~Object();

	OBJECT getType() { return type; }
	bool isVisible() { return visible; }

	float currentPosX() const;
	float currentPosY() const;
	virtual float getBottom();

	virtual void setPos(float px, float py);
	virtual void setOffSet(float x, float y) {};

	void setMoveList(float px, float py);
	void clearMoveList();
	void actMoveList();
	virtual void setMove(float px, float py);
	void setMove(Position p);
	void setMove(float px, float py, int fps);
	virtual bool actMove();

	void setDisappear(float time, int count);

	virtual void drawObjects(SDL_Renderer* gRenderer);
	virtual void drawObjectsScroll(SDL_Renderer* gRenderer, Position* scrollPos,Position* offset);
	virtual bool hitCheck();
	virtual bool hitCheckScroll(Position* scrollPos, Position* scrollOffSet);

	virtual void Update();
};