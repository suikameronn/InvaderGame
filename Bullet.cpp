#include"Bullet.h"

Bullet::Bullet(int index,BulletInfo info)
{
	this->index = index;

	this->visible = false;
	this->restart = true;

	this->info = info;
	this->reflected = 0;

	this->dirX = info.dirX[index];
	this->dirY = info.dirY[index];

	this->cosRad = acos(dirX * 0.0f + dirY * 1.0f);
	this->cosDeg = cosRad * 180.0f / M_PI;
	float crossZ;
	crossZ = dirX * 1.0f - dirY * 0.0f;
	if (crossZ > 0.0f)
	{
		this->cosDeg *= -1.0f;
		this->cosRad *= -1.0f;
	}


	this->texture = info.texture;
	SDL_QueryTexture(this->texture, nullptr, nullptr, &texWidth, &texHeight);
	texWidth *= info.texScale;
	texHeight *= info.texScale;

	this->pos->x = FLT_MAX;
	this->pos->y = FLT_MAX;

	collisionBox.calcCollisionBox(pos->x, pos->y, pos->x + texWidth, pos->y + texHeight, cosRad);
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

	this->cosRad = acos(dirX * 0.0f + dirY * 1.0f);
	this->cosDeg = cosRad * 180.0f / M_PI;
	float crossZ;
	crossZ = dirX * 1.0f - dirY * 0.0f;
	if (crossZ > 0.0f)
	{
		this->cosDeg *= -1.0f;
		this->cosRad *= -1.0f;
	}
}

void Bullet::initFrameSettings()
{

}

void Bullet::Update()
{
	if (!restart)
	{
		setPos(pos->x + dirX * info.speed, pos->y + dirY * info.speed);
		collisionBox.calcCollisionBox(pos->x, pos->y, pos->x + texWidth, pos->y + texHeight, cosRad);
	}
}

void Bullet::drawObjects(SDL_Renderer* gRenderer)
{
	if (isVisible())
	{
		renderQuad = { (int)pos->x, (int)pos->y,static_cast<int>(texWidth), static_cast<int>(texHeight) };

		//Set clip rendering dimensions
		if (clip != nullptr)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyEx(gRenderer, texture, clip, &renderQuad, cosDeg , center, flip);
	}
}

void Bullet::restartCheck()
{
	if (pos->x < 0.0 || pos->x > SCREEN_WIDTH)
	{
		if (reflected >= info.reflectCount)
		{
			Restart();
		}
		else
		{
			reflected++;
			dirX *= -1.0f;
			cosDeg *= -1.0f;
			cosRad *= -1.0f;
		}
	}
	else if(pos->y < 0.0 || pos->y > SCREEN_HEIGHT)
	{
		if (reflected >= info.reflectCount)
		{
			Restart();
		}
		else
		{
			reflected++;
			dirY *= -1.0f;
			cosDeg *= -1.0f;
			cosRad *= -1.0f;
		}
	}
}

void Bullet::Restart()
{
	visible = false;
	restart = true;

	pos->x = FLT_MAX;
	pos->y = FLT_MAX;

	collisionBox.calcCollisionBox(pos->x, pos->y, pos->x + texWidth, pos->y + texHeight, cosRad);
}