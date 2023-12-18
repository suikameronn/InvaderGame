#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>

#include"Object.h"
#include"Mouse.h"

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

	virtual void otherUpdate_virtual();

	void hitCheckScene(Mouse* mouse);
	void drawScene(SDL_Renderer* gRenderer);
};