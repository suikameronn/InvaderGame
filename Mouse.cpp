#include"Mouse.h"

Mouse::Mouse()
{
	mx = 0;
	my = 0;
	clickDown = false;
	clickUp = false;
	quit = false;
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
			cout << "Down" << endl;
			clickDown = true;
		}
		else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
		{
			cout << "Up" << endl;
			clickUp = true;
		}
		else
		{
			cout << "Middle" << endl;
			clickDown = false;
			clickUp = false;
		}
		
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}

		if (e.type == SDL_MOUSEWHEEL)
		{
			cout << e.wheel.y << endl;
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