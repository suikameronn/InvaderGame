#include"CourseSelect.h"

CourseSelect::CourseSelect(vector<TTF_Font*> fonts,SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;

	Text* selectText = new Text();
	selectText->setFont(fonts[static_cast<int>(FONTS::BIG)]);
	selectText->setColor(255, 255, 255);
	selectText->setPos(81, 70);
	selectText->setText("CourseSelect");
	addObjectToScene(selectText,"sceneText");

	Button* back = new Button();
	back->setPos(10, 600);
	back->setOffSet(50, 30);
	back->setLabel("Back", 0, 0, 0, fonts[static_cast<int>(FONTS::SMALL)], 14);

	int nextSceneNum = 1;
	std::function<void()> eventFunction = [=]() {changeScene(nextSceneNum); };
	//back->setListner(eventFunction);
	addObjectToScene(back,"back");

	int i = 1;
	vector<Button*> StageSelects;
	for (i = 0; i < 10; i++)
	{
		Button* StageSelect = new Button();
		std::function<void()> eventFunction = [=]() {changeScene(3); };
		//StageSelect->setListner(eventFunction);
		StageSelect->setPos(50, 5 + i * 150);
		StageSelect->setOffSet(200, 100);
		StageSelect->setLabel(std::to_string(i), 255, 255, 255, fonts[static_cast<int>(FONTS::NORMAL)], 28);
		StageSelects.emplace_back(StageSelect);
	}

	ScrollPanel* panel = new ScrollPanel();
	panel->setPos(100, 150);
	panel->setPanelSize(300, 450);
	panel->setColor(255, 255, 255,0);
	panel->setScrollSpeed(50.0f);
	for (auto itr = StageSelects.begin(); itr != StageSelects.end(); ++itr)
	{
		panel->addObjectList(*itr);
	}
	panel->setScrollLimit(50,0);
	addObjectToScene(panel,"scrollpanel");

	this->nextSceneNum = 0;
}

int CourseSelect::Update_Scene()
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