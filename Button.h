#pragma once
#include<iostream>
#include<SDL.h>

#include"Text.h"

class Button : public Text,public Object
{
private:
	Position* offSet = NULL;
	Position OffSet;

	SDL_Color* color = NULL;
	SDL_Color Color;

	SDL_Color* changeColor = NULL;
	SDL_Color ChangeColor;

	void* exeMethod;

public:
	Button();
	void setOffSet(int* x, int* y);
	void setColor(SDL_Color* col);
	void setChangeColor(SDL_Color* col);

	bool hitCheck(int* x, int* y,bool clicked) override;
};