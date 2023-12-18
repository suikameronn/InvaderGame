#include"Object.h"

Object::Object()
{
	pos = &position;
	tarPos = nullptr;
	movePos = nullptr;

	createdTex = false;
	moveFinish = true;
	changed = true;
	length = 0;
}

void Object::setPos(float px, float py)
{
	pos->x = px;
	pos->y = py;

	changed = true;
}

void Object::setMove(float px, float py)
{
	moveFinish = false;

	if (tarPos == nullptr)
	{
		tarPos = &tarPosition;
	}

	tarPos->x = px;
	tarPos->y = py;

	int lx, ly;
	lx = static_cast<int>(tarPos->x - pos->x);
	ly = static_cast<int>(tarPos->y - pos->y);

	length = static_cast<float>(sqrt(lx * lx + ly * ly) * 10);

	if (movePos == nullptr)
	{
		movePos = &movePosition;
	}

	movePos->x = lx / length;//ˆê‰ñ‚ÌˆÚ“®—Ê
	movePos->y = ly / length;
}

void Object::actMove()
{
	if (!moveFinish)
	{
		if (count > length)
		{
			moveFinish = true;
			count = 0;
		}
		else
		{
			setPos(pos->x + movePos->x, pos->y + movePos->y);
			count++;
		}
	}
}

void Object::drawObjects(SDL_Renderer* gRenderer)
{

}

bool Object::hitCheck(Mouse* mouse)
{
	return false;
}