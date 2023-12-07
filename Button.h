#pragma once
#include<iostream>
#include<SDL.h>

#include"Text.h"

class Button : public Text, public Object
{
private:
	Position* offSet = NULL;
	Position OffSet;

	void* exeMethod;

	SDL_Color* color;
	SDL_Color Color;

	SDL_Rect* clip = NULL;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double angle = 0;

	void changeColor(bool hit);

public:
	Button();

	void setOffSet(float x, float y);
	bool hitCheck(int* x, int* y,bool clicked) override;

	void drawObjects(SDL_Renderer* gRenderer) override;
};