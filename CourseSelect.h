#pragma once
#include<iostream>
#include<vector>
#include<SDL.h>

#include"MenuScene.h"

using namespace std;

class CourseSelect: public MenuScene
{

public:

	CourseSelect(vector<TTF_Font*> fonts,SDL_Renderer* gRenderer);

	int Update_Scene() override;
};