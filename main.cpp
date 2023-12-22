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

struct windowDeleter
{
	void operator()(SDL_Window* window)
	{
		SDL_DestroyWindow(window);
	}
};

struct rendererDeleter
{
	void operator()(SDL_Renderer* renderer)
	{
		SDL_DestroyRenderer(renderer);
	}
};

struct fontDeleter
{
	void operator()(TTF_Font* font)
	{
		TTF_CloseFont(font);
	}
};

class Game
{
private:

public:
	bool sceneChange;

	unique_ptr<SDL_Window,windowDeleter> gWindow;
	unique_ptr<SDL_Renderer,rendererDeleter> gRenderer;

	vector<TTF_Font*> fontManager;
	unique_ptr<TTF_Font,fontDeleter> normalFont;
	unique_ptr<TTF_Font, fontDeleter> titleFont;

	Game();

	bool init();
	bool loadMedia();
};

Game::Game()
{
	sceneChange = true;
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

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
		gWindow.reset(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
		if (gWindow == nullptr)
		{
			cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer.reset(SDL_CreateRenderer(gWindow.get(), -1, SDL_RENDERER_ACCELERATED));//ƒŒƒ“ƒ_[‚ðì¬
			if (gRenderer == nullptr)
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
				if (TTF_Init() == -1)//SDL_ttf‚ð‰Šú‰»‚·‚é
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
	normalFont.reset(TTF_OpenFont("MPLUSRounded1c-Regular.ttf", 28));
	titleFont.reset(TTF_OpenFont("MPLUSRounded1c-Regular.ttf", 56));

	fontManager.emplace_back(normalFont.get());
	fontManager.emplace_back(titleFont.get());

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
					case 0:
						currentScene.reset(new Title("InvaderGame", game.fontManager));
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

				//Clear screen
				SDL_SetRenderDrawColor(game.gRenderer.get(), 0, 0, 0, 255);
				SDL_RenderClear(game.gRenderer.get());


				//Update screen
				SDL_RenderPresent(game.gRenderer.get());
			}
		}
	}

    return 0;
}