#define main SDL_main

#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include<vector>
#include <windows.h>

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

	int frameCount;
	float deltaTime;
	LARGE_INTEGER freq;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	void clockInit();
	void clockStart();
	void clockEnd();
	void clockRestart();
};

Game::Game()
{
	sceneChange = true;
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	deltaTime = 0;

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

void Game::clockInit()
{
	QueryPerformanceFrequency(&freq);
}

void Game::clockStart()
{
	QueryPerformanceCounter(&start);
}

void Game::clockEnd()
{
	QueryPerformanceCounter(&end);
}

void Game::clockRestart()
{
	deltaTime = 0;
}

/**
*   ƒƒCƒ“
*/
int main(int argc, char** argv) {
    Game* game = new Game();

	game->clockInit();

	//Start up SDL and create window
	if (!game->init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		//Laad media
		if (!game->loadMedia())
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			//Main loop flag
			bool quit = false;

			int sceneNum = 0;

			unique_ptr<Scene> currentScene;
			currentScene = make_unique<Scene>();

			shared_ptr<Mouse> mouse;
			mouse = make_unique<Mouse>();

			//While application is running
			while (!quit)
			{
				game->clockStart();

				if (currentScene->sceneChange)
				{
					switch (sceneNum)
					{
					case 0:
						currentScene.reset(new Title("InvaderGame", game->fontManager));
						currentScene->sceneChange = false;
					}
				}

				currentScene->otherUpdate_virtual();

				mouse->setMouseState();
				currentScene->hitCheckScene(mouse.get());

				//Clear screen
				SDL_SetRenderDrawColor(game->gRenderer.get(), 0, 0, 0, 255);
				SDL_RenderClear(game->gRenderer.get());

				currentScene->drawScene(game->gRenderer.get());

				//Update screen
				SDL_RenderPresent(game->gRenderer.get());

				game->clockEnd();

				game->deltaTime += static_cast<float>(game->end.QuadPart - game->start.QuadPart) * 1000.0 / game->freq.QuadPart;
				game->frameCount++;

				//printf("time %f[ms]\n", game->deltaTime);

			}
		}
	}

    return 0;
}