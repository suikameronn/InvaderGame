#include"Object.h"

Object::Object()
{
	pos = &position;

	createdTex = false;
	actSet = false;
	changed = true;
	length = 0;
	moveCount = 0;
	moveCountList = 0;

	type = EMPTY;

	visible = true;

	disappearCount = 0;
	disappearInterval = 0;
}

Object::~Object()
{

}

float Object::currentPosX()const
{
	return pos->x;
}

float Object::currentPosY()const
{
	return pos->y;
}

float Object::getBottom()
{
	return 0.0f;
}

void Object::setPos(float px, float py)
{
	pos->x = px;
	pos->y = py;

	changed = true;
}

void Object::setMoveList(float px, float py)
{
	if (!actSetList)
	{
		moveList.emplace_back(Position{ px,py });
	}
	else
	{
		cout << "MoveListが終わってからセットする2024 1 5 5:41" << endl;
	}
}

void Object::clearMoveList()
{
	moveList.clear();
	moveList.shrink_to_fit();
}

void Object::actMoveList()
{
	actSetList = true;

	reverse(moveList.begin(), moveList.end());
}

void Object::setMove(float px, float py)
{
	actSet = true;

	int lx = static_cast<int>(px - pos->x);
	int ly = static_cast<int>(py - pos->y);

	length = sqrt(lx * lx + ly * ly);
	moveCount = length;
	onceMoveX = lx / length;
	onceMoveY = ly / length;
}

void Object::setMove(Position p)
{
	actSet = true;

	int lx = static_cast<int>(p.x - pos->x);
	int ly = static_cast<int>(p.y - pos->y);

	length = sqrt(lx * lx + ly * ly);
	moveCount = length;
	onceMoveX = lx / length;
	onceMoveY = ly / length;
}

void Object::setMove(float px, float py, int time)
{
	actSet = true;

	int lx = static_cast<int>(px - pos->x);
	int ly = static_cast<int>(py - pos->y);

	moveCount = time;
	onceMoveX = lx / static_cast<float>(time);
	onceMoveY = ly / static_cast<float>(time);
}

bool Object::actMove()
{
	if(actSet && moveCount > 0)
	{
		setPos(pos->x + onceMoveX, pos->y + onceMoveY);
		moveCount--;
		return false;
	}
	else
	{
		actSet = false;
		moveCount = 0;
		return true;
	}
}

void Object::setDisappear(float time, int count)
{
	disappearTime = clock();
	disappearInterval = time;
	disappearCount = count;
}

void Object::disappear()
{
	if (disappearCount > 0)
	{
		if ((clock() - disappearTime) / CLOCKS_PER_SEC >= disappearInterval)
		{
			disappearTime = clock();

			if (visible)
			{
				visible = false;
			}
			else
			{
				visible = true;

				disappearCount--;
				if (disappearInterval <= 0)
				{
					disappearInterval = 0.0f;
				}
			}
		}
	}
}

void Object::Update()
{
	if (disappearInterval)
	{
		disappear();
	}
}

void Object::drawObjects(SDL_Renderer* gRenderer)
{

}

void Object::drawObjectsScroll(SDL_Renderer* gRenderer, Position* scrollPos,Position* offset)
{

}

bool Object::hitCheck()
{
	return false;
}

bool Object::hitCheckScroll(Position* scrollPos, Position* scrollOffSet)
{
	return false;
}