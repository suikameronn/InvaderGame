#pragma once
#include"Object.h"
#include"Button.h"

class ScrollPanel:public Object
{
private:
	float scrollSpeed;
	Position* offSet;
	Position offset;
	SDL_Color color;
	vector<unique_ptr<Object>> objectList;
public:

	ScrollPanel();
	void setPanelSize(float width, float height);
	void setPanelSize(int x, int y, float width, float height);
	void setScrollSpeed(float scrollSpeed);
	void setScrollSpeed(int scrollSpeed);
	void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void addObjectList(Object* obj);

	void moveObjects(float wheel);

	bool hitCheck(Mouse* mouse) override;
	void drawObjects(SDL_Renderer* gRenderer) override;

};