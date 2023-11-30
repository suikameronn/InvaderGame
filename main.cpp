#define main SDL_main

#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include<vector>

#include"Text.h"

using namespace std;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

enum
{
	FONT,
	TOTAL
};

class Game
{
private:

public:

	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	TTF_Font* resources = NULL;

	bool init();
	bool loadMedia();
	void close();
};

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);//ƒŒƒ“ƒ_[‚ðì¬
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)//SDL_ttf‚ð‰Šú‰»‚·‚é
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	resources = TTF_OpenFont("C:\\Users\\sugiyama\\Downloads\\NotoSansJP-VariableFont_wght.ttf", 28);
	if (resources == NULL)
	{
		return false;
	}
	return true;
}

/**
*   ƒƒCƒ“
*/
int main(int argc, char** argv) {
    Game game;

	//Start up SDL and create window
	if (!game.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Laad media
		if (!game.loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			Text* text;
			text = new Text(game.resources);

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(game.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(game.gRenderer);

				text->setPos(10, 10);
				text->setText("AAAAAAA");
				//Render current frame
				text->draw(game.gRenderer);

				//Update screen
				SDL_RenderPresent(game.gRenderer);
			}
		}
	}

    return 0;
}