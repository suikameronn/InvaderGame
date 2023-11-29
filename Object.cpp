#include"Object.h"

Object::Object()
{
	pos = NULL;
}

void Object::setPos(int x, int y)
{
	pos->x = x;
	pos->y = y;
}

void Object::draw(SDL_Renderer* gRenderer)
{

}