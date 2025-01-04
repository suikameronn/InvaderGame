#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <windows.h>

#include"Title.h"
#include"CourseSelect.h"
#include"MainGame.h"

using namespace std;

const int screen_width = SCREEN_WIDTH;
const int screen_height = SCREEN_HEIGHT;

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

class GameManager
{
private:

	static GameManager* instance;

	int fps;
	bool quiet;

	GameManager();
	~GameManager();

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

	vector<TTF_Font*> fontManager;
	TTF_Font* smallFont;
	TTF_Font* normalFont;
	TTF_Font* titleFont;

	std::vector<SDL_Surface*> images;

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
	void changeScene(int nextSceneNum);

public:

	std::unique_ptr<Scene> currentScene;

	static GameManager* GetInstance()
	{
		if (instance)
		{
			return instance;
		}
		else
		{
			instance = new GameManager();
		}
	}

	SDL_Texture* crashTexture;

	void DestroyGameManager();

	void LoopGame();
	void quietGame() { quiet = true; }
	void ClearWindow();
	void SwapScreen();

	SDL_Renderer* getRenderer() { return gRenderer; }
};