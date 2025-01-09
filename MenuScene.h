#pragma once
#include"Scene.h"

class MenuScene :public Scene
{
protected:
	int frameCount = 0;

	map<int, Object*> actTimer;

public:
	MenuScene() { }
	MenuScene(std::string luaPath);

	~MenuScene() override {};

	void hitCheckScene() override;
	void drawScene() override;

	int Update_Scene() override;
};