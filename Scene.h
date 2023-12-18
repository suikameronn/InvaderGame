#pragma once

#include<iostream>
#include<SDL.h>

using namespace std;

enum FONTS;

class Scene
{
protected:
	int sceneChanger();
	void hitCheckScene(int* x, int* y, bool clicked);
	void drawScene(SDL_Renderer* gRenderer);

public:
	bool sceneChange;

	Scene();

	virtual void Update_virtual();
};