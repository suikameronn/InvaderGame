#include"Mouse.h"

Mouse::Mouse()
{
	mousePos = &mousePosition;
}

void Mouse::getMousePos(int* x, int* y)
{
	SDL_GetMouseState(x,y);
}