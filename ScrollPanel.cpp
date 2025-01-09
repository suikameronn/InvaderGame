#include"ScrollPanel.h"

ScrollPanel::ScrollPanel()
{
	scrollSpeed = 1.0f;
	margin = 0.7;
	offset = { 0 };
	offSet = &offset;
	color = { 0,0,0,0 };

	type = SCROLL;
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

void ScrollPanel::setScrollLimit(float topMargin,float bottomMargin)
{
	sort(objectList.begin(), objectList.end(), [](const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b)
		{
			return a->currentPosY() < b->currentPosY();
		});
}

void ScrollPanel::addObjectList(Object* obj)
{
	objectList.emplace_back(std::unique_ptr<Object>(obj));
}

void ScrollPanel::Update()
{

}

void ScrollPanel::moveObjects(float wheel)
{
	float scrolled = wheel * scrollSpeed;
	auto topObj = objectList.begin();
	float topPos = (*topObj)->currentPosY();
	auto bottomObj = objectList.end() - 1;
	float bottomPos = (*bottomObj)->getBottom();

	if (wheel != 0)
	{
		cout << wheel << endl;
	}

	if ((pos->y + offSet->y) * margin < bottomPos && wheel > 0)
	{
		(*bottomObj)->setPos((*bottomObj)->currentPosX(), (*bottomObj)->currentPosY() - scrolled);

		for (auto itr = objectList.begin(); itr != objectList.end() - 1; ++itr)
		{
			(*itr)->setPos((*itr)->currentPosX(), (*itr)->currentPosY() - scrolled);
			cout << (*itr)->currentPosY() - scrolled << endl;
		}
	}
	else if(pos->y * (1 - margin) > topPos&& wheel < 0)
	{
		(*topObj)->setPos((*topObj)->currentPosX(), (*topObj)->currentPosY() - wheel * scrollSpeed);
		
		for (auto itr = objectList.begin() + 1; itr != objectList.end(); ++itr)
		{
			(*itr)->setPos((*itr)->currentPosX(), (*itr)->currentPosY() - wheel * scrollSpeed);
		}
	}
}

bool ScrollPanel::hitCheck()
{
	Mouse* mouse = Mouse::GetInstance();

	if (mouse->mx > this->pos->x && mouse->mx < this->pos->x + offSet->x)
	{
		if (mouse->my > this->pos->y && mouse->my < this->pos->y + offSet->y)
		{
			moveObjects(mouse->wheel);
			for (auto itr = objectList.begin(); itr != objectList.end(); ++itr)
			{
				(*itr)->hitCheckScroll(pos, offSet);
			}

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