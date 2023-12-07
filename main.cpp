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

	unique_ptr<TTF_Font> titleFont;
	unique_ptr<TTF_Font> buttonFont;

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
		cout << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled!" << endl;
		}

		//Create window
		gWindow = shared_ptr<SDL_Window>(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN),SDL_DestroyWindow);
		if (gWindow == NULL)
		{
			cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = shared_ptr<SDL_Renderer>(SDL_CreateRenderer(gWindow.get(), -1, SDL_RENDERER_ACCELERATED),SDL_DestroyRenderer);//レンダーを作成
			if (gRenderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError() << endl;
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
					cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError() << endl;
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)//SDL_ttfを初期化する
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	titleFont = unique_ptr<TTF_Font>(TTF_OpenFont("NotoSansJP-VariableFont_wght.ttf", 56));
	buttonFont = unique_ptr<TTF_Font>(TTF_OpenFont("NotoSansJP-VariableFont_wght.ttf", 28));

	if (titleFont == NULL)
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
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		//Laad media
		if (!game.loadMedia())
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			//Main loop flag
			bool quit = false;

			bool clicked = false;

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
						currentScene.reset(new Title("InvaderGame", game.titleFont.get()));
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
					else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
					{
						clicked = true;
					}
					else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
					{
						clicked = false;
					}
				}

				mouse->getMousePos(&mouse->x, &mouse->y);
				currentScene->hitCheckScene(&mouse->x, &mouse->y, clicked);

				//Clear screen
				SDL_SetRenderDrawColor(game.gRenderer.get(), 0, 0, 0, 255);
				SDL_RenderClear(game.gRenderer.get());

				currentScene->drawScene(game.gRenderer.get());

				//Update screen
				SDL_RenderPresent(game.gRenderer.get());
			}
		}
	}

    return 0;
}