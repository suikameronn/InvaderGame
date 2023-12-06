#pragma once

#include<iostream>
#include<SDL.h>

class Scene
{
protected:
	bool sceneChange;

	virtual int sceneChanger();

public:
	Scene* scene;

	Scene();
	Scene(Scene* inputScene);

	void setScene(Scene* inputScene);

	virtual void drawScene(SDL_Renderer* gRenderer);
};