#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>

#include"Object.h"

using namespace std;

class Mouse
{
protected:
	Position* mousePos;
	Position mousePosition;

	vector<Object*> checkList;

public:
	int x, y;

	Mouse();
	void getMousePos(int* x, int* y);//マウスの座標を取得
};