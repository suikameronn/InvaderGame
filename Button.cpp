#include"Button.h"

Button::Button()
{
	OffSet = { 0 };
	offSet = &OffSet;

	Color = { 125,125,125,255 };
	color = &Color;

	exeMethod = nullptr;
}

void Button::setOffSet(float x, float y)
{
	offSet->x = x;
	offSet->y = y;
}

void Button::setLabel(string text, SDL_Color* labelColor, TTF_Font* font)
{
	if (label == nullptr)
	{
		label = new Text();
	}
	label->setText(text);
	label->setFont(font);
	label->setColor(labelColor);
}

void Button::setLabel(string text, SDL_Color* labelColor, TTF_Font* labelFont, int size)
{
	if (label == nullptr)
	{
		label = new Text();
	}
	label->setText(text);
	label->setFont(labelFont);
	label->setColor(labelColor);

	if (offSet->x != 0 && offSet->y != 0)
	{
		int sizeX = size / 2;
		int sizeY = size;

		int len = strlen(text.c_str());

		int centerX = (Object::pos->x * 2 + offSet->x) / 2;
		int centerY = (Object::pos->y * 2 + offSet->y) / 2;

		if (len % 2 == 0)
		{
			label->setPos(centerX - sizeX * (len / 2), centerY - sizeY);
		}
		else
		{
			label->setPos(centerX - (sizeX / 2) - sizeX * (len / 2), centerY - sizeY);
		}
	}
}

void Button::setMethod(void* method)
{
	exeMethod = method;
}

Text* Button::getLabel()
{
	return label;
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

void* buttonClicked()
{
	void* p;



	return p;
}

void Button::drawObjects(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, color->r,color->g,color->b,color->a);

	SDL_Rect rect = { Object::pos->x, Object::pos->y, offSet->x, offSet->y };
	SDL_RenderFillRect(gRenderer, &rect);
}