#pragma once
#include"GameEntity.h"
#include"Mouse.h"
#include"Bullet.h"

#include<time.h>
#include<cmath>

class GameManager;

const int bulletLimit = 100;

class Player:public GameEntity
{
private:
	static Player* instance;
	Player();

	Mouse* mouseInstance;

	float crashTime, crashDisplayTime;
	SDL_Texture* crashTexture;

	int hp;
	bool damaged;
	float damagedTime;
	float noDamagedTime;

	int offSetX, offSetY;
	int bulletOffsetX,bulletOffsetY;

	float shotTime;
	std::vector<std::shared_ptr<Bullet>> bullets;

	BulletInfo bulletInfo;

public:

	static Player* GetInstance()
	{
		if (!instance)
		{
			instance = new Player();
		}

		return instance;
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
	void addBulletDir(float x, float y);
	void setBulletSpeed(float speed);
	void setBulletTexture(SDL_Texture* tex, float texScale);
	void setBulletRate(float rate);
	void setBulletReflect(bool reflect, int count);

	std::shared_ptr<Bullet>* getBulletData();

	void damage();
	bool gameOver();
	bool isCrash();

	void Update() override;
	void initFrameSettings();

	void drawObjects(SDL_Renderer* gRenderer) override;
};