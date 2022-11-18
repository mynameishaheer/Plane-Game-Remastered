#pragma once
#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>

class TextController
{
    TTF_Font* font;

public:

    SDL_Renderer* renderer;
    TextController();

    uint32_t deltaTime = 0;

    void showText(SDL_Renderer* gRender, int x, int y, std::string text, int red, int blue, int green);

};


