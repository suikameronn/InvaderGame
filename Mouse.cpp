#include"Mouse.h"

Mouse::Mouse()
{
	mousePosition = { 0 };
	mousePos = &mousePosition;
}

void Mouse::getMousePos(int* x, int* y)
{
	SDL_GetMouseState(x, y);
}