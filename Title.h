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

	float count = 0.0f;

	vector<Object*> drawList;
public:

	Title();
	Title(string titleName, TTF_Font* font);

	void draw(SDL_Renderer* gRenderer);
};