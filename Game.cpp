#include "Game.h"
#include "TextureLoader.h"
#include "FontHandler.h"
#include "GameObject.h"
#include "playerEntity.h"
#include "bulletEntity.h"
#include "meteorEntity.h"


SDL_Texture* bgTex;
SDL_Texture* menuBg;
SDL_Texture* goverBg;
SDL_Texture* topsBg;
SDL_Texture* start;
SDL_Texture* save;
SDL_Texture* result;
SDL_Texture* quit;
SDL_Texture* arrow;
SDL_Texture* playerScore;
SDL_Texture* playerHealth;
SDL_Texture* gameOver;
SDL_Texture* username;
SDL_Texture* topResults;
SDL_Texture* playerResults;

char sScore[255];
char sHp[255];
char playerName[50];
SDL_Texture* explosion;
SDL_Surface* textsurface;
SDL_Rect bgR;
SDL_Rect menuR_1, menuR_2, menuR_3, menuR_4, arrowR;
SDL_Rect scoreR, hpR;
SDL_Rect overR, userR;
SDL_Rect topR, top_result_R;

TTF_Font* font_1;
TTF_Font* font_2;
SDL_Color text_color;
SDL_Color name_color;
SDL_Color tops_color;
int loaded_player_x, loaded_player_y, loaded_meteor1_x, loaded_meteor1_y,
    loaded_meteor2_x, loaded_meteor2_y, loaded_meteor3_x, loaded_meteor3_y,
    loaded_health, loaded_score;
playerEntity* player = nullptr;

meteorEntity* meteor_1 = nullptr;
meteorEntity* meteor_2 = nullptr;
meteorEntity* meteor_3 = nullptr;
bulletEntity* shot = nullptr;

list <bulletEntity*> bulletQueue;



const Uint8 *state = SDL_GetKeyboardState(NULL);
int randEv;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{

}
Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    score = 0;
    health = 3;
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
    }else
    {
        cout << "Unitialization Error." << endl;
    }
    isRunning = true;
    gameStarted = false;
    gamePaused = false;
    hasAnEnemy = true;
    font_1 = TTF_OpenFont("Xifiction.ttf", 64);
    font_2 = TTF_OpenFont("14334.ttf", 64);

    text_color = {180, 140, 55, 255};
    name_color = {255, 50, 50, 255};
    tops_color = {240, 195, 0, 255};

    bgTex = TextureLoader::LoadTexture("assets/bground.png");
    save = FontHandler::LoadText(font_1, "Load Game", text_color);
    result = FontHandler::LoadText(font_1, "Results", text_color);
    quit = FontHandler::LoadText(font_1, "Quit Game", text_color);
    menuBg = TextureLoader::LoadTexture("assets/menubg.jpg");
    goverBg = TextureLoader::LoadTexture("assets/gameover.jpg");
    topsBg = TextureLoader::LoadTexture("assets/terra.jpg");
    arrow = TextureLoader::LoadTexture("assets/chooser.png");

    explosion = TextureLoader::LoadTexture("assets/explosion.png");

    sprintf(sScore, "%d", score);
    sprintf(sHp, "%d", health);

    playerHealth = FontHandler::LoadText(font_2, sScore, text_color);
    playerScore = FontHandler::LoadText(font_2, sHp, text_color);

    bgR = {0, 0, 1336, 768};
    menuR_1 = {100, 100, 350, 80};
    menuR_2 = {100, 200, 350, 80};
    menuR_3 = {100, 300, 350, 80};
    menuR_4 = {100, 400, 350, 80};
    overR = {180, 50, 1000, 100};
    userR = {300, 200, 50, 50};
    arrowR = {475, 100, 80, 80};
    scoreR = {100, 50, 100, 80};
    hpR = {1200, 50, 100, 80};
    topR = {180, 50, 1000, 100};
    top_result_R = {180, 180, 300, 80};

    player = new playerEntity("assets/ship.png", 10, 100);
    meteor_1 = new meteorEntity("assets/meteor.png", 500, rand()%130);
    meteor_2 = new meteorEntity("assets/meteor.png", 500, rand()%386 + 256);
    meteor_3 = new meteorEntity("assets/meteor.png", 500, rand()%567 + 50);

    gameOver = FontHandler::LoadText(font_1, "You lose. Write your name, and press Enter", text_color);
    topResults = FontHandler::LoadText(font_1, "Five last player results:", name_color);

}

bool Game::loadGame(int &pposx, int &pposy, int &m1posx, int &m1posy, int &m2posx, int &m2posy, int &m3posx, int &m3posy, int &lhp, int &lsc)
{
    char buff[10];
    ifstream fin("save.txt");

        fin.getline(buff, sizeof(buff));
        pposx = atoi(buff);
        cout << "Loaded player xpos: " << pposx << endl;

        fin.getline(buff, sizeof(buff));
        pposy = atoi(buff);
        cout << "Loaded player ypos: " << pposy << endl;

        fin.getline(buff, sizeof(buff));
        m1posx = atoi(buff);
        cout << "Loaded meteor_1 xpos: " << m1posx << endl;

        fin.getline(buff, sizeof(buff));
        m1posy = atoi(buff);
        cout << "Loaded meteor_1 ypos: " << m1posy << endl;

        fin.getline(buff, sizeof(buff));
        m2posx = atoi(buff);
        cout << "Loaded meteor_2 xpos: " << m2posx << endl;

        fin.getline(buff, sizeof(buff));
        m2posy = atoi(buff);
        cout << "Loaded meteor_2 ypos: " << m2posy << endl;

        fin.getline(buff, sizeof(buff));
        m3posx = atoi(buff);
        cout << "Loaded meteor_3 xpos: " << m3posx << endl;

        fin.getline(buff, sizeof(buff));
        m3posy = atoi(buff);
        cout << "Loaded meteor_3 ypos: " << m3posy << endl;

        fin.getline(buff, sizeof(buff));
        lhp = atoi(buff);
        cout << "Loaded health: " << lhp << endl;

        fin.getline(buff, sizeof(buff));
        lsc = atoi(buff);
        cout << "Loaded score: " << lsc << endl;

    fin.close();
    return true;
}

bool Game::saveGame(void* player, void* m1, void* m2, void* m3)
{
    playerEntity* temp_player = (playerEntity*)player;
    meteorEntity* temp_m1 = (meteorEntity*)m1;
    meteorEntity* temp_m2 = (meteorEntity*)m2;
    meteorEntity* temp_m3 = (meteorEntity*)m3;
    cout << "Saved player xpos: " << temp_player->retXpos() << endl;
    cout << "Saved player ypos: " << temp_player->retYpos() << endl;
    cout << "Saved meteor_1 xpos: " << temp_m1->retXpos() << endl;
    cout << "Saved meteor_1 ypos: " << temp_m1->retYpos() << endl;
    cout << "Saved meteor_2 xpos: " << temp_m2->retXpos() << endl;
    cout << "Saved meteor_2 ypos: " << temp_m2->retYpos() << endl;
    cout << "Saved meteor_3 xpos: " << temp_m3->retXpos() << endl;
    cout << "Saved meteor_3 ypos: " << temp_m3->retYpos() << endl;
    ofstream fout("save.txt");
    fout << temp_player->retXpos() << endl;
    fout << temp_player->retYpos() << endl;
    fout << temp_m1->retXpos() << endl;
    fout << temp_m1->retYpos() << endl;
    fout << temp_m2->retXpos() << endl;
    fout << temp_m2->retYpos()  << endl;
    fout << temp_m3->retXpos()  << endl;
    fout << temp_m3->retYpos()<< endl;
    fout << health << endl;
    fout << score << endl;
    fout.close();
    return true;
}

void Game::renderMenu()
{
    SDL_RenderCopy(renderer, menuBg, NULL, &bgR);
    SDL_RenderCopy(renderer, start, NULL, &menuR_1);
    SDL_RenderCopy(renderer, save, NULL, &menuR_2);
    SDL_RenderCopy(renderer, result, NULL, &menuR_3);
    SDL_RenderCopy(renderer, quit, NULL, &menuR_4);
    SDL_RenderCopy(renderer, arrow, NULL, &arrowR);
}

void Game::menu()
{

    SDL_Event event;
    if(gamePaused == false)
    {
        start = FontHandler::LoadText(font_1, "Start New Game", text_color);
        save = FontHandler::LoadText(font_1, "Load Game", text_color);
        health = 3;
        score = 0;
    }else
    {
        start = FontHandler::LoadText(font_1, "Continue Game", text_color);
        save = FontHandler::LoadText(font_1, "Save Game", text_color);
    }
    renderMenu();
    cout << gameStarted << endl;
    SDL_FreeSurface(textsurface);
    SDL_RenderPresent(renderer);

while(gameStarted == false)
{

  while(SDL_PollEvent(&event))
    {
    if(event.type == SDL_KEYDOWN)
    {

        switch(event.key.keysym.sym)
        {
        case SDLK_UP:
            if(menuCounter > 0)
            {
                SDL_RenderClear(renderer);
                arrowR.y -= 100;
                renderMenu();
                SDL_RenderPresent(renderer);
                menuCounter--;
                cout << menuCounter << endl;

            }
            break;
        case SDLK_RETURN:
            switch(menuCounter)
            {
            case 0:
                gameStarted = true;
                break;
            case 1:
                if(gamePaused == true)
                    saveGame(player, meteor_1, meteor_2, meteor_3);
                else
                {
                    loadGame(loaded_player_x, loaded_player_y, loaded_meteor1_x, loaded_meteor1_y,
                             loaded_meteor2_x, loaded_meteor2_y, loaded_meteor3_x, loaded_meteor3_y,
                             loaded_health, loaded_score);
                    player = new playerEntity("assets/ship.png", loaded_player_x, loaded_player_y);
                    meteor_1 = new meteorEntity("assets/meteor.png", loaded_meteor1_x, loaded_meteor1_y);
                    meteor_2 = new meteorEntity("assets/meteor.png", loaded_meteor2_x, loaded_meteor2_y);
                    meteor_3 = new meteorEntity("assets/meteor.png", loaded_meteor3_x, loaded_meteor3_y);
                    health = loaded_health;
                    score = loaded_score;
                    gameStarted = true;
                }
                break;
            case 2:
                showResults();
                break;
            case 3:
                clean();
                break;
            }
            break;
        case SDLK_DOWN:
            if(menuCounter < 3)
            {
                SDL_RenderClear(renderer);
                arrowR.y += 100;
                renderMenu();
                SDL_RenderPresent(renderer);
                menuCounter++;
                cout << menuCounter << endl;
            }
            break;
        default:
            break;
        }
    }
    }
}

}

void Game::showResults()
{
    int counterTops = 0;
    SDL_RenderCopy(renderer, topsBg, NULL, &bgR);
    SDL_RenderCopy(renderer, topResults, NULL, &topR);
    SDL_RenderPresent(renderer);
    char buff[50];
    char
    ifstream fin("results.txt");
    while(1)
    {
        if(fin.eof()) break;
        fin.getline(buff, sizeof(buff));
        if(!fin.eof())
        {
            cout << "Name: " << buff << endl;
            topResults = FontHandler::LoadText(font_1, buff, tops_color);
            SDL_RenderCopy(renderer, topResults, NULL, &top_result_R);
            SDL_RenderPresent(renderer);
            top_result_R.y += 60;
        }
        fin.getline(buff, sizeof(buff));
        if(!fin.eof())cout << "Score: " << buff << endl;
        counterTops++;
        if(counterTops == 5) break;
    }
    fin.close();
    SDL_Delay(5000);
    menu();
}

void Game::gameover()
{
    userR.x = 300;
    free(playerName);

    SDL_Event ev;
    char symbol;
    bool flag = true;
    int i=0;
    char letter[50];
    gameStarted = false;
    gamePaused = false;
    SDL_RenderCopy(renderer, goverBg, NULL, &bgR);
    SDL_RenderCopy(renderer, gameOver, NULL, &overR);
    SDL_RenderPresent(renderer);

    while (flag)
    {

        while( SDL_PollEvent( &ev )&& flag )
        {
            if( ev.type == SDL_QUIT ) flag = false;
            if (( ev.type == SDL_KEYDOWN ) && (ev.key.keysym.sym == SDLK_RETURN )) flag = false;
            else
        {
            if (( ev.type == SDL_KEYDOWN ) && (ev.key.keysym.sym != SDLK_BACKSPACE ))
            {
                symbol = (char)ev.key.keysym.sym;
                playerName[i++] = symbol;
                letter[0] = symbol;
                username = FontHandler::LoadText(font_1, letter, name_color);
                SDL_RenderCopy(renderer, username, NULL, &userR);
                userR.x += 50;
                SDL_RenderPresent(renderer);
            }
            if (( ev.type == SDL_KEYDOWN )&& (ev.key.keysym.sym == SDLK_BACKSPACE ))
            {
                playerName[--i]=0;
            }
        }
        }
     }

    ofstream fout("results.txt", ios_base::app);
    fout << playerName << "       " << score << endl;
    fout.close();
    gamePaused = false;
    menu();
}

void Game::update()
{
    player->Update();
    if(!bulletQueue.empty())
    {
        for(bulletEntity* shot : bulletQueue)
        {
            shot->Update();
            if(shot->objCollision(meteor_1))
            {
                free(meteor_1);
                meteor_1 = new meteorEntity("assets/meteor.png", 1180, rand()%130);
                score += 50;
                cout << "Score: " << score << endl;
                bulletQueue.remove(shot);
                free(shot);
                break;
            }

            if(shot->objCollision(meteor_2))
            {

                free(meteor_2);
                meteor_2 = new meteorEntity("assets/meteor.png", 1186, rand()%386 + 256);
                score += 50;
                cout << "Score: " << score << endl;
                bulletQueue.remove(shot);

                break;
            }

            if(shot->objCollision(meteor_3))
            {
                free(meteor_3);
                meteor_3 = new meteorEntity("assets/meteor.png", 1186, rand()%567 + 50);
                score += 50;
                cout << "Score: " << score << endl;
                bulletQueue.remove(shot);
                break;
            }

            if(shot->retXpos() > 1336)
                bulletQueue.remove(shot);
        }
    }


    if(meteor_1->Update(player))
    {
        free(meteor_1);
        meteor_1 = new meteorEntity("assets/meteor.png", 1180, rand()%130);
        health--;
    }

    if(meteor_2->Update(player))
    {
        free(meteor_2);
        meteor_2 = new meteorEntity("assets/meteor.png", 1186, rand()%386 + 256);
        health--;
    }

    if(meteor_3->Update(player))
    {
        free(meteor_3);
        meteor_3 = new meteorEntity("assets/meteor.png", 1186, rand()%567 + 50);
        health--;
    }

}

void Game::renderStatic()
{
    delete sScore;
    delete sHp;
    sprintf(sScore, "%d", score);
    sprintf(sHp, "%d", health);

    SDL_DestroyTexture(playerHealth);
    SDL_DestroyTexture(playerScore);
    playerHealth = FontHandler::LoadText(font_2, sScore, text_color);
    playerScore = FontHandler::LoadText(font_2, sHp, text_color);

    SDL_RenderCopy(renderer, bgTex, NULL, &bgR);
    SDL_RenderCopy(renderer, playerHealth, NULL, &hpR);
    SDL_RenderCopy(renderer, playerScore, NULL, &scoreR);
}

void Game::render()
{
    SDL_RenderClear(renderer);
    renderStatic();
    player->Render();
    if(!bulletQueue.empty())
    {
        for(bulletEntity* shot : bulletQueue)
        {
            shot->Render();
        }
    }


    meteor_1->Render();
    meteor_2->Render();
    meteor_3->Render();
    SDL_RenderPresent(renderer);
}

void Game::spawnMeteor()
{
    if(meteor_1->retXpos() <= -10)
        meteor_1 = new meteorEntity("assets/meteor.png", 1180, rand()%130);
    if(meteor_2->retXpos() <= -10)
        meteor_2 = new meteorEntity("assets/meteor.png", 1180, rand()%386 + 256);
    if(meteor_3->retXpos() <= -10)
        meteor_3 = new meteorEntity("assets/meteor.png", 1180, rand()%567 + 50);
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
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                gamePaused = true;
                gameStarted = false;
                menu();
                break;
            case SDLK_SPACE:
                 bulletQueue.push_back(shot = new bulletEntity("assets/shot.png", player->retXpos() + player->retHeight(), player->retYpos() + player->retWidth()/4));
                 break;
            }
        default:
            break;
    }
    if(state[SDL_SCANCODE_W])
        player->moveUp();
    else if(state[SDL_SCANCODE_S])
        player->moveDown();
    spawnMeteor();
    if(health == 0)
    {
        gameover();
    }
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game loop cleaned." << endl;
}
