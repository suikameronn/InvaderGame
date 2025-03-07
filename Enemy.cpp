#include"GameManager.h"

#include"Enemy.h"

Enemy::Enemy(int index)
{
	this->index = index;
	this->luaUpdate = true;
	this->luaStatus = -10;
	this->type = OBJECT::ENEMY;
	this->crash = false;
	this->crashTime = 0.0f;
	this->crashDisplayTime = 0.5f;
	this->crashTexture = GameManager::GetInstance()->crashTexture;

	this->shotTime = -FLT_MAX;
}

Enemy::~Enemy()
{
	delete clip;
}

void Enemy::setLuaScript(std::string luaFilePath)
{
	lua = luaL_newstate();
	luaL_openlibs(lua);

	luaFunctionRegister();

	lua_pushlightuserdata(lua, this);
	lua_setglobal(lua, "myEnemy");

	lua_pushinteger(lua, index);
	lua_setglobal(lua, "Index");

	lua_pushinteger(lua, SCREEN_WIDTH);
	lua_setglobal(lua, "SCREEN_WIDTH");

	lua_pushinteger(lua, SCREEN_HEIGHT);
	lua_setglobal(lua, "SCREEN_HEIGHT");

	luaL_dofile(lua, luaFilePath.c_str());

	coroutine = lua_newthread(lua);
	lua_getglobal(coroutine, "Update");
}

void Enemy::luaFunctionRegister()
{
	lua_register(lua, "glueSetMove", glueSetMove);
	lua_register(lua, "glueSetPos", glueSetPos);
}

void Enemy::initFrameSettings(int bulletLimit, int hp, float posX, float posY, float speedX, float speedY,
	float texScale, SDL_Texture* texture, BulletInfo bulletInfo)
{
	this->hp = hp;
	this->pos->x = posX;
	this->pos->y = posY;
	this->speedX = speedX;
	this->speedY = speedY;
	this->texScale = texScale;
	this->bulletInfo = bulletInfo;

	this->texture = texture;
	SDL_QueryTexture(this->texture, nullptr, nullptr, &texWidth, &texHeight);

	texWidth *= texScale;
	texHeight *= texScale;

	int bulletOffsetX, bulletOffsetY;
	SDL_QueryTexture(bulletInfo.texture, nullptr, nullptr, &bulletOffsetX, &bulletOffsetY);
	bulletOffsetX *= bulletInfo.texScale;
	bulletOffsetY *= bulletInfo.texScale;

	this->bulletPosOffsetX = (texWidth / 2) - (bulletOffsetX / 2);
	this->bulletPosOffsetY = texHeight + (bulletOffsetY / 2);

	bullets.resize(bulletLimit);
	for(int i = 0;i < bullets.size();i++)
	{
		bullets[i] = std::shared_ptr<Bullet>(new Bullet(i % bulletInfo.dirX.size(),bulletInfo));
	}

	collisionBox.calcCollisionBox(pos->x, pos->y, pos->x + texWidth, pos->y + texHeight);

	lua_pushinteger(lua, texWidth);
	lua_setglobal(lua, "TEX_WIDTH");
	
	lua_pushinteger(lua, texHeight);
	lua_setglobal(lua, "TEX_HEIGHT");
}

std::shared_ptr<Bullet>* Enemy::getBulletData()
{
	return bullets.data();
}

void Enemy::Update()
{
	if (!crash)
	{
		if (luaUpdate && luaStatus != LUA_OK)
		{
			int nresults;
			luaStatus = lua_resume(coroutine, nullptr, 0, &nresults);
		}

		shotCheck();
	}
	else
	{
		defeat();
	}

	for (int i = 0;i < bullets.size();i++)
	{
		bullets[i]->restartCheck();
 		bullets[i]->Update();
	}
}

void Enemy::shotCheck()
{
	bool shot = false;
	std::vector<int> restartBullets;

	if ((clock() - shotTime) / CLOCKS_PER_SEC >= bulletInfo.rate)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->isRestart())
			{
				restartBullets.push_back(i);
				if (restartBullets.size() >= bulletInfo.dirX.size())
				{
					shot = true;
					shotTime = clock();
					break;
				}
			}
		}

		if (shot)
		{
			for (int i = 0; i < bulletInfo.dirX.size(); i++)
			{
				bullets[restartBullets[i]]->shoot(i % bulletInfo.dirX.size(), pos->x + bulletPosOffsetX, pos->y + bulletPosOffsetY);
			}
		}
	}
}

bool Enemy::isCrash()
{
	return crash;
}

void Enemy::damage()
{
   	hp--;
	if (hp == 0)
	{
		//Á–Å‚·‚éˆ—
		crash = true;
		crashTime = clock();
  		texture = crashTexture;

		luaUpdate = true;

		GameManager::GetInstance()->startSound(CRUSHED, false);
	}
	else
	{
		GameManager::GetInstance()->startSound(DAMAGED, false);
	}
}

void Enemy::defeat()
{
	if ((clock() - crashTime) / CLOCKS_PER_SEC < crashDisplayTime)
	{
		visible = true;
	}
	else
	{
		visible = false;
	}
}

void Enemy::drawObjects(SDL_Renderer* gRenderer)
{

	if (!crash)
	{
		luaUpdate = actMove();
		collisionBox.calcCollisionBox(pos->x, pos->y, pos->x + texWidth, pos->y + texHeight);
	}

	renderQuad = { (int)pos->x, (int)pos->y,
		static_cast<int>(texWidth), static_cast<int>(texHeight) };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if (visible)
	{
		//Render to screen
		SDL_RenderCopyEx(gRenderer, texture, clip, &renderQuad, angle, center, flip);
	}

	for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
	{
		(*itr)->drawObjects(gRenderer);
	}
}