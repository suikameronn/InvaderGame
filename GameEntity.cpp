#include"GameEntity.h"

GameEntity::GameEntity()
{
	texScale = 1.0f;
	visible = true;
}

void GameEntity::setImage(SDL_Texture* texture)
{
	this->texture = texture;
}

void GameEntity::setMove(float px, float py)
{
	actSet = true;

	if (speedX < 0.0f)
	{
		speedX *= -1.0f;
	}
	if (speedY < 0.0f)
	{
		speedY *= -1.0f;
	}

	distPosX = px;
	distPosY = py;

	if (distPosX - pos->x < 0.0f)
	{
		speedX *= -1.0f;
	}
	if (distPosY - pos->y < 0.0f)
	{
		speedY *= -1.0f;
	}
}

bool GameEntity::actMove()
{
	if (actSet)
	{
		float moveX, moveY;

		if (abs(distPosX - pos->x) < abs(speedX))
		{
			moveX = 0;
		}
		else
		{
			moveX = speedX;
		}
		if (abs(distPosY - pos->y) < abs(speedY))
		{
			moveY = 0;
		}
		else
		{
			moveY = speedY;
		}

		setPos(pos->x + moveX, pos->y + moveY);

		if (moveX == 0.0f && moveY == 0.0f)
		{
			actSet = false;
			return true;
		}

		return false;
	}

	return true;
}

void GameEntity::setTexScale(float texScale)
{
	this->texScale = texScale;
}

CollisionBox& GameEntity::getCollisionBox()
{
	return collisionBox;
}

bool GameEntity::hitCheck(CollisionBox& oppCollisionBox)
{
	return collisionBox.collisionCheck(oppCollisionBox);
}

void GameEntity::drawObjects(SDL_Renderer* gRenderer)
{
	if (!visible)
	{
		return;
	}

	luaUpdate = actMove();

	renderQuad = { (int)pos->x, (int)pos->y,
		static_cast<int>(texWidth), static_cast<int>(texHeight)};

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, texture, clip, &renderQuad, angle, center, flip);
}