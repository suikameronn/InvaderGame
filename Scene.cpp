#include"Scene.h"

Scene::Scene()
{
	sceneChange = true;
	scene = NULL;
}

int Scene::sceneChanger()
{
	return -1;
}

void Scene::setScene(Scene* inputScene)
{
	scene = inputScene;
}

void Scene::drawScene(SDL_Renderer* gRenderer)
{

}