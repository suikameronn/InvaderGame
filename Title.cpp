#include"Title.h"

Title::Title(vector<TTF_Font*> fonts, SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;

	Text* titleText = new Text();
	titleText->setColor(255,255,255);
	titleText->setPos(81, 70);
	titleText->setText("InvaderGame");
	titleText->setFont(fonts[static_cast<int>(FONTS::BIG)]);
	addObjectToScene(titleText, "TitleText");

	Button* button = new Button();
	button->setPos(100, 300);
	button->setOffSet(300, 100);
	button->setLabel("StageSelect", 255,255,255, fonts[static_cast<int>(FONTS::NORMAL)], 28);

	int nextSceneNum = 2;
	std::function<void()> eventFunction = [=]() {changeScene(nextSceneNum); };
	button->setListner(eventFunction);
	addObjectToScene(button,"ToSceneSelect");

	this->nextSceneNum = 0;
}

int Title::Update_Scene()
{
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		hitCheckScene();
	}

	drawScene();
	Mouse::GetInstance()->setMouseState();

	if (Mouse::GetInstance()->quit)
	{
		return -10;
	}

	return this->nextSceneNum;
}