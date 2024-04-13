#define main SDL_main

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include<vector>
#include <windows.h>

#include"Title.h"
#include"CourseSelect.h"

#include"Mouse.h"

#include"Text.h"

using namespace std;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

int fps;
int sceneNum = 0;

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

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	vector<TTF_Font*> fontManager;
	TTF_Font* smallFont;
	TTF_Font* normalFont;
	TTF_Font* titleFont;

	Game();
	~Game();

	bool init();
	bool loadMedia();

	float limitFrame;
	float deltaTime;
	LARGE_INTEGER freq;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	void clockInit();
	void clockStart();
	void clockEnd();
	void clockRestart();
	void fpsControl();
};

Game::Game()
{
}

Game::~Game()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	TTF_CloseFont(normalFont);
	TTF_CloseFont(titleFont);
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	deltaTime = 0;
	limitFrame = 1 / 60;

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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);//ƒŒƒ“ƒ_[‚ðì¬
			if (gRenderer == nullptr)
			{
				cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError() << endl;
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
	smallFont = TTF_OpenFont("MPLUSRounded1c-Regular.ttf", 14);
	normalFont = TTF_OpenFont("MPLUSRounded1c-Regular.ttf", 28);
	titleFont = TTF_OpenFont("MPLUSRounded1c-Regular.ttf", 56);

	fontManager.emplace_back(smallFont);
	fontManager.emplace_back(normalFont);
	fontManager.emplace_back(titleFont);

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

void Game::fpsControl()
{
	deltaTime = static_cast<float>(end.QuadPart - start.QuadPart) / freq.QuadPart;
	if (deltaTime < limitFrame)
	{
		Sleep(limitFrame - deltaTime);
		fps = 60;
	}
	else
	{
		fps = 1 / deltaTime;
	}
}

/**
*   ƒƒCƒ“
*/
int main(int argc, char** argv) {
    unique_ptr<Game> game = make_unique<Game>();

	game->clockInit();

	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(244);

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

			unique_ptr<Scene> currentScene;

			unique_ptr<Mouse> mouse;

			mouse = make_unique<Mouse>();

			//While application is running
			while (!quit)
			{
				game->clockStart();

				switch (sceneNum)
				{
				case 0:
					currentScene.reset(new Title(game->fontManager));
					break;
				case 1:
					currentScene.reset(new CourseSelect(game->fontManager));
				case -1:
					break;
				}

				currentScene->Update_Scene();

				mouse->setMouseState();
				if (mouse->quit)
				{
					break;
				}
				currentScene->hitCheckScene(mouse.get());

				//Clear screen
				SDL_SetRenderDrawColor(game->gRenderer, 0, 0, 0, 255);
				SDL_RenderClear(game->gRenderer);

				currentScene->drawScene(game->gRenderer);

				//Update screen
				SDL_RenderPresent(game->gRenderer);

				game->clockEnd();

				game->fpsControl();
			}
		}
	}

    return 0;
}