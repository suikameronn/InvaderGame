#include"GameManager.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	if (!instance)
	{
		instance = this;

		init();
		loadMedia();
		currentScene.reset(new MenuScene("luaScript/Title.lua"));
	}
}

void GameManager::DestroyGameManager()
{
	if (instance)
	{
		delete instance;
	}
}

GameManager::~GameManager()
{
	currentScene.reset();
	Mouse::GetInstance()->DestroyMouse();

	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	TTF_CloseFont(normalFont);
	TTF_CloseFont(titleFont);
}

bool GameManager::init()
{
	quiet = false;

	//Initialization flag
	bool success = true;

	deltaTime = 0;
	limitFrame = 1.0f / 60.0f;

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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width,screen_height, SDL_WINDOW_SHOWN);
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

bool GameManager::loadMedia()
{
	smallFont = TTF_OpenFont("MPLUSRounded1c-Regular.ttf", 14);
	normalFont = TTF_OpenFont("MPLUSRounded1c-Regular.ttf", 28);
	titleFont = TTF_OpenFont("MPLUSRounded1c-Regular.ttf", 56);

	fontManager.emplace_back(smallFont);
	fontManager.emplace_back(normalFont);
	fontManager.emplace_back(titleFont);

	IMG_Init(IMG_INIT_PNG);
	images.emplace_back(IMG_Load("Images/ufo_01_gray.png"));
	images.emplace_back(IMG_Load("Images/ufo_01_purple.png"));
	images.emplace_back(IMG_Load("Images/space.png"));

	crashTexture = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("Images/bakuhatsu_01.png"));

	return true;
}

void GameManager::clockInit()
{
	QueryPerformanceFrequency(&freq);
}

void GameManager::clockStart()
{
	QueryPerformanceCounter(&start);
}

void GameManager::clockEnd()
{
	QueryPerformanceCounter(&end);
}

void GameManager::clockRestart()
{
	deltaTime = 0;
}

void GameManager::fpsControl()
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

TTF_Font* GameManager::getFont(FONTS fonts)
{
	return fontManager[fonts];
}

SDL_Renderer* GameManager::getRenderer()
{
	return gRenderer;
}

SDL_Surface* GameManager::getImages(int index)
{
	return images[index];
}

void GameManager::LoopGame()
{
	int nextSceneNum = 0;

	while (nextSceneNum != -100)
	{
		ClearWindow();

		nextSceneNum = currentScene->Update_Scene();

		SwapScreen();
		fpsControl();

		if (nextSceneNum == -10)
		{
			break;
		}

		if (nextSceneNum != 0)
		{
			changeScene(nextSceneNum);
		}

	}

	DestroyGameManager();
}

void GameManager::ClearWindow()
{
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gRenderer);
}

void GameManager::SwapScreen()
{
	SDL_RenderPresent(gRenderer);
}

void GameManager::changeScene(int nextSceneNum)
{
	std::string path = currentScene->getNextLuaPath();

	switch (nextSceneNum)
	{
	case 1:
		currentScene.reset(new MenuScene(path));
		break;
	case 2:
		currentScene.reset(new MainGame(path));
		break;
	}
}