#pragma once
#include<iostream>
#include<SDL.h>

#include"Text.h"
#include"Listner.h"

class Button : public Text,public Listner
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

	Listner* listner;

	void changeColor(bool hit);
	void buttonClicked(auto method);

public:
	Button();

	void setOffSet(float x, float y);
	void setLabel(string text, SDL_Color* textColor, TTF_Font* labelFont);
	void setLabel(string text, SDL_Color* textColor, TTF_Font* labelFont,int size);
	void setListner(Listner* obj);
	Text* getLabel();

	bool hitCheck(int* x, int* y,bool clicked) override;
	void drawObjects(SDL_Renderer* gRenderer) override;
};