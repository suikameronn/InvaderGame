#pragma once
#include"Scene.h"
#include"Mouse.h"

#include"Player.h"
#include"EnemyWaveGroup.h"

class MainGame :public Scene
{
private:
	Player* player;

	lua_State* lua;

	std::vector<SDL_Texture*> textures;

	int currentWaveIndex;
	std::vector<EnemyWave*> enemyWaves;

	int nextScene;

	void initLuaScript(std::string stageLuaFilePath);
	void luaFunctionRegister();
	void luaImageNumberRegister();

	void nextWave();

public:
	MainGame(std::string stageLuaFilePath,std::vector<SDL_Surface*>& images,SDL_Renderer* gRenderer);
	~MainGame() override;

	EnemyWave* createEnemyWaves();

	SDL_Texture* getTexture(int number);

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
	}

	return 0;
}

static int glueSetBulletStatus(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -10));

	float dirX = static_cast<float>(lua_tonumber(lua, -9));
	float dirY = static_cast<float>(lua_tonumber(lua, -8));
	float speed = static_cast<float>(lua_tonumber(lua, -7));
	float width = static_cast<float>(lua_tonumber(lua, -6));
	float height = static_cast<float>(lua_tonumber(lua, -5));
	float r = static_cast<float>(lua_tonumber(lua, -4));
	float g = static_cast<float>(lua_tonumber(lua, -3));
	float b = static_cast<float>(lua_tonumber(lua, -2));
	float rate = static_cast<float>(lua_tonumber(lua, -1));

	SDL_Color color = SDL_Color(r, g, b);

	switch (entity->getType())
	{
	case ENEMY:
	{
		EnemyGroup* enemyGroup = dynamic_cast<EnemyGroup*>(entity);
		enemyGroup->setBulletStatus(dirX, dirY, speed,width,height,color,rate);
		break;
	}
	case PLAYER:
	{
		Player* player = dynamic_cast<Player*>(entity);
		player->bulletInfo.dirX = dirX;
		player->bulletInfo.dirY = dirY;
		player->bulletInfo.speed = speed;
		player->bulletInfo.width = width;
		player->bulletInfo.height = height;
		player->bulletInfo.color = color;
		player->bulletInfo.rate = rate;
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