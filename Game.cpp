#include "Game.h"
#include "TextureLoader.h"
#include "FontHandler.h"
#include "GameObject.h"
SDL_Texture* bgTex;
SDL_Texture* menuBg;
SDL_Texture* start;
SDL_Texture* save;
SDL_Texture* result;
SDL_Texture* quit;
SDL_Surface* textsurface;
SDL_Rect bgR;
SDL_Rect menuR_1, menuR_2, menuR_3, menuR_4;
TTF_Font* font;
SDL_Color text_color;
GameObject* player;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{

}
Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        TTF_Init();
        cout << "All subsystems initialized." << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
        {
            cout << "Window created." << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            cout << "Renderer created." << endl;
        }


    }
    isRunning = true;
    gameStarted = false;
    font = TTF_OpenFont("Xifiction.ttf", 16);
    text_color.r = 140;
    text_color.g = 140;
    text_color.b = 0;
    text_color.a = 255;
    bgTex = TextureLoader::LoadTexture("assets/bground.png");
    bgR.h = 768;
    bgR.w = 1024;
    bgR.x = 0;
    bgR.y = 0;
    menuR_1.h = 80;
    menuR_1.w = 350;
    menuR_1.x = 100;
    menuR_1.y = 100;
    menuR_2.h = 80;
    menuR_2.w = 350;
    menuR_2.x = 100;
    menuR_2.y = 200;
    menuR_3.h = 80;
    menuR_3.w = 350;
    menuR_3.x = 100;
    menuR_3.y = 300;
    menuR_4.h = 80;
    menuR_4.w = 350;
    menuR_4.x = 100;
    menuR_4.y = 400;
    player = new GameObject("assets/ship.png", 0, 0);

}

int Game::menu()
{
    SDL_Event event;
    start = FontHandler::LoadText(font, "Start Game", text_color);
    save = FontHandler::LoadText(font, "Save Game", text_color);
    result = FontHandler::LoadText(font, "Results", text_color);
    quit = FontHandler::LoadText(font, "Quit Game", text_color);
    menuBg = TextureLoader::LoadTexture("assets/menubg.jpg");
    SDL_RenderCopy(renderer, menuBg, NULL, &bgR);
    SDL_RenderCopy(renderer, start, NULL, &menuR_1);
    SDL_RenderCopy(renderer, save, NULL, &menuR_2);
    SDL_RenderCopy(renderer, result, NULL, &menuR_3);
    SDL_RenderCopy(renderer, quit, NULL, &menuR_4);
    cout << gameStarted << endl;

    SDL_FreeSurface(textsurface);
    SDL_RenderPresent(renderer);

while(Game::gameStarted == false)
{

  while(SDL_WaitEvent(&event))
    {
    if(event.type == SDL_KEYDOWN)
    {

        switch(event.key.keysym.sym)
        {
        case SDLK_UP:
            gameStarted = true;
            break;
        case SDLK_RETURN:
            gameStarted = true;
            break;
        case SDLK_DOWN:
            gameStarted = true;
            break;
        default:
            break;
        }
    }
    }
}
}
void Game::update()
{
    player->Update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTex, NULL, &bgR);
    player->Render();
    SDL_RenderPresent(renderer);

}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }

}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game loop cleaned." << endl;
}
