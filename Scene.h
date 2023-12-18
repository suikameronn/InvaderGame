#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>

#include"Object.h"

using namespace std;

enum FONTS;

class Scene
{
protected:
	int sceneChanger();

	vector<Object*> drawList;
	vector<Object*> hitCheckList;

public:
	bool sceneChange;

	Scene();

	virtual void Update_virtual();

	void hitCheckScene(int* x, int* y, bool clicked);
	void drawScene(SDL_Renderer* gRenderer);
};