#pragma once

#include<iostream>
#include<SDL.h>

class Mouse
{
protected:
	SDL_Point* mousePos;
	SDL_Point mousePosition;

public:

	Mouse();
	void getMousePos(int* x, int* y);//�}�E�X�̍��W���擾
};