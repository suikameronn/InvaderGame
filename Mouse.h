#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>

using namespace std;

class Mouse
{
private:
	//Event handler
	SDL_Event e;

public:

	int mx, my;
	int wheel;
	bool clickDown;
	bool clickUp;
	bool quit;

	Mouse();

	void setMouseState();
	void setFalseClickUpDown();
};