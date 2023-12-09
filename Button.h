#pragma once
#include<iostream>
#include<SDL.h>

#include"Text.h"

class Button : public Text, public Object
{
private:
	Position* offSet = nullptr;
	Position OffSet;

	SDL_Color* color;
	SDL_Color Color;

	Text* label;

	void* exeMethod;

	SDL_Rect* clip = nullptr;
	SDL_Point* center = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double angle = 0;

	void changeColor(bool hit);
	void* buttonClicked();

public:
	Button();

	void setOffSet(float x, float y);
	void setLabel(string text, SDL_Color* textColor, TTF_Font* labelFont);
	void setLabel(string text, SDL_Color* textColor, TTF_Font* labelFont,int size);
	void setMethod(void* method);
	Text* getLabel();

	bool hitCheck(int* x, int* y,bool clicked) override;
	void drawObjects(SDL_Renderer* gRenderer) override;
};