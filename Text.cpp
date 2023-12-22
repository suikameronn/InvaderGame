#include"Text.h"

Text::Text()
{
	color = nullptr;
	gFont = nullptr;
	mWidth = 0;
	mHeight = 0;
	mTexture = nullptr;
	renderQuad = { 0 };
	textSurface = nullptr;
}

Text::Text(TTF_Font* font)
{
	color = nullptr;
	gFont = nullptr;
	mWidth = 0;
	mHeight = 0;
	mTexture = nullptr;
	renderQuad = { 0 };
	textSurface = nullptr;

	gFont = font;
	changed = true;
}

Text::~Text()
{
	TTF_CloseFont(gFont);
	SDL_DestroyTexture(mTexture);
	SDL_FreeSurface(textSurface);
}

void Text::setFont(TTF_Font* font)
{
	gFont = font;
	changed = true;
}

void Text::setText(string str)
{
	text = str;
	changed = true;
}

void Text::setColor(SDL_Color* col)
{
	color = col;
	changed = true;
}



void Text::drawObjects(SDL_Renderer* gRenderer)
{
	actMove();

	if (!createdTex)
	{
		textSurface = TTF_RenderText_Solid(gFont, text.c_str(), *color);//文字をレンダリングしたサーフェスを作成
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);//テクスチャの作成
		createdTex = true;
	}

	if (changed)
	{
		mWidth = textSurface->w;
		mHeight = textSurface->h;

		renderQuad = { (int)pos->x, (int)pos->y, mWidth, mHeight };

		//Set clip rendering dimensions
		if (clip != nullptr)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
	}
	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);

	changed = false;
}
