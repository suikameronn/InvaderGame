#pragma once
#include"GameEntity.h"
#include"Mouse.h"
#include"Bullet.h"

#include<time.h>

class Player:public GameEntity
{
private:
	static Player* instance;
	Player();

	Mouse* mouseInstance;

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

	void setBulletLimit(int limit);
	int getBulletLimit();

	std::shared_ptr<Bullet>* getBulletData();

	void damage();

	void Update() override;
	void initFrameSettings();

	void drawObjects(SDL_Renderer* gRenderer) override;
};