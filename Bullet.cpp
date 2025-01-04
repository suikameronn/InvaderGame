#include"Bullet.h"

Bullet::Bullet(BulletInfo info)
{
	this->visible = false;
	this->restart = true;

	this->dirX = info.dirX;
	this->dirY = info.dirY;
	this->speed = info.speed;
	this->width = info.width;
	this->height = info.height;
	this->color = info.color;
}

bool Bullet::isRestart()
{
	return restart;
}

void Bullet::shoot(float x,float y)
{
	visible = true;
	restart = false;

	pos->x = x;
	pos->y = y;
}

void Bullet::initFrameSettings()
{

}

void Bullet::Update()
{
	if (!restart)
	{
		setPos(pos->x + dirX * speed, pos->y + dirY * speed);
	}
}

void Bullet::drawObjects(SDL_Renderer* gRenderer)
{
	if (isVisible())
	{
		SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
		SDL_Rect rect = { pos->x,pos->y , width, height };
		SDL_RenderFillRect(gRenderer, &rect);
	}
}

CollisionBox& Bullet::getCollisionBox()
{
	collisionBox.center.x = pos->x + (width / 2);
	collisionBox.center.y = pos->y + (height / 2);
	collisionBox.rightDown.x = pos->x + width;
	collisionBox.rightDown.y = pos->y + height;

	return collisionBox;
}

void Bullet::restartCheck()
{
	if (pos->x < 0.0 || (pos->x + texWidth) > SCREEN_WIDTH
		|| pos->y < 0.0 || pos->y + texHeight > SCREEN_HEIGHT)
	{
		Restart();
	}
}

void Bullet::Restart()
{
	visible = false;
	restart = true;

	pos->x = -FLT_MAX;
	pos->y = -FLT_MAX;
}