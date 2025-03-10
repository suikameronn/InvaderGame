#include"Text.h"

Text::Text()
{
	gFont = nullptr;
	mWidth = 0;
	mHeight = 0;
	mTexture = nullptr;
	clip = nullptr;
	renderQuad = { 0 };
	textSurface = nullptr;

	type = TEXT;
}

Text::Text(TTF_Font* font)
{
	gFont = nullptr;
	mWidth = 0;
	mHeight = 0;
	mTexture = nullptr;
	clip = nullptr;
	renderQuad = { 0 };
	textSurface = nullptr;

	gFont = font;
	changed = true;

	type = TEXT;
}

Text::~Text()
{
	SDL_DestroyTexture(mTexture);
	delete clip;
	//SDL_FreeSurface(textSurface);
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
	createdTex = false;
}

void Text::setColor(unsigned char r, unsigned char g, unsigned char b)
{
	color = { r,g,b };
	changed = true;
}

string Text::getText()
{
	return text;
}

float Text::getBottom()
{
	return pos->y + mHeight;
}

void Text::Update()
{
	if (disappearInterval > 0.0f)
	{
		disappear();
	}
}

void Text::drawObjects(SDL_Renderer* gRenderer)
{
	actMove();

	if (!visible)
	{
		return;
	}

	if (!createdTex)
	{
		textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);//文字をレンダリングしたサーフェスを作成
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

void Text::drawObjectsScroll(SDL_Renderer* gRenderer, Position* scrollPos,Position* offSet)
{
	actMove();

	if (!createdTex)
	{
		textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);//文字をレンダリングしたサーフェスを作成
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);//テクスチャの作成
		createdTex = true;
	}

	if (changed)
	{
		mWidth = textSurface->w;
		mHeight = textSurface->h;

		if (clip == nullptr)
		{
			clip = new SDL_Rect();
		}

		if (pos->y < 0)
		{
			*clip = { 0,-(int)pos->y, mWidth, mHeight + (int)pos->y };
			renderQuad = { int(pos->x + scrollPos->x), int(pos->y + scrollPos->y) - (int)pos->y, clip->w, clip->h };
		}
		else if(pos->y + mHeight > offSet->y)
		{
			*clip = { 0, 0,mWidth, int(mHeight - (pos->y + mHeight - offSet->y))};
			renderQuad = { int(pos->x + scrollPos->x), int(pos->y + scrollPos->y), clip->w, clip->h };
		}
		else
		{
			*clip = { 0,0, mWidth, mHeight };
			renderQuad = { int(pos->x + scrollPos->x), int(pos->y + scrollPos->y), clip->w, clip->h };
		}
	}
	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
	changed = false;
}
