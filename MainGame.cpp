#include"GameManager.h"

#include"MainGame.h"

MainGame::MainGame(std::string stageLuaFilePath)
{
	GameManager* manager = GameManager::GetInstance();

	this->gRenderer = manager->getRenderer();
	this->nextScene = 0;
	this->currentWaveIndex = 0;
	this->fonts = fonts;

	dstRect = SDL_Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

   	player = Player::GetInstance();
	playerCrash = false;

	textures.push_back(SDL_CreateTextureFromSurface(gRenderer, manager->getImages(0)));
	textures.push_back(SDL_CreateTextureFromSurface(gRenderer, manager->getImages(1)));

	backSpaceTexture = SDL_CreateTextureFromSurface(gRenderer, manager->getImages(2));
	backSpaceTextureHeight = manager->getImages(2)->h;

	initLuaScript(stageLuaFilePath);

	waveTextVisible = true;
	waveText = new Text();
	waveText->setFont(GameManager::GetInstance()->getFont(FONTS::BIG));
	waveText->setText("WAVE1");
	waveText->setPos(155, 150);
	waveText->setColor(255, 255, 255);
	waveText->setDisappear(0.4f, 3);
}

MainGame::~MainGame()
{
	//deleteˆ—‚ğs‚¤
	for (int i = 0; i < enemyWaves.size(); i++)
	{
		delete enemyWaves[i];
	}

	for (int i = 0; i < textures.size(); i++)
	{
		SDL_DestroyTexture(textures[i]);
	}

	if (waveText)
	{
		delete waveText;
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
	lua_register(lua, "glueAddBulletDir", glueAddBulletDir);
	lua_register(lua, "glueSetBulletSpeed", glueSetBulletSpeed);
	lua_register(lua, "glueSetBulletSize", glueSetBulletSize);
	lua_register(lua, "glueSetBulletColor", glueSetBulletColor);
	lua_register(lua, "glueSetBulletRate", glueSetBulletRate);
	lua_register(lua, "glueSetBulletLimit", glueSetBulletLimit);
	lua_register(lua, "glueSetBulletReflect", glueSetBulletReflect);
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
	waveTextVisible = true;
	waveTextVisibleTime = clock();

	currentWaveIndex++;
	waveText->setText("WAVE" + std::to_string(currentWaveIndex + 1));
	waveText->setDisappear(0.4f, 3);

	if (currentWaveIndex >= enemyWaves.size())
	{
		nextScene = 1;
		nextLuaPath = "luaScript/Clear.lua";
	}
}

int MainGame::Update_Scene()
{
	backSpaceHeight += 0.05f;
	if (SCREEN_HEIGHT + backSpaceHeight > backSpaceTextureHeight)
	{
		backSpaceHeight = 0;
	}

	if (!player->isCrash())
	{
		player->Update();
	}
	else
	{
		if (player->gameOver())
		{
			nextScene = 1;
			nextLuaPath = "LuaScript/GameOver.lua";
		}
	}

	if (!waveTextVisible)
	{
		enemyWaves[currentWaveIndex]->Update();

		hitCheckScene();
	}
	else
	{
		waveText->Update();

		if ((clock() - waveTextVisibleTime) / CLOCKS_PER_SEC > 2.0f)
		{
			waveTextVisible = false;
		}
	}

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
	waveTextVisibleTime = clock();

	player->initFrameSettings();

	for (auto itr = enemyWaves.begin(); itr != enemyWaves.end(); itr++)
	{
		(*itr)->initFrameSettings();
	}
}

void MainGame::drawSpace()
{
	sourceRect = { 0, (backSpaceTextureHeight - SCREEN_HEIGHT) - static_cast<int>(backSpaceHeight)
		,SCREEN_WIDTH, SCREEN_HEIGHT };

	//Render to screen
	SDL_RenderCopy(gRenderer, backSpaceTexture, &sourceRect,&dstRect);

}

void MainGame::drawScene()
{
	drawSpace();

	player->drawObjects(gRenderer);

	if (!waveTextVisible)
	{
		enemyWaves[currentWaveIndex]->draw(gRenderer);
	}
	else
	{
		waveText->drawObjects(gRenderer);
	}
}