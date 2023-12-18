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

}

void Scene::drawScene(SDL_Renderer* gRenderer)
{

}