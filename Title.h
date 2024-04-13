#pragma once
#include<iostream>
#include<vector>
#include<SDL.h>

#include"Scene.h"

using namespace std;

class Title : public Scene
{
private:

	enum class FONTS
	{
		SMALL,
		NORMAL,
		BIG
	};

public:

	Title(vector<TTF_Font*> fonts);

	void Update_Scene() override;
};