#include"EnemyWaveGroup.h"

EnemyGroup::EnemyGroup()
{
	this->type = OBJECT::ENEMY;
	this->clear = false;
	this->luaPath = "";
}

EnemyGroup::~EnemyGroup()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		delete enemys[i];
	}
}

void EnemyGroup::setLuaScript(std::string updateScriptPath)
{
	luaPath = updateScriptPath;
}

void EnemyGroup::setInitPos(float x, float y)
{
	posX = x;
	posY = y;
}

void EnemyGroup::setHP(int hp)
{
	this->hp = hp;
}

void EnemyGroup::setSpeed(float speedX,float speedY)
{
	this->speedX = speedX;
	this->speedY = speedY;
}

void EnemyGroup::setBulletLimit(int limit)
{
	this->bulletLimit = limit;
}

void EnemyGroup::addBulletDir(float x, float y)
{
	float length = sqrt(x * x + y * y);
	y /= length;
	x /= length;

	bulletInfo.dirX.push_back(x);
	bulletInfo.dirY.push_back(y);
}

void EnemyGroup::setBulletSpeed(float speed)
{
	bulletInfo.speed = speed;
}

void EnemyGroup::setBulletSize(int width, int height)
{
	bulletInfo.width = width;
	bulletInfo.height = height;
}

void EnemyGroup::addBulletColor(SDL_Color color)
{
	bulletInfo.colors.push_back(color);
}

void EnemyGroup::setBulletRate(float rate)
{
	bulletInfo.rate = rate;
}

void EnemyGroup::setBulletReflect(bool reflect, int count)
{
	bulletInfo.reflect = reflect;
	bulletInfo.reflectCount = count;
}

void EnemyGroup::setDelayFrame(int delayFrame)
{
	this->delayFrame = delayFrame;
}

void EnemyGroup::setImage(SDL_Texture* texture)
{
	this->texture = texture;
}

void EnemyGroup::setGroupEnemyCount(int count)
{
	enemys.resize(count);
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i] = new Enemy(i);
	}
}

void EnemyGroup::hitCheck(Player* player)
{
	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i]->hitCheck(player->getCollisionBox()))
		{
			//プレイヤーがダメージを受けたときの処理
			player->damage();
		}

		std::shared_ptr<Bullet> bullet;
		for (int j = 0; j < bulletLimit; j++)
		{
			bullet = enemys[i]->getBulletData()[j];
			if (!bullet->isRestart()
				&& bullet->hitCheck(player->getCollisionBox()))
			{
				player->damage();
				bullet->Restart();
			}
		}

		for (int j = 0; j < player->getBulletLimit(); j++)
		{
			bullet = player->getBulletData()[j];
			if (!bullet->isRestart()
				&& !enemys[i]->isCrash()
				&& bullet->hitCheck(enemys[i]->getCollisionBox()))
			{
				enemys[i]->damage();
				bullet->Restart();
				break;
			}
		}
	}
}

void EnemyGroup::Update()
{
	for (size_t i = 0; i < enemys.size(); i++)
	{
		if (currentFrame >= i * delayFrame || enemys[i]->isCrash())
		{
			enemys[i]->Update();
			enemys[i]->luaUpdate = false;
		}
	}

	currentFrame++;

	if (currentFrame > 10000000)
	{
		currentFrame = 10000000;
	}
}

EnemyGroup* EnemyWave::addEnemyGroup()
{
	EnemyGroup* group = new EnemyGroup();
	enemyGroups.push_back(group);

	return group;
}

void EnemyGroup::initFrameSettings()
{
	for (auto itr = enemys.begin(); itr != enemys.end(); itr++)
	{
		(*itr)->setLuaScript(luaPath);
	}

	for (auto itr = enemys.begin(); itr != enemys.end(); itr++)
	{
		(*itr)->initFrameSettings(bulletLimit,hp,posX,posY,speedX,speedY,texScale,texture,bulletInfo);
	}
}

void EnemyGroup::draw(SDL_Renderer* gRenderer)
{
	for (auto itr = enemys.begin(); itr != enemys.end(); itr++)
	{
		(*itr)->drawObjects(gRenderer);
	}
}

bool EnemyGroup::clearCheck()
{
	for (auto itr = enemys.begin(); itr != enemys.end(); itr++)
	{
		if ((*itr)->isVisible())
		{
			return false;
		}
	}

	return true;
}

EnemyWave::EnemyWave()
{
	currentGroupNumber = 0;
	clear = false;
}

EnemyWave::~EnemyWave()
{
	for (int i = 0; i < enemyGroups.size(); i++)
	{
		delete enemyGroups[i];
	}
}

void EnemyWave::initFrameSettings()
{
	for (auto itr = enemyGroups.begin(); itr != enemyGroups.end(); itr++)
	{
		(*itr)->initFrameSettings();
	}
}

void EnemyWave::Update()
{
	enemyGroups[currentGroupNumber]->Update();
}

void EnemyWave::hitCheck(Player* player)
{
	enemyGroups[currentGroupNumber]->hitCheck(player);
}

void EnemyWave::draw(SDL_Renderer* gRenderer)
{
	enemyGroups[currentGroupNumber]->draw(gRenderer);
}

bool EnemyWave::clearCheck()
{
	if (enemyGroups[currentGroupNumber]->clearCheck())
	{
		currentGroupNumber++;
		if (currentGroupNumber >= enemyGroups.size())
		{
			return true;
		}
	}

	return false;
}