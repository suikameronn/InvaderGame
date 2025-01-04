#pragma once

#include"GameEntity.h"

class Bullet:public GameEntity
{
private:
	bool restart;

	float dirX, dirY;
	float speed;

	float width, height;

	SDL_Color color;

public:
	Bullet(BulletInfo info);

	bool isRestart();
	void shoot(float x, float y);

	void initFrameSettings() override;
	void Update() override;

	void drawObjects(SDL_Renderer* gRenderer) override;

	CollisionBox& getCollisionBox() override;

	void restartCheck();
	void Restart();
};