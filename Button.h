#pragma once
#include<iostream>
#include<SDL.h>

#include"Text.h"

class Button : public Text,public Object
{
private:
	Position* offSet = NULL;
	Position OffSet;

	void* exeMethod;

	SDL_Rect* clip = NULL;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double angle = 0;

public:
	Button();
	void setOffSet(int* x, int* y);
	void setColor(SDL_Color* col);
	void setChangeColor(SDL_Color* col);

	bool hitCheck(int* x, int* y,bool clicked) override;
};