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

void Object::draw(SDL_Renderer* gRenderer)
{

}