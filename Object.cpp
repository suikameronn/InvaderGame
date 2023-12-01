#include"Object.h"

Object::Object()
{
	pos = &position;

	createdTex = false;
}

void Object::setPos(int px, int py)
{
	pos->x = px;
	pos->y = py;

	changed = true;
}

void Object::setMove(int px, int py)
{
	if (movePos == NULL)
	{
		movePos = &movePosition;
	}

	movePos->x = px;
	movePos->y = py;
}

void Object::actMove()
{
	pos->x
}

void Object::draw(SDL_Renderer* gRenderer)
{

}