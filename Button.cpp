#include"Button.h"

Button::Button()
{
	offSet = &OffSet;
}

void Button::setOffSet(int* x, int* y)
{
	offSet->x = *x;
	offSet->y = *y;
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

void drawObects(SDL_Renderer* gRenderer)
{
	SDL_Color color = { 125,125,125,255 };
	SDL_SetRenderDrawColor(gRenderer, color.r,color.g,color.b,color.a);
	SDL_RenderFillRect(gRenderer,)
}