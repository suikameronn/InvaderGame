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
	bool click;

	Mouse();

	void setMouseState();
};