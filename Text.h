#pragma once
#include<iostream>
#include<string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include"Object.h"

using namespace std;

class Text:public Object
{
private:

	unique_ptr<TTF_Font> gFont;
	string text;
	SDL_Color color;
	SDL_Rect rederQuad;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;

	SDL_Rect* clip = NULL;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip;
	double angle = 0;

public:

	Text();
	Text(TTF_Font* font);
	void setText(string text);
	void setColor(SDL_Color color);

	virtual void draw(SDL_Renderer* gRenderer) override;
};

