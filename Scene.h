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

#include"Object.h"
#include"Mouse.h"
#include"Text.h"
#include"Button.h"
#include"ScrollPanel.h"

//#include"Player.h"
//#include"Enemy.h"

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
	int frameCount = 0;

	vector<TTF_Font*> fonts;

	unordered_map<string, shared_ptr<Object>> objList;

	unordered_map<string,shared_ptr<Object>,less<>> drawList;

	void addObjectToScene(Text* text,string objName);
	void addObjectToScene(Button* button, string objName);
	void addObjectToScene(ScrollPanel* button, string objName);

	map<int,Object*> actTimer;

	SDL_Renderer* gRenderer;

	void initLuaScript(lua_State* pL);

public:

	Scene();
	Scene(vector<TTF_Font*> fonts, SDL_Renderer* gRenderer);
	virtual ~Scene();

	void changeScene(int nextSceneNum);

	void hitCheckScene();
	void drawScene();

	virtual int Update_Scene();

	void createText(std::string objName);
	void createButton(std::string objName);
	void createScrollPanel(std::string objName);
	void setPos(std::string objName,float x, float y);
	void setOffSet(std::string objName, float ox, float oy);
	void setText(std::string objName, std::string text);
	void setColor(std::string objName, unsigned char r, unsigned char g, unsigned char b);
	void setFont(std::string objName, FONTS font);
	void setListner(std::string objName, EVENT event);
	void setMove(std::string objName,float px, float py, int fps);
	void setMoveList(std::string objName, float px, float py);
};

int glue_createText(lua_State* pL);
int glue_createButton(lua_State* pL);
int glue_createScrollPanel(lua_State* pL);
int glue_setPos(lua_State* pL);
int glue_setOffSet(lua_State* pL);
int glue_setText(lua_State* pL);
int glue_setColor(lua_State* pL);
int glue_setFont(lua_State* pL);
int glue_setListner(lua_State* pL);
int glue_setMove(lua_State* pL);
int glue_setMoveList(lua_State* pL);