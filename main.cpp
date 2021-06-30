#include "Game.h"


Game *gameLoop = NULL;

int main(int argc, char* args[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    gameLoop = new Game();
    gameLoop->init("Course Work", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,768,false);
    gameLoop->menu();
    while(gameLoop->running())
    {


        frameStart = SDL_GetTicks();

        gameLoop->handleEvents();
        gameLoop->update();
        gameLoop->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    gameLoop->clean();
    SDL_Delay(3000);
    return 0;
}
