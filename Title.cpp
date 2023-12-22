#include"Title.h"

Title::Title(string titleName, vector<TTF_Font*> fonts)
{
	titleText = make_unique<Text>();
	//drawList.emplace_back(titleText);

	color = { 255,255,255,255 };
	titleText->setColor(&color);
	titleText->setPos(70, 30);
	//titleText->setMove(100, 60);
	titleText->setText(titleName);
	titleText->setFont(fonts[static_cast<int>(FONTS::BIG)]);
	addObjectToScene(titleText.get());

	button.reset(new Button());
	button->Object::setPos(100, 300);
	button->setOffSet(300, 100);
	bColor = { 255,255,255,255 };
	button->setListner(new NextScene);
	button->setLabel("aaa", &bColor, fonts[static_cast<int>(FONTS::NORMAL)], 28);
	addObjectToScene(button.get());
}

int Title::sceneChanger()
{
	if (sceneChange)
	{
		return 1;
	}

	return 0;
}

void Title::otherUpdate_virtual()
{

}