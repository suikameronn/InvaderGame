#include"CourseSelect.h"

CourseSelect::CourseSelect(vector<TTF_Font*> fonts)
{

	Text* selectText = new Text();
	selectText->setFont(fonts[static_cast<int>(FONTS::BIG)]);
	selectText->setColor(255, 255, 255);
	selectText->setPos(81, 70);
	selectText->setText("CourseSelect");
	addObjectToScene(selectText,"sceneText");

	
	Text* text = new Text();
	text->setText("aaaAAAAA");
	text->setFont(fonts[static_cast<int>(FONTS::NORMAL)]);
	text->setColor(100, 100, 100);
	text->setPos(20, 40);
	

	Button* button = new Button();
	button->setPos(50, 30);
	//button->setColor(100, 100, 100);
	button->setOffSet(200, 60);
	button->setLabel("text",0,0,0,fonts[static_cast<int>(FONTS::NORMAL)],28);
	button->setListner(new Test());

	Button* back = new Button();
	back->setPos(10, 600);
	//back->setColor(100, 100, 100);
	back->setOffSet(50, 40);
	back->setLabel("Title", 0, 0, 0, fonts[static_cast<int>(FONTS::NORMAL)], 28);
	back->setListner(new SelectToTitle());
	addObjectToScene(back,"back");

	Button* a = new Button();
	a->setPos(10, 300);
	a->setOffSet(300, 100);
	a->setListner(new TitleToSelect());/*NextScene*/
	a->setLabel("StageSelect", 255, 255, 255, fonts[static_cast<int>(FONTS::NORMAL)], 28);
	addObjectToScene(a, "ToSceneSelect");

	ScrollPanel* panel = new ScrollPanel();
	panel->setPos(100, 150);
	panel->setPanelSize(300, 450);
	panel->setColor(255, 255, 255,0);
	panel->setScrollSpeed(50.0f);
	panel->addObjectList(button);
	panel->addObjectList(text);
	addObjectToScene(panel,"scrollpanel");
}

void CourseSelect::Update_Scene()
{
	cout << sceneNum << endl;
}