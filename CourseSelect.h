#pragma once
#include<iostream>

#include"Scene.h"

using namespace std;

class CourseSelect: public Scene
{
	enum class FONTS
	{
		NORMAL,
		BIG
	};


	unique_ptr<Text> titleText;
	SDL_Color color;

	unique_ptr<Button> button;
	SDL_Color bColor;

public:
	
	CourseSelect(vector<TTF_Font*> fonts);

	void Update_Scene() override;
};