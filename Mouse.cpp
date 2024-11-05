#include"Mouse.h"

Mouse* Mouse::instance = nullptr;

Mouse::Mouse()
{
	mx = 0;
	my = 0;
	clickDown = false;
	clickUp = false;
	quit = false;
}

Mouse::~Mouse()
{

}

void Mouse::setMouseState()
{
	wheel = 0;

	SDL_GetMouseState(&mx, &my);


	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
		{
			clickDown = true;
			break;
		}
		else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
		{
			clickUp = true;
			break;
		}
		
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}

		if (e.type == SDL_MOUSEWHEEL)
		{
			if (e.wheel.y > 0)
			{
				wheel = -1;
			}
			else
			{
				wheel = 1;
			}
		}
		else
		{
			wheel = 0;
		}
	}
}

void Mouse::setFalseClickUpDown()
{
	clickDown = false;
	clickUp = false;
}