#pragma once
#include<iostream>
#include<string>
#include <SDL.h>
#include <SDL_ttf.h>

#include"Object.h"

using namespace std;

class Text:public Object
{
private:

	TTF_Font* gFont;
	string text;
	SDL_Color color;
	SDL_Rect renderQuad;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	SDL_Surface* textSurface;


	SDL_Rect* clip = NULL;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double angle = 0;

public:

	Text();
	Text(TTF_Font* font);
	void setText(string text);
	void setColor(SDL_Color color);
	void setFont(TTF_Font* font);

	virtual void drawObjects(SDL_Renderer* gRenderer) override;
};

