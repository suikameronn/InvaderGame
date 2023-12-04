#include"Mouse.h"

Mouse::Mouse()
{
	mousePos = &mousePosition;
	x = 0;
	y = 0;
}

void Mouse::getMousePos(int* x, int* y)
{
	SDL_GetMouseState(x,y);
}