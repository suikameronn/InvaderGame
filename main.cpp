#define main SDL_main

#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include<vector>

#include"Title.h"
#include"Mouse.h"

#include"Text.h"

using namespace std;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

enum
{
	TITLE,
	COURSESELECT,
	GAME,
	RESULT
};

class Game
{
private:

public:
	bool sceneChange;

	shared_ptr<SDL_Window> gWindow;
	shared_ptr<SDL_Renderer> gRenderer;
	TTF_Font* font;

	bool init();
	bool loadMedia();
	void close();
};

bool Game::init()
{
	//Initialization flag
	bool success = true;

	sceneChange = true;

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
		gWindow = shared_ptr<SDL_Window>(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN),SDL_DestroyWindow);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = shared_ptr<SDL_Renderer>(SDL_CreateRenderer(gWindow.get(), -1, SDL_RENDERER_ACCELERATED),SDL_DestroyRenderer);//レンダーを作成
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)//SDL_ttfを初期化する
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
	font = TTF_OpenFont("C:\\Users\\sugiyama\\Downloads\\NotoSansJP-VariableFont_wght.ttf", 56);
	if (font == NULL)
	{
		return false;
	}
	return true;
}

/**
*   メイン
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

			int sceneNum = 0;

			unique_ptr<Scene> currentScene;
			currentScene = make_unique<Scene>();

			shared_ptr<Mouse> mouse;
			mouse = make_unique<Mouse>();

			//While application is running
			while (!quit)
			{
				if (currentScene->sceneChange)
				{
					switch (sceneNum)
					{
					case TITLE:
						currentScene->scene = new Title("InvaderGame", game.font);
						currentScene->sceneChange = false;
					}
				}

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				mouse->getMousePos(&mouse->x, &mouse->y);

				//Clear screen
				SDL_SetRenderDrawColor(game.gRenderer.get(), 0, 0, 0, 255);
				SDL_RenderClear(game.gRenderer.get());

				currentScene->scene->drawScene(game.gRenderer.get());

				//Update screen
				SDL_RenderPresent(game.gRenderer.get());
			}
		}
	}

    return 0;
}