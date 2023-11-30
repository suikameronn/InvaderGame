#pragma once
#include<iostream>
#include<vector>
#include"Text.h"

using namespace std;

class Title
{
private:
	Text* title;
	SDL_Color color;

	vector<Object*> drawList;
public:

	Title();
	Title(string titleName, TTF_Font* font);

	void draw();
};