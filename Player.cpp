#include"GameManager.h"

#include"Player.h"

Player* Player::instance = nullptr;

Player::Player()
{
	shotTime = FLT_MAX;

	type = PLAYER;
	mouseInstance = Mouse::GetInstance();

	shotTime = 0.0f;

	damaged = false;
	damagedTime = -FLT_MAX;
	noDamagedTime = 1.0f;

	crashDisplayTime = 0.6f;

	crashTexture = GameManager::GetInstance()->crashTexture;
}

void Player::initFrameSettings()
{
	SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);

	texWidth *= texScale;
	texHeight *= texScale;

	offSetX = static_cast<int>(texWidth / 2);
	offSetY = static_cast<int>(texHeight / 2);

	SDL_QueryTexture(bulletInfo.texture, nullptr, nullptr, &bulletOffsetX, &bulletOffsetY);
	bulletOffsetX *= bulletInfo.texScale;
	bulletOffsetX /= 2;
	bulletOffsetY /= 2;

 	bullets.resize(bulletLimit);
	for(int i = 0;i < bulletLimit;i++)
	{
		bullets[i] = std::shared_ptr<Bullet>(new Bullet(i % bulletInfo.dirX.size(), bulletInfo));
	}
}

void Player::setHP(int hp)
{
	this->hp = hp;
}

void Player::addBulletDir(float x, float y)
{
	bulletInfo.addBulletDir(x, y);
}

void Player::setBulletSpeed(float speed)
{
	bulletInfo.speed = speed;
}

void Player::setBulletTexture(SDL_Texture* tex,float texScale)
{
	bulletInfo.texture = tex;
	bulletInfo.texScale = texScale;
}

void Player::setBulletRate(float rate)
{
	bulletInfo.rate = rate;
}

void Player::setBulletReflect(bool reflect, int count)
{
	bulletInfo.reflect = reflect;
	bulletInfo.reflectCount = count;
}

std::shared_ptr<Bullet>* Player::getBulletData()
{
	return bullets.data();
}

void Player::Update()
{
	if (disappearInterval > 0.0f)
	{
		disappear();
	}

	pos->x = mouseInstance->mx - offSetX;
	pos->y = mouseInstance->my - offSetY;

	collisionBox.calcCollisionBox(pos->x, pos->y, pos->x + texWidth, pos->y + texHeight);

	if (mouseInstance->spaceKey)
	{
		if ((clock() - shotTime) / CLOCKS_PER_SEC >= bulletInfo.rate)
		{
			for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
			{
				if ((*itr)->isRestart())
				{
					shotTime = clock();
					(*itr)->shoot(0,pos->x + offSetX - bulletOffsetX, pos->y - bulletOffsetY);
					break;
				}
			}
		}
	}

	for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
	{
		(*itr)->restartCheck();
		(*itr)->Update();
	}
}

void Player::drawObjects(SDL_Renderer* gRenderer)
{
	luaUpdate = actMove();

	renderQuad = { (int)pos->x, (int)pos->y,
		static_cast<int>(texWidth), static_cast<int>(texHeight) };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (!isCrash())
	{
		if (visible)
		{
			//Render to screen
			SDL_RenderCopyEx(gRenderer, texture, clip, &renderQuad, angle, center, flip);
		}
	}
	else if(isCrash())
	{
		SDL_RenderCopyEx(gRenderer, crashTexture, clip, &renderQuad, angle, center, flip);
	}

	for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
	{
		(*itr)->drawObjects(gRenderer);
	}
}

void Player::damage()
{
	if ((clock() - damagedTime) / CLOCKS_PER_SEC < noDamagedTime)
	{
		return;
	}

	hp--;
	if (hp <= 0)
	{
		crashTime = clock();
		GameManager::GetInstance()->startSound(CRUSHED, false);
	}
	else
	{
		GameManager::GetInstance()->startSound(DAMAGED, false);
	}
	

	damaged = true;
	damagedTime = clock();
	setDisappear(noDamagedTime / 5, 5);
}

bool Player::gameOver()
{
	if ((clock() - crashTime) / CLOCKS_PER_SEC > crashDisplayTime)
	{
		return true;
	}

	return false;
}

bool Player::isCrash()
{
	return hp <= 0;
}