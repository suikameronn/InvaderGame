#include"Title.h"

Title::Title()
{

}

Title::Title(string titleName,TTF_Font* font)
{
	title = new Text();
	drawList.emplace_back(title);

	color = { 255,255,255,255 };
	title->setColor(color);
	title->setPos(50, 30);
	title->setText(titleName);
	title->setFont(font);
}

void Title::draw()
{

}