#include"GameManager.h"

#include"Scene.h"

Scene::Scene()
{
	gRenderer = GameManager::GetInstance()->getRenderer();
}

void Scene::changeScene(int nextSceneNum,std::string path)
{
	this->nextSceneNum = nextSceneNum;
	this->nextLuaPath = path;
}

void Scene::luaFunctionRegister()
{
	lua_register(lua, "glueCreateText", glueCreateText);
	lua_register(lua, "glueCreateButton", glueCreateButton);
	lua_register(lua, "glueCreateScrollPanel", glueCreateScrollPanel);
	lua_register(lua, "glueCreateTextToPanel", glueCreateTextToPanel);
	lua_register(lua, "glueCreateButtonToPanel", glueCreateButtonToPanel);
	lua_register(lua, "glueSetPos", glueSetPos);
	lua_register(lua, "glueSetOffset", glueSetOffset);
	lua_register(lua, "glueSetColor", glueSetColor);
	lua_register(lua, "glueSetText", glueSetText);
	lua_register(lua, "glueSetFont", glueSetFont);
	lua_register(lua, "glueSetLabelTextSize", glueSetLabelTextSize);
	lua_register(lua, "glueSetLabelOffset", glueSetLabelOffset);
	lua_register(lua, "glueSetLabelColor", glueSetLabelColor);
	lua_register(lua, "glueSetNextScene", glueSetNextScene);
	lua_register(lua, "glueSetPanelSize", glueSetPanelSize);
	lua_register(lua, "glueSetScrollSpeed", glueSetScrollSpeed);
	lua_register(lua, "glueSetScrollLimit", glueSetScrollLimit);
	lua_register(lua, "glueSetObjectToPanel", glueSetObjectToPanel);
}

void Scene::luaNumberRegister()
{
	lua_pushinteger(lua, 0);
	lua_setglobal(lua, "Small");

	lua_pushinteger(lua, 1);
	lua_setglobal(lua, "Normal");

	lua_pushinteger(lua, 2);
	lua_setglobal(lua, "Big");
}

void Scene::addObject(std::shared_ptr<Object> obj)
{
	objList.push_back(obj);
}

TTF_Font* Scene::getFont(FONTS font)
{
	return GameManager::GetInstance()->getFont(font);
}

int Scene::startSound(SoundNumber num, bool loop)
{
	return GameManager::GetInstance()->startSound(num, loop);
}