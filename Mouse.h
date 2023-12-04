#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>

#include"Object.h"

using namespace std;

class Mouse
{
protected:
	SDL_Point* mousePos;
	SDL_Point mousePosition;

	vector<Object*> checkList;

public:

	int x, y;

	Mouse();
	void getMousePos(int* x, int* y);//マウスの座標を取得
};