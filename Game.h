#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<algorithm>
#include<list>
#include<time.h>
#include<sstream>
#include<string>
#include<fstream>
#include<cstdlib>



using namespace std;
class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void renderMenu();
    void menu();
    void gameover();
    void showResults();
    bool saveGame(void*, void*, void*, void*);
    bool loadGame(int &pposx, int &pposy, int &m1posx, int &m1posy, int &m2posx, int &m2posy, int &m3posx, int &m3posy, int &lhp, int &lsc);
    void handleEvents();
    void update();
    void render();
    void spawnMeteor();
    void renderStatic();

    static SDL_Renderer *renderer;

    bool running()
    {
        return isRunning;
    };
    void clean();
private:
    int menuCounter = 0;
    int score;
    int health;
    bool isRunning;
    bool gameStarted;
    bool gamePaused;
    bool hasAnEnemy;
    SDL_Window *window;
};
