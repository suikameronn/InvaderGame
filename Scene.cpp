#include"Scene.h"

Scene::Scene()
{
	sceneChange = false;
	scene = NULL;
}

Scene::Scene(Scene* inputScene)
{
	sceneChange = false;
	scene = inputScene;
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