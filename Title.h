#pragma once
#include<iostream>
#include<vector>
#include<SDL.h>

#include"MenuScene.h"

using namespace std;

class Title : public MenuScene
{
private:

public:

	Title(vector<TTF_Font*> fonts, SDL_Renderer* gRenderer);

	int Update_Scene() override;
};