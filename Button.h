#pragma once
#include<iostream>
#include<SDL.h>

#include"Text.h"
using namespace std;

class Scene;

class Button : public Text
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

	std::function<void()> listner;

	int fontSize;

	void setPosText();
	void changeColor(bool hit);

public:
	Text* label;

	Button();
	~Button();

	void setOffSet(float x, float y) override;
	void setLabel(string text, unsigned char r, unsigned char g, unsigned char b, TTF_Font* labelFont);
	void setLabel(string text, unsigned char r, unsigned char g, unsigned char b, TTF_Font* labelFont,int size);
	void setLabelSize(int size);
	void setLabel(string text);
	Text* getLabel() { return label; }
	void setNextScene(std::function<void()> f);

	void setPos(float px, float py) override;
	float getBottom() override;
	bool hitCheck() override;
	bool hitCheckScroll(Position* scrollPos,Position* scrollOffSet) override;
	void drawObjects(SDL_Renderer* gRenderer) override;
	void drawObjectsScroll(SDL_Renderer* gRenderer, Position* scrollPos,Position* offset) override;
};