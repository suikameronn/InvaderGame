#pragma once
#include"Scene.h"

#include"Object.h"
#include"Text.h"
#include"Button.h"
#include"ScrollPanel.h"

class MenuScene :public Scene
{
protected:
	lua_State* lua;
	
	int frameCount = 0;

	vector<TTF_Font*> fonts;

	unordered_map<string, shared_ptr<Object>> objList;

	unordered_map<string, shared_ptr<Object>, less<>> drawList;

	map<int, Object*> actTimer;

public:
	MenuScene();
	MenuScene(vector<TTF_Font*> fonts, SDL_Renderer* gRenderer);

	~MenuScene() override {};

	void luaFunctionRegister();
	void luaNumberRegister();

	TTF_Font* getFont(FONTS font);

	void addObjectToScene(Text* text, string objName);
	void addObjectToScene(Button* button, string objName);
	void addObjectToScene(ScrollPanel* button, string objName);

	std::shared_ptr<Object> accessObject(std::string objName, OBJECT& obj);

	void hitCheckScene() override;
	void drawScene() override;

	int Update_Scene() override;
};

static int glueCreateText(lua_State* lua)
{
	Text* text = new Text();
	lua_pushlightuserdata(lua, text);

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

	lua_getglobal(lua, "MenuScene");
	MenuScene* menu = static_cast<MenuScene*>(lua_touserdata(lua, -1));

	switch (obj->getType())
	{
	case TEXT:
	{
		Text* text = dynamic_cast<Text*>(obj);
		text->setFont(menu->getFont(font));
		break;
	}
	case BUTTON:
	{
		Button* button = dynamic_cast<Button*>(obj);
		Text* text = button->getLabel();
		text->setFont(menu->getFont(font));
		break;
	}
	}

	return 0;
}

static int glueSetLabelTextSize(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -2));
	int size = static_cast<int>(lua_tonumber(lua, -1));

	switch(obj->getType())
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
	int x = static_cast<int>(lua_tonumber(lua, -2));
	int y = static_cast<int>(lua_tonumber(lua, -1));

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

static int glueSetNextScene(lua_State* lua)
{
	Object* obj = static_cast<Object*>(lua_touserdata(lua, -2));
	int nextScene = static_cast<int>(lua_tonumber(lua, -1));

	lua_getglobal(lua, "MenuScene");
	MenuScene* menu = static_cast<MenuScene*>(lua_touserdata(lua, -1));

	switch (obj->getType())
	{
	case BUTTON:
	{
		Button* button = dynamic_cast<Button*>(obj);
		std::function<void()> eventFunction = [=]() {menu->changeScene(nextScene); };
		button->setNextScene(eventFunction);
		break;
	}
	}

	return 0;
}