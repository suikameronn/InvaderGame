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
void Scene::Update_virtual ()
{

}

void Scene::hitCheckScene(int* x, int* y, bool clicked)
{
	int i;

	for (i = 0; i < hitCheckList.size(); ++i)
	{
		hitCheckList[i]->hitCheck(x, y, clicked);
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