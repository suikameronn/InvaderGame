#include"MenuScene.h"

MenuScene::MenuScene(std::string luaPath)
{
	lua = luaL_newstate();
	luaL_openlibs(lua);

	lua_pushlightuserdata(lua, this);
	lua_setglobal(lua, "Scene");

	luaFunctionRegister();
	luaNumberRegister();

	luaL_dofile(lua, luaPath.c_str());

	this->nextSceneNum = 0;
}

void MenuScene::hitCheckScene()
{
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		if ((*itr)->hitCheck())
		{
		}
	}
}

void MenuScene::drawScene()
{
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		(*itr)->drawObjects(gRenderer);
	}
}

int MenuScene::Update_Scene()
{
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		hitCheckScene();
	}

	drawScene();
	Mouse::GetInstance()->setMouseState();

	if (Mouse::GetInstance()->quit)
	{
		return -10;
	}

	return this->nextSceneNum;
}