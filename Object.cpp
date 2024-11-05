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
	int lx = static_cast<int>(px - pos->x);
	int ly = static_cast<int>(py - pos->y);

	length = sqrt(lx * lx + ly * ly);
	moveCount = length;
	onceMoveX = lx / time;
	onceMoveY = ly / time;
}

void Object::actMove()
{
	if(actSet && moveCount > 0)
	{
		setPos(pos->x + onceMoveX, pos->y + onceMoveY);
		moveCount--;
		return;
	}
	else
	{
		moveCount = 0;
	}

	if (actSetList)
	{
		if (!moveList.empty())
		{
			if (moveCountList == 0)
			{
				setMove(moveList.back());
				moveList.pop_back();
			}
			else
			{
				setPos(pos->x + onceMoveX, pos->y + onceMoveY);
				moveCount--;

			}
		}
		else
		{
			cout << "MoveListが空の状態で、actMoveListされた" << endl;
		}
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