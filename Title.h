#pragma once
#include<iostream>
#include<vector>
#include<SDL.h>

#include"Scene.h"
#include"Text.h"
#include"Button.h"

using namespace std;

class Title : public Scene
{
private:
	Text* titleText;
	SDL_Color color;

	Button* button;

	vector<Object*> drawList;
	vector<Object*> hitCheckList;

public:

	Title();
	Title(string titleName, TTF_Font* font);

	void hitCheckScene(int* x, int* y, bool clicked);
	void drawScene(SDL_Renderer* gRenderer);
	int sceneChanger();
};