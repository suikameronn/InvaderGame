#include"Title.h"

Title::Title(string titleName, vector<TTF_Font*> fonts)
{
	titleText = new Text();
	drawList.emplace_back(titleText);

	color = { 255,255,255,255 };
	titleText->setColor(&color);
	titleText->setPos(70, 30);
	//titleText->setMove(100, 60);
	titleText->setText(titleName);
	titleText->setFont(fonts[static_cast<int>(FONTS::BIG)]);

	button = new Button();
	drawList.emplace_back(button);
	hitCheckList.emplace_back(button);
	button->Object::setPos(100, 300);
	button->setOffSet(300, 100);
	bColor = { 255,255,255,255 };
	button->setLabel("aaa", &bColor, fonts[static_cast<int>(FONTS::NORMAL)], 28);

	drawList.emplace_back(button->getLabel());
}

int Title::sceneChanger()
{
	if (sceneChange)
	{
		return 1;
	}

	return 0;
}