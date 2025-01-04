#include"MenuScene.h"

MenuScene::MenuScene()
{
}

MenuScene::MenuScene(vector<TTF_Font*> fonts, SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;
	this->fonts = fonts;

	lua = luaL_newstate();
	luaL_openlibs(lua);

	lua_pushlightuserdata(lua, this);
	lua_setglobal(lua, "MenuScene");

	luaFunctionRegister();
	luaNumberRegister();

	luaL_dofile(lua, "luaScript/Title.lua");
}

void MenuScene::luaFunctionRegister()
{
	lua_register(lua, "glueCreateText", glueCreateText);
	lua_register(lua, "glueSetPos", glueSetPos);
	lua_register(lua, "glueSetColor", glueSetColor);
	lua_register(lua, "glueSetText", glueSetText);
	lua_register(lua, "glueSetFont", glueSetFont);
	lua_register(lua, "glueSetLabelTextSize", glueSetLabelTextSize);
	lua_register(lua, "glueSetLabelOffset", glueSetLabelOffset);
	lua_register(lua, "glueSetNextScene", glueSetNextScene);
}

void MenuScene::luaNumberRegister()
{
	lua_pushinteger(lua, 0);
	lua_setglobal(lua, "Normal");
	lua_pushinteger(lua, 1);
	lua_setglobal(lua, "Big");
}

TTF_Font* MenuScene::getFont(FONTS font)
{
	return fonts[static_cast<int>(font)];
}

void MenuScene::hitCheckScene()
{
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		if (itr->second->hitCheck())
		{
			//itr->second->l
		}
	}
}

void MenuScene::drawScene()
{
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		itr->second->drawObjects(gRenderer);
	}
}

int MenuScene::Update_Scene()
{
	return 0;
}

void MenuScene::addObjectToScene(Text* text, string objName)
{
	objList.insert(pair<string, unique_ptr<Object>>(objName, text));
}

void MenuScene::addObjectToScene(Button* button, string objName)
{
	objList.insert(pair<string, unique_ptr<Object>>(objName, button));
}

void MenuScene::addObjectToScene(ScrollPanel* scroll, string objName)
{
	objList.insert(pair<string, unique_ptr<Object>>(objName, scroll));
}

std::shared_ptr<Object> MenuScene::accessObject(std::string objName, OBJECT& obj)
{
	std::shared_ptr<Object> objPointer = objList[objName];
	obj = objPointer->getType();
	return objPointer;
}