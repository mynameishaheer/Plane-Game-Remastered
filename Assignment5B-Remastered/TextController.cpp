#include "TextController.h"

TextController::TextController()
{

    TTF_Init();

    font = TTF_OpenFont("media/INVASION2000.ttf", 24);
    if (font == NULL) 
    {
        std::cout << ""<< std::endl;
        printf("%s", TTF_GetError());
    }
}

void TextController::showText( SDL_Renderer* gRender, int x, int y, std::string text, int red, int blue, int green ) 
{
 
    SDL_Color fg = { red, blue, green };
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    surface = TTF_RenderText_Solid(font, text.c_str(), fg);
    texture = SDL_CreateTextureFromSurface(gRender, surface);
    SDL_FreeSurface(surface);


    SDL_Rect srcRest;
    SDL_Rect desRect;
    TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);

    srcRest.x = 0;
    srcRest.y = 0;

    desRect.x = x;
    desRect.y = y;

    desRect.w = srcRest.w;
    desRect.h = srcRest.h;
    SDL_RenderCopy(gRender, texture, &srcRest, &desRect);
    SDL_DestroyTexture(texture);

}
