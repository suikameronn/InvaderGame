#include"GameManager.h"

#include"Enemy.h"

Enemy::Enemy()
{
	this->luaUpdate = true;
	this->type = OBJECT::ENEMY;
	this->crash = false;
	this->crashTime = 0.0f;
	this->crashDisplayTime = 1.0f;
	this->crashTexture = GameManager::GetInstance()->crashTexture;
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

	luaL_dofile(lua, luaFilePath.c_str());

	coroutine = lua_newthread(lua);
	lua_getglobal(coroutine, "Update");
}

void Enemy::luaFunctionRegister()
{
	lua_register(lua, "glueSetMove", glueSetMove);
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

	bullets.resize(bulletLimit);
	for (auto itr = bullets.begin(); itr != bullets.end(); itr++)
	{
		(*itr) = std::shared_ptr<Bullet>(new Bullet(bulletInfo));
	}
}

std::shared_ptr<Bullet>* Enemy::getBulletData()
{
	return bullets.data();
}

void Enemy::Update()
{
	if (!crash)
	{
		int nresults;
		lua_resume(coroutine, nullptr, 0, &nresults);
	}
	else
	{
		defeat();
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
}