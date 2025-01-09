#pragma once
#include"Scene.h"
#include"Mouse.h"

#include"Player.h"
#include"EnemyWaveGroup.h"

class GamaManager;

class MainGame :public Scene
{
private:
	Player* player;
	bool playerCrash;

	lua_State* lua;

	float backSpaceHeight;
	int backSpaceTextureHeight;
	SDL_Rect sourceRect;
	SDL_Rect dstRect;
	SDL_Texture* backSpaceTexture;
	
	std::vector<SDL_Texture*> textures;

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
		enemyGroup->addBulletDir(dirX, dirY);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->bulletInfo.dirX.push_back(dirX);
		player->bulletInfo.dirY.push_back(dirY);
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
		player->bulletInfo.speed = speed;
		break;
	}
	}

	return 0;
}

static int glueSetBulletSize(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -3));
	float width = static_cast<float>(lua_tonumber(lua, -2));
	float height = static_cast<float>(lua_tonumber(lua, -1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setBulletSize(width,height);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->bulletInfo.width = width;
		player->bulletInfo.height = height;
		break;
	}
	}

	return 0;
}

static int glueSetBulletColor(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -4));

	float r = static_cast<float>(lua_tonumber(lua, -3));
	float g = static_cast<float>(lua_tonumber(lua, -2));
	float b = static_cast<float>(lua_tonumber(lua, -1));
	SDL_Color color = SDL_Color(r, g, b);

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->addBulletColor(color);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->bulletInfo.colors.push_back(color);
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
		player->bulletInfo.rate = rate;
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
		player->bulletInfo.reflect = reflect;
		player->bulletInfo.reflectCount = reflectCount;
		break;
	}
	}

	return 0;
}

static int glueSetBulletLimit(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -2));
	int limit = static_cast<int>(lua_tonumber(lua, -1));

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setBulletLimit(limit);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->setBulletLimit(limit);
		break;
	}
	}

	return 0;
}