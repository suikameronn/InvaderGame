#pragma once
#include<iostream>
#include<vector>
#include<SDL.h>

#include"Scene.h"

using namespace std;

class Title : public Scene
{
private:

public:

	Title(vector<TTF_Font*> fonts, SDL_Renderer* gRenderer);

	int Update_Scene() override;
};