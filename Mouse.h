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

	static Mouse* instance;

	Mouse();
	~Mouse();

public:

	static Mouse* GetInstance()
	{
		if (instance)
		{
			return instance;
		}

		instance = new Mouse();
	}

	int mx, my;
	int wheel;
	bool clickDown;
	bool clickUp;
	bool spaceKey;
	bool quit;

	void setMouseState();
	void setFalseClickUpDown();

	void DestroyMouse() { delete instance; }
};