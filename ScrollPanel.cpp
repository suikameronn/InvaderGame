#include"ScrollPanel.h"

ScrollPanel::ScrollPanel()
{
	scrollSpeed = 1.0f;
	offset = { 0 };
	offSet = &offset;
	color = { 0,0,0,0 };
}

void ScrollPanel::setPanelSize(float w, float h)
{
	offSet->x = w;
	offSet->y = h;
}

void ScrollPanel::setPanelSize(int x, int y, float w, float h)
{
	this->setPos(x, y);

	offSet->x = w;
	offSet->y = h;
}

void ScrollPanel::setScrollSpeed(float speed)
{
	scrollSpeed = speed;
}

void ScrollPanel::setScrollSpeed(int speed)
{
	scrollSpeed = static_cast<int>(speed);
}

void ScrollPanel::setColor(unsigned char r, unsigned char g, unsigned char b,unsigned char a)
{
	color = { r,g,b,a };
}

void ScrollPanel::addObjectList(Object* obj)
{
	objectList.emplace_back(obj);
}

void ScrollPanel::moveObjects(float wheel)
{
	for (auto itr = objectList.begin(); itr != objectList.end(); ++itr)
	{
		(*itr)->setPos((*itr)->currentPosX(), (*itr)->currentPosY() - wheel * scrollSpeed);
	}
}

bool ScrollPanel::hitCheck(Mouse* mouse)
{
	if (mouse->mx > this->pos->x && mouse->mx < this->pos->x + offSet->x)
	{
		if (mouse->my > this->pos->y && mouse->my < this->pos->y + offSet->y)
		{
			moveObjects(mouse->wheel);
			return true;
		}
	}

	return false;
}

void ScrollPanel::drawObjects(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);

	SDL_Rect rect = { pos->x, pos->y, offSet->x, offSet->y};
	SDL_RenderFillRect(gRenderer, &rect);

	for (auto itr = objectList.begin(); itr != objectList.end(); ++itr)
	{
		(*itr)->drawObjectsScroll(gRenderer, pos,offSet);
	}
}