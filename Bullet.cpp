#include"Bullet.h"

Bullet::Bullet(BulletInfo info)
{
	this->visible = false;
	this->restart = true;

	this->info = info;
	this->reflected = 0;

	this->dirX = info.dirX;
	this->dirY = info.dirY;

	this->pos->x = FLT_MAX;
	this->pos->y = FLT_MAX;

	calcCollisionBox();
}

bool Bullet::isRestart()
{
	return restart;
}

void Bullet::shoot(int index,float x,float y)
{
	visible = true;
	restart = false;

	pos->x = x;
	pos->y = y;

	reflected = 0;
	dirX = info.dirX[index];
	dirY = info.dirY[index];
}

void Bullet::initFrameSettings()
{

}

void Bullet::Update()
{
	if (!restart)
	{
		setPos(pos->x + dirX * info.speed, pos->y + dirY * info.speed);
		calcCollisionBox();
	}
}

void Bullet::drawObjects(SDL_Renderer* gRenderer)
{
	if (isVisible())
	{
		SDL_SetRenderDrawColor(gRenderer, info.color.r, info.color.g, info.color.b, info.color.a);
		SDL_Rect rect = { pos->x,pos->y , info.width, info.height };
		SDL_RenderFillRect(gRenderer, &rect);
	}
}

void Bullet::calcCollisionBox()
{
	collisionBox.lx = pos->x;
	collisionBox.ly = pos->y;
	collisionBox.rx = pos->x + info.width;
	collisionBox.ry = pos->y + info.height;
}

void Bullet::restartCheck()
{
	if (pos->x < 0.0 || (pos->x + info.width) > SCREEN_WIDTH
		|| pos->y < 0.0 || pos->y + info.height > SCREEN_HEIGHT)
	{
		if (reflected >= info.reflectCount)
		{
			Restart();
		}
		else
		{
			dirX *= -1;
			dirY *= -1;
			reflected++;
		}
	}
}

void Bullet::Restart()
{
	visible = false;
	restart = true;

	pos->x = FLT_MAX;
	pos->y = FLT_MAX;

	calcCollisionBox();
}