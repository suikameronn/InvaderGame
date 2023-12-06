#include"Mouse.h"

Mouse::Mouse()
{
	mousePos = unique_ptr<Position>(new Position);
	mousePos->x = 0;
	mousePos->y = 0;
}

void Mouse::getMousePos(int* x, int* y)
{
	SDL_GetMouseState(x, y);
}