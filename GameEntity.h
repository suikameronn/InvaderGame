#pragma once
#include"Object.h"

#include<array>

struct BulletInfo
{
	bool reflect;
	int reflectCount;
	std::vector<float> dirX;
	std::vector<float> dirY;
	float speed;
	float rate;
	float texScale;
	SDL_Texture* texture;

	void addBulletDir(float x, float y)
	{
		dirX.push_back(x);
		dirY.push_back(y);
	}
};

struct CollisionBox
{
	std::array<float, 4> vx;
	std::array<float, 4> vy;

	void getCollisionBoxCoords(float& left, float& top, float& bottom, float& right)
	{
		left = vx[0];
		top = vy[0];
		bottom = vy[1];
		right = vx[1];
	}

	void calcCollisionBox(float lx, float ly, float rx, float ry, float rad)
	{

		float centerX = (lx + rx) / 2.0f;
		float centerY = (ly + ry) / 2.0f;

		lx -= centerX;
		ly -= centerY;
		rx -= centerX;
		ry -= centerY;

		lx = lx * cos(rad) - ly * sin(rad);
		ly = lx * sin(rad) + ly * cos(rad);
		rx = rx * cos(rad) - ry * sin(rad);
		ry = rx * sin(rad) + ry * cos(rad);

		lx += centerX;
		ly += centerY;
		rx += centerX;
		ry += centerY;

		vx[0] = lx;
		vx[1] = rx;
		vx[2] = rx;
		vx[3] = lx;

		vy[0] = ly;
		vy[1] = ly;
		vy[2] = ry;
		vy[3] = ry;
	}

	void calcCollisionBox(float lx, float ly, float rx, float ry)
	{
		vx[0] = lx;
		vx[1] = rx;
		vx[2] = rx;
		vx[3] = lx;

		vy[0] = ly;
		vy[1] = ly;
		vy[2] = ry;
		vy[3] = ry;
	}

	std::array<float, 2> minusVector(std::array<float, 2> a, std::array<float, 2> b)
	{
		return { a[0] - b[0],a[1] - b[1] };
	}

	std::array<float, 2> getNormalVector(std::array<float, 2> v)
	{
		return { v[1],v[0] * -1.0f };
	}

	std::array<float, 2> getProjection(std::array<float, 2> vector)
	{
		float min = vx[0] * vector[0] + vy[0] * vector[1];
		float max = min;

		for (int i = 1; i < 4; i++)
		{
			float dot = vx[i] * vector[0] + vy[i] * vector[1];
			if (dot < min)
			{
				min = dot;
			}
			else if (dot > max)
			{
				max = dot;
			}
		}

		return { min,max };
	}

	bool collisionCheck(CollisionBox& opponent)
	{
		std::array<std::array<float, 2>, 8> normals;
		std::array<float, 2> vector1, vector2;
		for (int i = 0; i < 4; i++)
		{
			vector1[0] = vx[i];
			vector1[1] = vy[i];
			if (i == 3)
			{
				vector2[0] = vx[0];
				vector2[1] = vy[0];
			}
			else
			{
				vector2[0] = vx[i + 1];
				vector2[1] = vy[i + 1];
			}

			normals[i] = getNormalVector(minusVector(vector2, vector1));
		}

		for (int i = 0; i < 4; i++)
		{
			vector1[0] = opponent.vx[i];
			vector1[1] = opponent.vy[i];
			if (i == 3)
			{
				vector2[0] = opponent.vx[0];
				vector2[1] = opponent.vy[0];
			}
			else
			{
				vector2[0] = opponent.vx[i + 1];
				vector2[1] = opponent.vy[i + 1];
			}

			normals[i + 4] = getNormalVector(minusVector(vector2, vector1));
		}

		std::array<float, 2> dotResults, dotResults2;
		for (int i = 0; i < 8; i++)
		{
			dotResults = getProjection(normals[i]);
			dotResults2 = opponent.getProjection(normals[i]);

			if (!((dotResults[0] <= dotResults2[0] && dotResults2[0] <= dotResults[1])
				|| (dotResults2[0] <= dotResults[0] && dotResults[0] <= dotResults2[1])))
			{
				return false;
			}
		}

		return true;
	}
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

	CollisionBox& getCollisionBox();
	virtual bool hitCheck(CollisionBox& oppCollisionBox);
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