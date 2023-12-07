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
	titleText->setPos(70, 30);
	//titleText->setMove(100, 60);
	titleText->setText(titleName);
	titleText->setFont(font);

	button = new Button();
	drawList.emplace_back(button);
	hitCheckList.emplace_back(button);
	button->Object::setPos(100, 300);
	button->setOffSet(300, 100);
}

void Title::hitCheckScene(int* x, int* y, bool clicked)
{
	int i;

	for (i = 0; i < hitCheckList.size(); ++i)
	{
		hitCheckList[i]->hitCheck(x, y, clicked);
	}
}

void Title::drawScene(SDL_Renderer* gRenderer)
{
	int i;

	for (i = 0; i < drawList.size(); ++i)
	{
		drawList[i]->drawObjects(gRenderer);
	}
}

int Title::sceneChanger()
{
	if (sceneChange)
	{
		return 1;
	}
}