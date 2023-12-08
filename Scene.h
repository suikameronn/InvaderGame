#pragma once

#include<iostream>
#include<SDL.h>

using namespace std;

enum FONTS;

class Scene
{
protected:
	virtual int sceneChanger();

public:
	bool sceneChange;

	Scene();

	virtual void hitCheckScene(int* x, int* y, bool clicked);
	virtual void drawScene(SDL_Renderer* gRenderer);
};