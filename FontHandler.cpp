#include "FontHandler.h"

SDL_Texture* FontHandler::LoadText( TTF_Font* font_p, const char* text, SDL_Color color_p)
{
    SDL_Surface* textsurface = TTF_RenderUTF8_Blended(font_p, text, color_p);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, textsurface);
    return tex;
}
