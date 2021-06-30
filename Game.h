#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>

using namespace std;
class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    int menu();
    void handleEvents();
    void update();
    void render();
    void clean();

    static SDL_Renderer *renderer;

    bool running()
    {
        return isRunning;
    };

private:
    int cnt = 0;
    bool isRunning;
    bool gameStarted;
    SDL_Window *window;
};
