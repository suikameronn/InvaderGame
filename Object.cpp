#include"Object.h"

Object::Object()
{
	pos = &position;

	createdTex = false;
	moveFinish = true;
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

	if (tarPos == NULL)
	{
		tarPos = &tarPosition;
	}

	tarPos->x = px;
	tarPos->y = py;

	int lx, ly;
	lx = tarPos->x - pos->x;
	ly = tarPos->y - pos->y;

	length = sqrt(lx * lx + ly * ly) * 10;

	if (movePos == NULL)
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

void Object::draw(SDL_Renderer* gRenderer)
{

}