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
	SDL_Color color;
	SDL_Rect* clip;
	SDL_Rect renderQuad;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	SDL_Surface* textSurface;

	SDL_Point* center = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double angle = 0;

	string text;

public:

	Text();
	~Text();
	Text(TTF_Font* font);

	void Update() override;

	void setText(string text);
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	void setFont(TTF_Font* font);
	string getText();
	float getBottom() override;

	void drawObjects(SDL_Renderer* gRenderer) override;
	void drawObjectsScroll(SDL_Renderer* gRenderer, Position* scrollPos,Position* offset) override;
};

