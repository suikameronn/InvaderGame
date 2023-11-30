#include"Object.h"

Object::Object()
{
	pos = &position;
}

void Object::setPos(int px, int py)
{
	pos->x = px;
	pos->y = py;
}

void Object::draw(SDL_Renderer* gRenderer)
{

}