#pragma once

#include<iostream>
#include<vector>

#include"Enemy.h"

class EnemyGroup:public GameEntity
{
private:
	bool clear;

	std::string luaPath;

	int bulletLimit;

	int hp;
	float posX, posY;
	float speedX, speedY;

	std::vector<Enemy*> enemys;
	BulletInfo bulletInfo;
	int delayFrame;
	int currentFrame;

	SDL_Texture* texture;

public:

	EnemyGroup();
	~EnemyGroup() override;

	void setHP(int hp);
	void setBulletLimit(int limit);
	void setBulletStatus(float dirX, float dirY, float speed, float width, float height, SDL_Color color, float rate);
	void setLuaScript(std::string updateScriptPath);
	void setInitPos(float x, float y);
	void setSpeed(float speedX,float speedY);
	void setDelayFrame(int delayFrame);
	void setImage(SDL_Texture* texture) override;
	void setGroupEnemyCount(int count);

	void initFrameSettings() override;

	void Update();
	void hitCheck(Player* player);
	void draw(SDL_Renderer* gRenderer);

	bool clearCheck();
};

class EnemyWave
{
private:
	bool clear;

	int currentGroupNumber;
	std::vector<EnemyGroup*> enemyGroups;
public:

	EnemyWave();
	~EnemyWave();

	EnemyGroup* addEnemyGroup();

	void initFrameSettings();

	bool clearCheck();

	void Update();
	void hitCheck(Player* player);
	void draw(SDL_Renderer* gRenderer);
};