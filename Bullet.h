#pragma once

#include"GameEntity.h"

class Bullet:public GameEntity
{
private:
	int index;
	bool restart;

	int reflected;

	float dirX;
	float dirY;

	float cosDeg,cosRad;

	BulletInfo info;

public:
	Bullet(int index,BulletInfo info);

	bool isRestart();
	void shoot(int index,float x, float y);

	void initFrameSettings() override;
	void Update() override;

	void drawObjects(SDL_Renderer* gRenderer) override;

	void restartCheck();
	void Restart();
};