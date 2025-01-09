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

	luaL_dofile(lua, luaFilePath.c_str());

	coroutine = lua_newthread(lua);
	lua_getglobal(coroutine, "Update");
}

void Enemy::luaFunctionRegister()
{
	lua_register(lua, "glueSetMove", glueSetMove);
	lua_register(lua, "glueSetPos", glueSetPos);
}

void Enemy::initFrameSettings(int bulletLimit,int hp,float posX,float posY,float speedX,float speedY,
	float texScale,SDL_Texture* texture,BulletInfo bulletInfo)
{
	this->hp = hp;
	this->pos->x = posX;
	this->pos->y = posY;
	this->speedX = speedX;
	this->speedY = speedY;
	this->texScale = texScale;
	this->bulletInfo = bulletInfo;

	this->texture = texture;
	SDL_QueryTexture(this->texture, nullptr,nullptr, &texWidth, &texHeight);

	texWidth *= texScale;
	texHeight *= texScale;

	this->bulletPosOffsetX = texWidth / 2;
	this->bulletPosOffsetY = texHeight;

	bullets.resize(bulletLimit);
	for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
	{
		(*itr) = std::shared_ptr<Bullet>(new Bullet(bulletInfo));
	}

	calcCollisionBox();
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

	for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
	{
		(*itr)->restartCheck();
		(*itr)->Update();
	}
}

void Enemy::shotCheck()
{
	if ((clock() - shotTime) / CLOCKS_PER_SEC >= bulletInfo.rate)
	{
		for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
		{
			if ((*itr)->isRestart())
			{
				shotTime = clock();
				(*itr)->shoot(pos->x + bulletPosOffsetX, pos->y + bulletPosOffsetY);
				break;
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
		//è¡ñ≈Ç∑ÇÈèàóù
		crash = true;
		crashTime = clock();
  		texture = crashTexture;

		luaUpdate = true;
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
	if (!visible)
	{
		return;
	}

	if (!crash)
	{
		luaUpdate = actMove();
		calcCollisionBox();
	}

	renderQuad = { (int)pos->x, (int)pos->y,
		static_cast<int>(texWidth), static_cast<int>(texHeight) };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, texture, clip, &renderQuad, angle, center, flip);

	for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
	{
		(*itr)->drawObjects(gRenderer);
	}
}