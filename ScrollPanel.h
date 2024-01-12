#pragma once
#include"Object.h"
#include"Button.h"

class ScrollPanel:Object
{
private:
	float scrollSpeed;
	int width;
	int height;
	SDL_Color color;
	vector<Object*> objectList;
public:

	ScrollPanel();
	void setPanelSize(int width, int height);
	void setPanelSize(int x, int y, int width, int height);
	void setScrollSpeed(float scrollSpeed);
	void setScrollSpeed(int scrollSpeed);
	void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void addObjectList(Object* obj);

	void moveObjects(int wheel);

	bool hitCheck(Mouse* mouse) override;
	void drawObjects(SDL_Renderer* gRenderer) override;

};