#include "App.h"
#include "Textures.h"
#include "FontTTF.h"

#include "Defs.h"
#include "Log.h"

#include "SDL_ttf/include/SDL_ttf.h"

#pragma comment( lib, "../Game/Source/External/SDL_ttf/libx86/SDL2_ttf.lib" )

FontTTF::FontTTF()
{
}

FontTTF::~FontTTF()
{
}

SDL_Texture* FontTTF::Print(const char* text, SDL_Color color, _TTF_Font* font, SDL_Texture* tex, int endLine)
{
	SDL_Texture* ret = NULL;
	//SDL_Surface* surface = TTF_RenderText_Blended_Wrapped((font) ? font : defaultFont, text, color, endLine);

	//if (surface == NULL)
	//{
	//	LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	//}
	//else
	//{
	//	ret = app->tex->LoadSurface(surface, tex);
	//	SDL_FreeSurface(surface);
	//}

	return ret;
}

bool FontTTF::CalcSize(const char* text, int& width, int& height, _TTF_Font* font) const
{
	bool ret = false;

	//if (TTF_SizeText((font) ? font : defaultFont, text, & width, & height) != 0)
	//{
	//	LOG("Unable to calc size of text surface! SDL_ttf Error: %s\n", TTF_GetError());
	//}
	//else
	//{
	//	ret = true;
	//}

	return ret;
}

void FontTTF::IntToDynamicString(char* buffer, int k,int lenght) {

	for (int i = 0; i < lenght; i++) {
		buffer[i] = '0';
	}

	buffer[lenght] = 0;

	int i = lenght - 1;
	while (k != 0) {
		if (i < 0) break;
		buffer[i--] += k % 10;
		k /= 10;
	}
}