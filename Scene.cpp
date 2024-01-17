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
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		itr->second->hitCheck(mouse);
	}
}

void Scene::drawScene(SDL_Renderer* gRenderer)
{
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		itr->second->drawObjects(gRenderer);
	}
}

void Scene::Update_Scene()
{

}

void Scene::addObjectToScene(Text* text,string objName)
{
	objList.insert(pair<string, unique_ptr<Object>>(objName, text));
}

void Scene::addObjectToScene(Button* button,string objName)
{
	objList.insert(pair<string, unique_ptr<Object>>(objName, button));
}

void Scene::addObjectToScene(ScrollPanel* scroll, string objName)
{
	objList.insert(pair<string, unique_ptr<Object>>(objName, scroll));
}