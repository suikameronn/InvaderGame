#pragma once
#include"Scene.h"
#include"Mouse.h"

#include"Player.h"
#include"EnemyWaveGroup.h"

#if _DEBUG
	#include<chrono>
#endif

class GamaManager;

class MainGame :public Scene
{
private:
#if _DEBUG
	int collisionCount;
#endif

	Player* player;
	bool playerCrash;

	lua_State* lua;

	float backSpaceHeight;
	int backSpaceTextureHeight;
	SDL_Rect sourceRect;
	SDL_Rect dstRect;
	SDL_Texture* backSpaceTexture;
	
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Texture*> bulletTextures;

	bool waveTextVisible;
	float waveTextVisibleTime;
	int currentWaveIndex;
	std::vector<EnemyWave*> enemyWaves;
	Text* waveText;

	int nextScene;

	void initLuaScript(std::string stageLuaFilePath);
	void luaFunctionRegister();
	void luaImageNumberRegister();

	void nextWave();

public:
	MainGame(std::string stageLuaFilePath);
	~MainGame() override;

	EnemyWave* createEnemyWaves();

	SDL_Texture* getTexture(int number);
	SDL_Texture* getBulletTexture(int number);

	void drawSpace();

	void initFrameSettings();

	int Update_Scene() override;
	void hitCheckScene() override;
	void drawScene() override;
};

static int startEnemySettings(lua_State* lua)
{
	lua_getglobal(lua, "MainGame");
	MainGame* mainGame = static_cast<MainGame*>(lua_touserdata(lua, -1));
	EnemyWave* wave = mainGame->createEnemyWaves();

	lua_pushlightuserdata(lua, wave);

	return 1;
}

static int glueAddEnemyGroup(lua_State* lua)
{
	EnemyWave* wave = static_cast<EnemyWave*>(lua_touserdata(lua, -1));
	EnemyGroup* group = wave->addEnemyGroup();

	lua_pushlightuserdata(lua, group);

	return 1;
}

static int glueSetLuaScript(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -2));
	std::string luaPath = std::string(lua_tostring(lua, -1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setLuaScript(luaPath);
		break;
	}
	default:
		break;
	}

	return 0;
}

static int glueSetInitPos(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -3));
	float x = static_cast<float>(lua_tonumber(lua, -2));
	float y = static_cast<float>(lua_tonumber(lua, -1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setInitPos(x, y);
		break;
	}
	default:
		break;
	}

	return 0;
}

static int glueSetSpeed(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -3));
	float speedX = static_cast<float>(lua_tonumber(lua,-2));
	float speedY = static_cast<float>(lua_tonumber(lua,-1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setSpeed(speedX, speedY);
		break;
	}
	default:
		break;
	}

	return 0;
}

static int glueSetDelayFrame(lua_State* lua)
{
	EnemyGroup* enemyGroup = static_cast<EnemyGroup*>(lua_touserdata(lua, -2));
	float delayFrame = lua_tonumber(lua, -1);

	enemyGroup->setDelayFrame(delayFrame);

	return 0;
}

static int glueSetImage(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -2));
	int imageNum = static_cast<int>(lua_tointeger(lua, -1));

	lua_getglobal(lua, "MainGame");
	MainGame* mainGame = static_cast<MainGame*>(lua_touserdata(lua, -1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setImage(mainGame->getTexture(imageNum));
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->setImage(mainGame->getTexture(imageNum));
		break;
	}
	}

	return 0;
}

static int glueSetTexScale(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -2));
	float texScale = static_cast<float>(lua_tonumber(lua, -1));

	entity->setTexScale(texScale);

	return 0;
}

static int glueSetEnemyCount(lua_State* lua)
{
	EnemyGroup* group = static_cast<EnemyGroup*>(lua_touserdata(lua, -2));
	int enemyCount = lua_tointeger(lua, -1);

	group->setGroupEnemyCount(enemyCount);

	return 0;
}

static int glueSetHP(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -2));
	int hp = static_cast<int>(lua_tointeger(lua, -1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setHP(hp);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->setHP(hp);
	}
	}

	return 0;
}

static int glueAddBulletDir(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -3));
	float dirX = static_cast<float>(lua_tonumber(lua, -2));
	float dirY = static_cast<float>(lua_tonumber(lua, -1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->addBulletDir(dirX,dirY);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->addBulletDir(dirX, dirY);
		break;
	}
	}

	return 0;
}

static int glueSetBulletSpeed(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -2));
	float speed = static_cast<float>(lua_tonumber(lua, -1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setBulletSpeed(speed);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->setBulletSpeed(speed);
		break;
	}
	}

	return 0;
}

static int glueSetBulletTexture(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -3));
	int bulletTexNum = static_cast<int>(lua_tonumber(lua, -2));
	float texScale = static_cast<float>(lua_tonumber(lua, -1));

	lua_getglobal(lua, "MainGame");
	MainGame* mainGame = static_cast<MainGame*>(lua_touserdata(lua, -1));

	SDL_Texture* tex = mainGame->getBulletTexture(bulletTexNum);

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setBulletTexture(tex,texScale);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->setBulletTexture(tex,texScale);
		break;
	}
	}

	return 0;
}

static int glueSetBulletRate(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -2));
	float rate = static_cast<float>(lua_tonumber(lua, -1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setBulletRate(rate);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->setBulletRate(rate);
		break;
	}
	}

	return 0;
}

static int glueSetBulletReflect(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -3));

	bool reflect = static_cast<bool>(lua_toboolean(lua, -2));
	int reflectCount = static_cast<int>(lua_tointeger(lua, -1));

	switch(entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setBulletReflect(reflect,reflectCount);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->setBulletReflect(reflect, reflectCount);
		break;
	}
	}

	return 0;
}