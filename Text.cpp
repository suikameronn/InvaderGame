#include"Text.h"

Text::Text()
{

}

Text::Text(TTF_Font* font)
{
	gFont = font;
}

void Text::setFont(TTF_Font* font)
{
	gFont = font;
}

void Text::setText(string str)
{
	text = str;
}

void Text::setColor(SDL_Color col)
{
	color = col;
}

void Text::draw(SDL_Renderer* gRenderer)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);//文字をレンダリングしたサーフェスを作成
	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);//テクスチャの作成
	
	mWidth = textSurface->w;
	mHeight = textSurface->h;

	SDL_FreeSurface(textSurface);

	SDL_Rect renderQuad = { pos->x, pos->y, mWidth, mHeight};

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

