#include"Scene.h"

Scene::Scene()
{
}

Scene::Scene(vector<TTF_Font*> fonts, SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;
	this->fonts = fonts;
}

Scene::~Scene()
{
}

void Scene::initLuaScript(lua_State* pL)
{
	std::string str;

	str = "createText";
	lua_register(pL, str.c_str(), &glue_createText);
}

void Scene::hitCheckScene()
{
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		if (itr->second->hitCheck())
		{
			//itr->second->l
		}
	}
}

void Scene::drawScene()
{
	for (auto itr = objList.begin(); itr != objList.end(); itr++)
	{
		itr->second->drawObjects(gRenderer);
	}
}

int Scene::Update_Scene()
{
	return 0;
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

void Scene::changeScene(int nextSceneNum)
{
	this->nextSceneNum = nextSceneNum;
}

void Scene::createText(std::string objName)
{
	Text* text = new Text();
	objList.insert(pair<string, unique_ptr<Object>>(objName, text));
}

void Scene::createButton(std::string objName)
{
	Button* button = new Button();
	objList.insert(pair<string, unique_ptr<Object>>(objName, button));
}

void Scene::createScrollPanel(std::string objName)
{
	ScrollPanel* scroll = new ScrollPanel();
	objList.insert(pair<string, unique_ptr<Object>>(objName,scroll));
}

void Scene::setPos(std::string objName, float x, float y)
{
	objList[objName]->setPos(x, y);
}

void Scene::setOffSet(std::string objName, float ox, float oy)
{
	if (objList[objName]->getType() == BUTTON)
	{
		objList[objName]->setOffSet(ox, oy);
	}
}

void Scene::setText(std::string objName, std::string text)
{
	OBJECT type = objList[objName]->getType();

	switch (type)
	{
	case TEXT:
		static_cast<Text*>(objList[objName].get())->setText(text);

	case BUTTON:
		static_cast<Button*>(objList[objName].get())->setLabel(text);
	}
}

void Scene::setColor(std::string objName, unsigned char r, unsigned char g, unsigned char b)
{
	OBJECT type = objList[objName]->getType();

	switch (type)
	{
	case TEXT:
		static_cast<Text*>(objList[objName].get())->setColor(r,g,b);

	case BUTTON:
		static_cast<Button*>(objList[objName].get())->setColor(r,g,b);
	}
}

void Scene::setFont(std::string objName, FONTS font)
{
	OBJECT type = objList[objName]->getType();

	switch (type)
	{
	case TEXT:
		static_cast<Text*>(objList[objName].get())->setFont(fonts[static_cast<int>(font)]);

	case BUTTON:
		static_cast<Button*>(objList[objName].get())->setFont(fonts[static_cast<int>(font)]);
	}
}

void Scene::setListner(std::string objName, EVENT event)
{
	OBJECT type = objList[objName]->getType();

	std::function<void()> function;
	switch (event)
	{
	case GOTO_TITLE:
		function = [=] {changeScene(1); };
	case GOTO_COURSE_SELECT:
		function = [=] {changeScene(2); };
	}

	switch (type)
	{
	case BUTTON:
		static_cast<Button*>(objList[objName].get())->setListner(function);
	}
}

void Scene::setMove(std::string objName,float px, float py, int fps)
{
	objList[objName]->setMove(px, py, fps);
}

void Scene::setMoveList(std::string objName, float px, float py)
{
	objList[objName]->setMoveList(px, py);
}

/*
int glue_createText(lua_State* pL);
int glue_createButton(lua_State* pL);
int glue_createScrollPanel(lua_State* pL);
int glue_setPos(lua_State* pL);
int glue_setOffSet(lua_State* pL);
int glue_setText(lua_State* pL);
int glue_setColor(lua_State* pL);
int glue_setFont(lua_State* pL);
int glue_setListner(lua_State* pL);
int glue_setMove(lua_State* pL);
int glue_setMoveList(lua_State* pL);
*/

int glue_createText(lua_State* pL)
{

}