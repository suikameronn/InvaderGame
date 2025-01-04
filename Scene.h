#pragma once

#include<iostream>
#include <unordered_map>
#include<map>
#include<vector>
#include<SDL.h>
#include <windows.h>
#include<functional>
#include<string>

#include"lua.hpp"
#include"lualib.h"
#include"luaconf.h"
#include"lauxlib.h"

using namespace std;

enum FONTS
{
	SMALL,
	NORMAL,
	BIG
};

enum EVENT
{
	GOTO_TITLE,
	GOTO_COURSE_SELECT
};

class Scene
{
protected:

	int nextSceneNum = 0;

	SDL_Renderer* gRenderer;

public:

	Scene();
	virtual ~Scene() {};

	void changeScene(int nextSceneNum);

	virtual void hitCheckScene() = 0;
	virtual void drawScene() = 0;

	virtual int Update_Scene() = 0;
};