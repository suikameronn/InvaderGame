#pragma once
#include<iostream>
#include<vector>
#include"Text.h"

using namespace std;

class Title
{
private:
	Text* titleText;
	SDL_Color color;

	int count = 0;

	vector<Object*> drawList;
public:

	Title();
	Title(string titleName, TTF_Font* font);

	void draw(SDL_Renderer* gRenderer);
};