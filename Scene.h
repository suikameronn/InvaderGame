#pragma once

#include<iostream>
#include<map>
#include<vector>
#include<SDL.h>
#include <windows.h>

#include"Object.h"
#include"Mouse.h"
#include"Button.h"

//#include"Player.h"
//#include"Enemy.h"

using namespace std;

enum FONTS;

enum ObjType
{
	BUTTON,
	PLAYER,
	ENEMY
};

class Scene
{
protected:

	int frameCount = 0;


	vector<Object*> drawList;

	vector<Object*> button_CheckList;
	vector<Object*> player_CheckList;
	vector<Object*> enemy_CheckList;

	void addObjectToScene(Text* text);
	void addObjectToScene(Button* button);

	map<int,Object*> actTimer;

public:
	bool sceneChange;

	Scene();

	void hitCheckScene(Mouse* mouse);
	void drawScene(SDL_Renderer* gRenderer);

	virtual void Update_Scene();
};