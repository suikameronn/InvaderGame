#pragma once
#include"GameEntity.h"
#include"Mouse.h"
#include"Bullet.h"

#include<time.h>
#include<cmath>

class GameManager;

class Player:public GameEntity
{
private:
	static Player* instance;
	Player();

	Mouse* mouseInstance;

	float crashTime, crashDisplayTime;
	SDL_Texture* crashTexture;

	int bulletLimit;
	int hp;
	bool damaged;
	float damagedTime;
	float noDamagedTime;

	int offSetX, offSetY;

	float shotTime;
	std::vector<std::shared_ptr<Bullet>> bullets;

public:

	BulletInfo bulletInfo;

	static Player* GetInstance()
	{
		if (instance)
		{
			return instance;
		}
		else
		{
			instance = new Player();
		}
	}

	static void Delete()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	~Player() {};

	void setHP(int hp);
	void setBulletLimit(int limit);
	int getBulletLimit();

	std::shared_ptr<Bullet>* getBulletData();

	void damage();
	bool gameOver();
	bool isCrash();

	void Update() override;
	void initFrameSettings();

	void drawObjects(SDL_Renderer* gRenderer) override;
};