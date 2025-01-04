#include"MainGame.h"

MainGame::MainGame(std::string stageLuaFilePath, std::vector<SDL_Surface*>& images, SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;
	this->nextScene = 0;
	this->currentWaveIndex = 0;

   	player = Player::GetInstance();

	textures.resize(images.size());
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i] = SDL_CreateTextureFromSurface(gRenderer, images[i]);
	}

	initLuaScript(stageLuaFilePath);
}

MainGame::~MainGame()
{
	//deleteˆ—‚ðs‚¤
	for (int i = 0; i < enemyWaves.size(); i++)
	{
		delete enemyWaves[i];
	}

	for (int i = 0; i < textures.size(); i++)
	{
		SDL_DestroyTexture(textures[i]);
	}

	player->Delete();
}

void MainGame::initLuaScript(std::string stageLuaFilePath)
{
	lua = luaL_newstate();
	luaL_openlibs(lua);

	luaFunctionRegister();
	luaImageNumberRegister();

	lua_pushlightuserdata(lua, this);
	lua_setglobal(lua, "MainGame");

	lua_pushlightuserdata(lua, player);
	lua_setglobal(lua, "Player");

	luaL_dofile(lua,stageLuaFilePath.c_str());

	initFrameSettings();
}

void MainGame::luaFunctionRegister()
{
	lua_register(lua, "startEnemySettings", startEnemySettings);
	lua_register(lua, "glueAddEnemyGroup", glueAddEnemyGroup);
	lua_register(lua, "glueSetLuaScript", glueSetLuaScript);
	lua_register(lua, "glueSetInitPos", glueSetInitPos);
	lua_register(lua, "glueSetDelayFrame", glueSetDelayFrame);
	lua_register(lua, "glueSetImage", glueSetImage);
	lua_register(lua, "glueSetEnemyCount", glueSetEnemyCount);
	lua_register(lua, "glueSetSpeed", glueSetSpeed);
	lua_register(lua, "glueSetTexScale", glueSetTexScale);
	lua_register(lua, "glueSetHP", glueSetHP);
	lua_register(lua, "glueSetBulletStatus", glueSetBulletStatus);
	lua_register(lua, "glueSetBulletLimit", glueSetBulletLimit);
}

void MainGame::luaImageNumberRegister()
{
	lua_pushinteger(lua, 0);
	lua_setglobal(lua, "NormalEnemy");
	lua_pushinteger(lua, 1);
	lua_setglobal(lua, "BossEnemy");
}

EnemyWave* MainGame::createEnemyWaves()
{
	EnemyWave* wave = new EnemyWave();
	enemyWaves.push_back(wave);

	return wave;
}

SDL_Texture* MainGame::getTexture(int number)
{
	return textures[number];
}

void MainGame::nextWave()
{
	currentWaveIndex++;
	if (currentWaveIndex >= enemyWaves.size())
	{
		nextScene = 2;
	}
}

int MainGame::Update_Scene()
{
	enemyWaves[currentWaveIndex]->Update();

	player->Update();

	hitCheckScene();

	drawScene();

	Mouse::GetInstance()->setMouseState();
	if (Mouse::GetInstance()->quit)
	{
		return -10;
	}

	if (enemyWaves[currentWaveIndex]->clearCheck())
	{
		nextWave();
	}

	return nextScene;
}

void MainGame::hitCheckScene()
{
	enemyWaves[currentWaveIndex]->hitCheck(player);
}

void MainGame::initFrameSettings()
{
	player->initFrameSettings();

	for (auto itr = enemyWaves.begin(); itr != enemyWaves.end(); itr++)
	{
		(*itr)->initFrameSettings();
	}
}

void MainGame::drawScene()
{
	enemyWaves[currentWaveIndex]->draw(gRenderer);

	player->drawObjects(gRenderer);
}