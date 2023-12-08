#include"Text.h"

Text::Text()
{

}

Text::Text(TTF_Font* font)
{
	gFont = font;
	changed = true;
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
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
	}
	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);

	changed = false;
}
