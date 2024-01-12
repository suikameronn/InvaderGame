#include"Scene.h"

Scene::Scene()
{
	sceneNum = -1;
}

Scene::~Scene()
{
}

void Scene::hitCheckScene(Mouse* mouse)
{
	int i;

	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		itr->second->hitCheck(mouse);
	}

	/*
	for (i = 0; i < button_CheckList.size(); ++i)
	{
		button_CheckList[i]->hitCheck(mouse);
	}
	*/
}

void Scene::drawScene(SDL_Renderer* gRenderer)
{
	int i;

	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		itr->second->drawObjects(gRenderer);
	}

	/*
	for (i = 0; i < drawList.size(); ++i)
	{
		drawList[i]->drawObjects(gRenderer);
	}
	*/
}

void Scene::Update_Scene()
{

}

void Scene::addObjectToScene(Text* text,string objName)
{
	objList.insert(pair<string, unique_ptr<Object>>(objName, text));
	//drawList.insert(pair<string,unique_ptr<Object>>(objName,text));

	/*
	if (text->actSet)
	{
		actTimer[frameCount] = text;
	}
	*/
}

void Scene::addObjectToScene(Button* button,string objName)
{
	objList.insert(pair<string, unique_ptr<Object>>(objName, button));

	//drawList.insert(pair<string, unique_ptr<Object>>(objName, button));
	//button_CheckList.insert(pair<string, unique_ptr<Object>>(objName, button));

	/*
	if (button->actSet)
	{
		actTimer[frameCount] = button;
	}
	*/
}