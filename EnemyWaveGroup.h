#pragma once

#include<iostream>
#include<vector>

#include"Enemy.h"

class EnemyGroup:public GameEntity
{
private:
	bool clear;

	std::string luaPath;

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
	void addBulletDir(float dirX, float dirY);
	void setBulletSpeed(float speed);
	void setBulletTexture(SDL_Texture* tex, float texScale);
	void setBulletRate(float rate);
	void setBulletReflect(bool reflect, int count);
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