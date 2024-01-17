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

	ScrollPanel* panel = new ScrollPanel();
	panel->setPos(100, 200);
	panel->setPanelSize(300, 300);
	panel->setColor(255, 255, 255,0);
	panel->setScrollSpeed(5.0f);
	panel->addObjectList(text);
	addObjectToScene(panel,"scrollpanel");
}

void CourseSelect::Update_Scene()
{

}