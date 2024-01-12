#include"Mouse.h"

Mouse::Mouse()
{
	mx = 0;
	my = 0;
	click = false;
	quit = false;
}

void Mouse::setMouseState()
{
	SDL_GetMouseState(&mx, &my);

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
		{
			click = true;
		}
		else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
		{
			click = false;
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