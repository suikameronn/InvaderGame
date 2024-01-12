#include"ScrollPanel.h"

ScrollPanel::ScrollPanel()
{
	scrollSpeed = 5.0f;
	width = 200;
	height = 300;
	color = { 0,0,0,0 };
}

void ScrollPanel::setPanelSize(int width, int height)
{
	width = width;
	height = height;
}

void ScrollPanel::setPanelSize(int x, int y, int w, int h)
{
	this->setPos(x, y);

	width = w;
	height = h;
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

void ScrollPanel::moveObjects(int wheel)
{
	iterator<Object*> itr;

}

bool ScrollPanel::hitCheck(Mouse* mouse)
{
	if (mouse->mx > Object::pos->x && mouse->mx < Object::pos->x + width)
	{
		if (mouse->my > Object::pos->y && mouse->my < Object::pos->y + height)
		{

		}
	}
}

void ScrollPanel::drawObjects(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);

	SDL_Rect rect = { Object::pos->x, Object::pos->y, Object::pos->x + width, Object::pos->y + height};
	SDL_RenderFillRect(gRenderer, &rect);
}