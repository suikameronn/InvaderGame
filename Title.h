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

	enum class FONTS
	{
		NORMAL,
		BIG
	};


	unique_ptr<Text> titleText;
	SDL_Color color;

	unique_ptr<Button> button;
	SDL_Color bColor;

public:

	Title(string titleName, vector<TTF_Font*> fonts);

	void Update();
	void hitCheckScene(int* x, int* y, bool clicked);
	void drawScene(SDL_Renderer* gRenderer);
};