#pragma once
#include"Object.h"
#include"Button.h"

class ScrollPanel
{
private:
	float scrollSpeed;
	int panelWidth;
	int panelHeight;
	SDL_Color panelColor;
	vector<Button> buttonList;
public:

	ScrollPanel();
	void setPanelSize(int width, int height);
	void setPanelSize(int x, int y, int width, int height);
	void setScrollSpeed(float scrollSpeed);
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	void addButtonList(Button* button);

};