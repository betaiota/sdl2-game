#include "Game.h"

Game *gameLoop = nullptr;

int main(int argc, char* args[])
{
    srand(4541);
    const int FPS = 125;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    gameLoop = new Game();
    gameLoop->init("Course Work", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1336,768,false);
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
    return 0;
}
