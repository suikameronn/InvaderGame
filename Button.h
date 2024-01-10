#pragma once
#include<iostream>
#include<SDL.h>

#include"Text.h"
#include"Listner.h"

using namespace std;

class Button : public Text,public Listner
{
private:
	Position* offSet = nullptr;
	Position OffSet;

	SDL_Color* color;
	SDL_Color Color;

	SDL_Rect* clip = nullptr;
	SDL_Point* center = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double angle = 0;

	unique_ptr<Listner> listner;

	void changeColor(bool hit);

public:
	Text* label;


	Button();
	~Button();

	void setOffSet(float x, float y);
	void setLabel(string text, unsigned char r, unsigned char g, unsigned char b, TTF_Font* labelFont);
	void setLabel(string text, unsigned char r, unsigned char g, unsigned char b, TTF_Font* labelFont,int size);
	void setListner(Listner* obj);

	bool hitCheck(Mouse* mouse) override;
	void drawObjects(SDL_Renderer* gRenderer) override;
};