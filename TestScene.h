#pragma once

#include"Scene.h"

class TestScene:public Scene
{
public:
	TestScene(vector<TTF_Font*> fonts, SDL_Renderer* gRenderer);

	int Update_Scene() override
};