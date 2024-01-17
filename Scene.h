#pragma once

#include<iostream>
#include <unordered_map>
#include<map>
#include<vector>
#include<SDL.h>
#include <windows.h>

#include"Object.h"
#include"Mouse.h"
#include"Text.h"
#include"Button.h"
#include"ScrollPanel.h"

//#include"Player.h"
//#include"Enemy.h"

using namespace std;

enum FONTS;

enum ObjType
{
	TEXT,
	BUTTON,
	PLAYER,
	ENEMY
};

class Scene
{
protected:

	int frameCount = 0;

	unordered_map<string, unique_ptr<Object>> objList;

	unordered_map<string,unique_ptr<Object>,less<>> drawList;

	unordered_map<string, unique_ptr<Object>> button_CheckList;
	unordered_map<string, unique_ptr<Object>> player_CheckList;
	unordered_map<string, unique_ptr<Object>> enemy_CheckList;

	void addObjectToScene(Text* text,string objName);
	void addObjectToScene(Button* button, string objName);
	void addObjectToScene(ScrollPanel* button, string objName);

	map<int,Object*> actTimer;

public:

	Scene();
	virtual ~Scene();

	void hitCheckScene(Mouse* mouse);
	void drawScene(SDL_Renderer* gRenderer);

	virtual void Update_Scene();
};