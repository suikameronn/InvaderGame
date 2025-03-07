#pragma once

#include<iostream>
#include <unordered_map>
#include<map>
#include<vector>
#include<SDL.h>
#include <windows.h>
#include<functional>
#include<string>

#include"EnumList.h"

#include"lua.hpp"
#include"lualib.h"
#include"luaconf.h"
#include"lauxlib.h"

#include"Object.h"
#include"Text.h"
#include"Button.h"
#include"ScrollPanel.h"

enum FONTS
{
	SMALL,
	NORMAL,
	BIG
};

class GameManager;

class Scene
{
protected:
	lua_State* lua;

	int nextSceneNum = 0;
	std::string nextLuaPath;

	SDL_Renderer* gRenderer;

	std::vector<TTF_Font*> fonts;

	std::vector<std::shared_ptr<Object>> objList;

public:

	Scene();
	virtual ~Scene() {};

	void luaFunctionRegister();
	void luaNumberRegister();

	void changeScene(int nextSceneNum,std::string path);

	std::string getNextLuaPath() { return nextLuaPath; }

	TTF_Font* getFont(FONTS fonts);

	void addObject(std::shared_ptr<Object> obj);

	int startSound(SoundNumber num, bool loop);

	virtual void hitCheckScene() = 0;
	virtual void drawScene() = 0;

	virtual int Update_Scene() = 0;
};

static int glueCreateText(lua_State* lua)
{
	std::shared_ptr<Text> text = std::shared_ptr<Text>(new Text());

	lua_getglobal(lua, "Scene");
	Scene* scene = static_cast<Scene*>(lua_touserdata(lua, -1));
	scene->addObject(text);

	lua_pushlightuserdata(lua, text.get());

	return 1;
}

static int glueCreateButton(lua_State* lua)
{
	std::shared_ptr<Button> button = std::shared_ptr<Button>(new Button());

	lua_getglobal(lua, "Scene");
	Scene* scene = static_cast<Scene*>(lua_touserdata(lua, -1));
	scene->addObject(button);

	lua_pushlightuserdata(lua, button.get());

	return 1;
}

static int glueCreateScrollPanel(lua_State* lua)
{
	std::shared_ptr<ScrollPanel> scrollPanel = std::shared_ptr<ScrollPanel>(new ScrollPanel());

	lua_getglobal(lua, "Scene");
	Scene* scene = static_cast<Scene*>(lua_touserdata(lua, -1));
	scene->addObject(scrollPanel);

	lua_pushlightuserdata(lua, scrollPanel.get());

	return 1;
}

static int glueCreateTextToPanel(lua_State* lua)
{
	Text* text = new Text();

	Object* obj = static_cast<Object*>(lua_touserdata(lua, -1));
	switch (obj->getType())
	{
	case SCROLL:
		ScrollPanel* panel = dynamic_cast<ScrollPanel*>(obj);
		panel->addObjectList(text);
	}

	lua_pushlightuserdata(lua, text);

	return 1;
}

static int glueCreateButtonToPanel(lua_State* lua)
{
	Button* button = new Button();

	Object* obj = static_cast<Object*>(lua_touserdata(lua, -1));
	switch (obj->getType())
	{
	case SCROLL:
		ScrollPanel* panel = dynamic_cast<ScrollPanel*>(obj);
		panel->addObjectList(button);
	}

	lua_pushlightuserdata(lua, button);

	return 1;
}

static int glueSetPos(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -3));
	float x = static_cast<float>(lua_tonumber(lua, -2));
	float y = static_cast<float>(lua_tonumber(lua, -1));

	obj->setPos(x, y);

	return 0;
}

static int glueSetOffset(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -3));
	float x = static_cast<float>(lua_tonumber(lua, -2));
	float y = static_cast<float>(lua_tonumber(lua, -1));

	switch (obj->getType())
	{
	case BUTTON:
		Button* button = dynamic_cast<Button*>(obj);
		button->setOffSet(x, y);
		break;
	}

	return 0;
}

static int glueSetColor(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -4));
	float r = static_cast<float>((lua_tonumber(lua, -3)));
	float g = static_cast<float>((lua_tonumber(lua, -2)));
	float b = static_cast<float>((lua_tonumber(lua, -1)));

	switch (obj->getType())
	{
	case TEXT:
	{
		Text* text = dynamic_cast<Text*>(obj);
		text->setColor(r, g, b);
		break;
	}
	case BUTTON:
	{
		Button* button = dynamic_cast<Button*>(obj);
		Text* text = button->getLabel();
		text->setColor(r, g, b);
		break;
	}
	}

	return 0;
}

static int glueSetText(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -2));
	std::string word = static_cast<std::string>(lua_tostring(lua, -1));

	switch (obj->getType())
	{
	case TEXT:
	{
		Text* text = dynamic_cast<Text*>(obj);
		text->setText(word);
		break;
	}
	case BUTTON:
	{
		Button* button = dynamic_cast<Button*>(obj);
		button->setLabel(word);
		break;
	}
	}

	return 0;
}

static int glueSetFont(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -2));
	FONTS font = static_cast<FONTS>(lua_tonumber(lua, -1));

	lua_getglobal(lua, "Scene");
	Scene* scene = static_cast<Scene*>(lua_touserdata(lua, -1));

	switch (obj->getType())
	{
	case TEXT:
	{
		Text* text = dynamic_cast<Text*>(obj);
		text->setFont(scene->getFont(font));
		break;
	}
	case BUTTON:
	{
		Button* button = dynamic_cast<Button*>(obj);
		Text* text = button->getLabel();
		text->setFont(scene->getFont(font));
		break;
	}
	}

	return 0;
}

static int glueSetLabelTextSize(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -2));
	int size = static_cast<int>(lua_tonumber(lua, -1));

	switch (obj->getType())
	{
	case BUTTON:
	{
		Button* button = dynamic_cast<Button*>(obj);
		button->setLabelSize(size);
		break;
	}
	}

	return 0;
}

static int glueSetLabelOffset(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -3));
	int x = static_cast<int>(lua_tointeger(lua, -2));
	int y = static_cast<int>(lua_tointeger(lua, -1));

	switch (obj->getType())
	{
	case BUTTON:
	{
		Button* button = dynamic_cast<Button*>(obj);
		button->setOffSet(x, y);
		break;
	}
	}

	return 0;
}

static int glueSetLabelColor(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -4));
	float r = static_cast<float>((lua_tonumber(lua, -3)));
	float g = static_cast<float>((lua_tonumber(lua, -2)));
	float b = static_cast<float>((lua_tonumber(lua, -1)));

	switch (obj->getType())
	{
	case BUTTON:
	{
		Button* button = dynamic_cast<Button*>(obj);
		Text* text = button->getLabel();
		text->setColor(r, g, b);
		break;
	}
	}

	return 0;
}

static int glueSetNextScene(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -3));
	int nextScene = static_cast<int>(lua_tointeger(lua, -2));
	std::string luaPath = std::string(lua_tostring(lua, -1));

	lua_getglobal(lua, "Scene");
	Scene* scene = static_cast<Scene*>(lua_touserdata(lua, -1));

	switch (obj->getType())
	{
	case BUTTON:
	{
		Button* button = dynamic_cast<Button*>(obj);
		std::function<void()> eventFunction = [=]()
			{
				scene->changeScene(nextScene,luaPath);
				scene->startSound(CLICKED, false);
			};
		button->setNextScene(eventFunction);
		break;
	}
	}

	return 0;
}

static int glueSetPanelSize(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -3));
	int width = static_cast<int>(lua_tointeger(lua, -2));
	int height = static_cast<int>(lua_tointeger(lua, -1));

	switch (obj->getType())
	{
	case SCROLL:
		ScrollPanel* panel = dynamic_cast<ScrollPanel*>(obj);
		panel->setPanelSize(width, height);
		break;
	}

	return 0;
}

static int glueSetScrollSpeed(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -2));
	float speed = static_cast<float>(lua_tonumber(lua, -1));

	switch (obj->getType())
	{
	case SCROLL:
		ScrollPanel* panel = dynamic_cast<ScrollPanel*>(obj);
		panel->setScrollSpeed(speed);
		break;
	}

	return 0;
}

static int glueSetScrollLimit(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -3));
	int top = static_cast<float>(lua_tointeger(lua, -2));
	int bottom = static_cast<float>(lua_tointeger(lua, -1));

	switch (obj->getType())
	{
	case SCROLL:
		ScrollPanel* panel = dynamic_cast<ScrollPanel*>(obj);
		panel->setScrollLimit(top, bottom);
		break;
	}

	return 0;
}

static int glueSetObjectToPanel(lua_State* lua)
{
	Object* panelObj = static_cast<Object*>(lua_touserdata(lua, -2));
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -1));

	switch (panelObj->getType())
	{
	case SCROLL:
	{
		ScrollPanel* panel = dynamic_cast<ScrollPanel*>(panelObj);
		panel->addObjectList(obj);
		break;
	}
	}

	return 0;
}