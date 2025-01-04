#pragma once

#include"GameEntity.h"
#include"EnumList.h"

#include"Bullet.h"

#include"Player.h"

class GameManager;

class Enemy : public GameEntity
{
private:
	bool crash;
	float crashTime, crashDisplayTime;
	SDL_Texture* crashTexture;

	int hp;
	BulletInfo bulletInfo;

	std::vector<std::shared_ptr<Bullet>> bullets;

	void luaFunctionRegister() override;

	void defeat();

public:

	Enemy();
	~Enemy();

	bool isCrash();

	std::shared_ptr<Bullet>* getBulletData();

	void setLuaScript(std::string luaFilePath);
	void initFrameSettings(int bulletLimit,int hp, float posX, float posY, float speedX, float speedY
		, float texScale, SDL_Texture* texture, BulletInfo bulletInfo);
	void initFrameSettings() override {};

	void Update() override;

	void damage();

	void drawObjects(SDL_Renderer* gRenderer) override;
};