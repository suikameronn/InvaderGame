#include"Button.h"

Button::Button()
{
	offSet = &OffSet;
	color = &Color;
	changeColor = &ChangeColor;
}

void Button::setOffSet(int* x, int* y)
{
	offSet->x = *x;
	offSet->y = *y;
}

void Button::setColor(SDL_Color* col)
{
	color->r = col->r;
	color->g = col->g;
	color->b = col->b;
	color->a = col->a;
}

void Button::setChangeColor(SDL_Color* col)
{
	changeColor->r = col->r;
	changeColor->g = col->g;
	changeColor->b = col->b;
	changeColor->a = col->a;
}

bool Button::hitCheck(int* x, int* y, bool clicked)
{
	if (clicked)
	{
		if (*x < offSet->x && *x > Object::pos->x)
		{
			if (*y < offSet->y && *y > Object::pos->y)
			{
				return true;
			}
		}
	}

	return false;
}