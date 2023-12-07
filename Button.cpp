#include"Button.h"

Button::Button()
{
	offSet = &OffSet;

	Color = { 125,125,125,255 };
	color = &Color;
}

void Button::setOffSet(float x, float y)
{
	offSet->x = x;
	offSet->y = y;
}

//private
void Button::changeColor(bool hit)
{
	if (hit)
	{
		*color = { 25,25,25,255 };
	}
	else
	{
		*color = { 125,125,125,255 };
	}
}

bool Button::hitCheck(int* x, int* y, bool clicked)
{
	if (clicked)
	{
		if (*x > Object::pos->x && *x < Object::pos->x + offSet->x)
		{
			if (*y > Object::pos->y && *y < Object::pos->y + offSet->y)
			{
				changeColor(true);
				return true;
			}
		}
	}
	else
	{
		changeColor(false);
	}

	return false;
}

void Button::drawObjects(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, color->r,color->g,color->b,color->a);

	SDL_Rect rect = { Object::pos->x, Object::pos->y, offSet->x, offSet->y };
	SDL_RenderFillRect(gRenderer, &rect);
}