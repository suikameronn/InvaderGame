#pragma once
#include<iostream>
#include<vector>
#include<SDL.h>

#include"Scene.h"
#include"Text.h"

using namespace std;

class Title : public Scene
{
private:
	Text* titleText;
	SDL_Color color;

	float count = 0.0f;

	vector<Object*> drawList;
	vector<Object*> hitCheckList;

public:

	Title();
	Title(string titleName, TTF_Font* font);

	void drawScene(SDL_Renderer* gRenderer);
	int sceneChanger();
};