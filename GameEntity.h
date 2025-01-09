#pragma once
#include"Object.h"

struct BulletInfo
{
	bool reflect;
	int reflectCount;
	std::vector<float> dirX;
	std::vector<float> dirY;
	float speed;
	float width;
	float height;
	float rate;
	std::vector<SDL_Color> colors;

	void addBulletDir(float x, float y)
	{
		dirX.push_back(x);
		dirY.push_back(y);
	}
};

struct CollisionBox
{
	float lx, ly;
	float rx, ry;
};

class GameEntity : public Object
{
protected:

	lua_State* lua;
	lua_State* coroutine;
	lua_State* from;
	int imageNum;

	SDL_Texture* texture;
	int texWidth, texHeight;
	float texScale;

	SDL_Rect renderQuad;
	SDL_Rect* clip;
	SDL_Point* center = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double angle = 0;

	float speedX, speedY;
	float distPosX, distPosY;

	CollisionBox collisionBox;

public:

	GameEntity();
	~GameEntity() override {};

	bool luaUpdate;

	virtual void luaFunctionRegister() {}

	void setTexScale(float texScale);
	virtual void setImage(SDL_Texture* texture);

	void setMove(float x, float y) override;
	bool actMove() override;

	virtual void initFrameSettings() = 0;

	void drawObjects(SDL_Renderer* gRenderer) override;

	virtual void calcCollisionBox();
	CollisionBox& getCollisionBox();
	virtual bool hitCheck(const CollisionBox& oppCollisionBox);
	virtual void hittedAction(OBJECT opponentType) {};
};

static int glueSetMove(lua_State* lua)
{
	GameEntity* entity = static_cast<GameEntity*>(lua_touserdata(lua, -3));

	float distPosX = static_cast<float>(lua_tonumber(lua, -2));
	float distPosY = static_cast<float>(lua_tonumber(lua, -1));

	entity->setMove(distPosX, distPosY);

	return 0;
}