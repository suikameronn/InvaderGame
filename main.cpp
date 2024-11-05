#define main SDL_main

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include<iostream>
#include <string>
#include<memory>

#include"GameManager.h"

struct fontDeleter
{
	void operator()(TTF_Font* font)
	{
		TTF_CloseFont(font);
	}
};

/**
*   ƒƒCƒ“
*/
int main(int argc, char** argv) {

	GameManager* manager = GameManager::GetInstance();

	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(244);

	manager->LoopGame();
	
	return 0;
}