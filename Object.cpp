#include"Object.h"

Object::Object()
{
	Position position;
	pos = &position;
}

void Object::setPos(int x, int y)
{
	pos->x = x;
	pos->y = y;
}

void Object::draw(SDL_Renderer* gRenderer)
{

}