#include"Scene.h"

Scene::Scene()
{
	sceneChange = true;
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

	for (i = 0; i < hitCheckList.size(); ++i)
	{
		hitCheckList[i]->hitCheck(mouse);
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