#pragma once

#include<iostream>
#include<SDL.h>

using namespace std;

class Scene
{
protected:
	virtual int sceneChanger();

public:
	bool sceneChange;
	Scene* scene;

	Scene();

	void setScene(Scene* inputScene);

	virtual void drawScene(SDL_Renderer* gRenderer);
};