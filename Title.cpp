#include"Title.h"

Title::Title()
{

}

Title::Title(string titleName,TTF_Font* font)
{
	titleText = new Text();
	drawList.emplace_back(titleText);

	color = { 255,255,255,255 };
	titleText->setColor(color);
	titleText->setPos(50, 30);
	titleText->setText(titleName);
	titleText->setFont(font);
}

void Title::draw(SDL_Renderer* gRenderer)
{
	int i;

	titleText->setPos(count, 30);
	count++;

	for (i = 0; i < drawList.size(); ++i)
	{
		drawList[i]->draw(gRenderer);
	}
}