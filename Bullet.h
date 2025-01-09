#pragma once

#include"GameEntity.h"

class Bullet:public GameEntity
{
private:
	bool restart;

	int reflected;

	float dirX;
	float dirY;


	BulletInfo info;

	bool borderCheck();

public:
	Bullet(BulletInfo info);

	bool isRestart();
	void shoot(float x, float y);

	void initFrameSettings() override;
	void Update() override;

	void drawObjects(SDL_Renderer* gRenderer) override;

	void calcCollisionBox() override;

	void restartCheck();
	void Restart();
};