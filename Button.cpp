#include"Button.h"

Button::Button()
{
	OffSet = { 0 };
	offSet = &OffSet;

	Color = { 125,125,125,255 };
	color = &Color;

	fontSize = 28;
}

Button::~Button()
{
	if (label != nullptr)
	{
		delete label;
	}
}

void Button::setPos(float px, float py)
{
	pos->x = px;
	pos->y = py;

	changed = true;

	if(offSet != nullptr && label != nullptr)
	{
		int sizeX = fontSize / 2;
		int sizeY = fontSize;

		int len = strlen(label->getText().c_str());

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

void Button::setPosText()
{
	if (offSet != nullptr && label != nullptr)
	{
		int sizeX = fontSize / 2;
		int sizeY = fontSize;

		int len = strlen(label->getText().c_str());

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

		changed = true;
	}
}

void Button::setOffSet(float x, float y)
{
	offSet->x = x;
	offSet->y = y;

	setPosText();
}

void Button::setLabel(string text, unsigned char r, unsigned char g, unsigned char b, TTF_Font* font)
{
	if (label == nullptr)
	{
		label = new Text();
	}
	label->setText(text);
	label->setFont(font);
	label->setColor(r,g,b);

	setPosText();
}

void Button::setLabel(string text, unsigned char r, unsigned char g, unsigned char b, TTF_Font* labelFont, int size)
{
	fontSize = size;

	if (label == nullptr)
	{
		label = new Text();
	}
	label->setText(text);
	label->setFont(labelFont);
	label->setColor(r, g, b);

	setPosText();
}

void Button::setListner(Listner* obj)
{
	listner.reset(obj);
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

bool Button::hitCheck(Mouse* mouse)
{
	if (mouse->mx > Object::pos->x && mouse->mx < Object::pos->x + offSet->x)
	{
		if (mouse->my > Object::pos->y && mouse->my < Object::pos->y + offSet->y)
		{
			if (mouse->clickDown)
			{
				changeColor(true);
				return true;
			}
			else if (mouse->clickUp)
			{
				listner->action();
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

bool Button::hitCheckScroll(Mouse* mouse,Position* scrollPos,Position* scrollOffSet)
{
	if (mouse->mx > Object::pos->x + scrollPos->x && mouse->mx < Object::pos->x + offSet->x + scrollOffSet->x)
	{
		if (mouse->my > Object::pos->y + scrollPos->y && mouse->my < Object::pos->y + offSet->y + scrollOffSet->y)
		{
			if (mouse->clickDown)
			{
				changeColor(true);
				return true;
			}
			else if (mouse->clickUp)
			{
				listner->action();
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
	if (label != nullptr)
	{
		label->drawObjects(gRenderer);
	}
}

void Button::drawObjectsScroll(SDL_Renderer* gRenderer, Position* scrollPos, Position* scrollOffSet)
{
	SDL_SetRenderDrawColor(gRenderer, color->r, color->g, color->b, color->a);

	SDL_Rect rect;
	if (pos->y < 0)
	{
		if (pos->y + offSet->y < 0)
		{
			rect = { 0,0,0,0 };
		}
		else
		{
			rect = { int(pos->x + scrollPos->x), int(scrollPos->y), int(offSet->x), int(offSet->y + pos->y) };
		}
	}
	else if (pos->y + this->offSet->y > scrollOffSet->y)
	{
		if (pos->y > scrollOffSet->y)
		{
			rect = { 0,0,0,0 };
		}
		else
		{
			rect = { int(pos->x + scrollPos->x), int(pos->y + scrollPos->y), int(offSet->x), int(offSet->y - (pos->y + offSet->y - scrollOffSet->y)) };
		}
	}
	else
	{
		rect = { int(pos->x + scrollPos->x), int(pos->y + scrollPos->y), int(offSet->x), int(offSet->y) };
	}
	
	SDL_RenderFillRect(gRenderer, &rect);
	if (label != nullptr)
	{
		label->drawObjectsScroll(gRenderer,scrollPos,scrollOffSet);
	}
}