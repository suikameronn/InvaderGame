#include"Scene.h"

Scene::Scene()
{
	sceneChange = true;
}

void Update()
{

}

int Scene::sceneChanger()
{
	return -1;
}

//virtual
void Scene::otherUpdate_virtual ()
{

}

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

void Scene::addObjectToScene(Text* text)
{
	drawList.emplace_back(text);
	button_CheckList.emplace_back(text);
}

void Scene::addObjectToScene(Button* button)
{
	drawList.emplace_back(button);
	button_CheckList.emplace_back(button);

	if (button->label != nullptr)
	{
		drawList.emplace_back(button->label);
	}
}