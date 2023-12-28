#include"Scene.h"

/*
bool operator<(pair<LARGE_INTEGER*, LARGE_INTEGER*> prev, pair<LARGE_INTEGER*, LARGE_INTEGER*> next)
{
	LARGE_INTEGER a;
	LARGE_INTEGER b;
	return a < b;
}
*/

Scene::Scene()
{

}

/*
void Scene::clockInit()
{
	QueryPerformanceFrequency(&freq);
}

void Scene::clockStart()
{
	QueryPerformanceCounter(&start);
}

void Scene::clockEnd()
{
	QueryPerformanceCounter(&end);
}
*/

void Scene::hitCheckScene(Mouse* mouse)
{
	int i;

	for (i = 0; i < button_CheckList.size(); ++i)
	{
		button_CheckList[i]->hitCheck(mouse);
	}
}

void Scene::drawScene(SDL_Renderer* gRenderer)
{
	int i;

	for (i = 0; i < drawList.size(); ++i)
	{
		drawList[i]->drawObjects(gRenderer);
	}
}

void Scene::Update_Scene()
{

}

void Scene::addObjectToScene(Text* text)
{
	drawList.emplace_back(text);
	button_CheckList.emplace_back(text);

	if (text->actSet)
	{
		actTimer[frameCount] = text;
	}
}

void Scene::addObjectToScene(Button* button)
{
	drawList.emplace_back(button);
	button_CheckList.emplace_back(button);

	if (button->label != nullptr)
	{
		drawList.emplace_back(button->label);
	}

	if (button->actSet)
	{
		actTimer[frameCount] = button;
	}
}