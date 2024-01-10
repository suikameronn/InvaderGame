#include"Title.h"

Title::Title(vector<TTF_Font*> fonts)
{
	sceneNum = -1;

	Text* titleText = new Text();
	titleText->setColor(255,255,255);
	titleText->setPos(81, 70);
	titleText->setText("InvaderGame");
	titleText->setFont(fonts[static_cast<int>(FONTS::BIG)]);
	addObjectToScene(titleText, "TitleText");

	Button* button = new Button();
	button->Object::setPos(100, 300);
	button->setOffSet(300, 100);
	button->setListner(new NextScene());
	button->setLabel("StageSelect", 255,255,255, fonts[static_cast<int>(FONTS::NORMAL)], 28);
	addObjectToScene(button,"ToSceneSelect");
}

void Title::Update_Scene()
{

}