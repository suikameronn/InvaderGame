#include"TestScene.h"

TestScene::TestScene(vector<TTF_Font*> fonts, SDL_Renderer* gRenderer)
{
	lua_State* pL = luaL_newstate();

	if (luaL_dofile(pL, "a.lua") != LUA_OK)
	{
		std::cout << "ƒGƒ‰[‚ð“f‚«o‚·" << std::endl;
	}


}

int TestScene::Update_Scene()
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