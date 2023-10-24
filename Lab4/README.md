# Lab 4 - Tic-Tac-Toe
## Pretext
- Incorporate the SDL framework into your C++ project
- Utilise mouse input within the SDL framework for game actions
- Print fonts on the SDL window screen
## SDL Framework
- Download [SDL]() & [SDL TTF]() dev packages.
- Extract to your library folder (remember the path). Start a C++ project and copy the 2 DLL files into the CPP folder.

![CPPFolder.png](/Lab4/media/CPPFolder.png)

- Look for a TTF font of your liking, download it and place the TTF file in your CPP folder.
- Right-click on your project solution properties and add the 
    - Additional include directories for both SDL and SDL_TTF
    - Add the additional library directories for the lib\x64 directories for both SDL and SDL_TTF
    - Add the additional dependencies for SDL2.lib, SDL2main.lib and SDL2_ttf.lib.
- Add the SDL and SDL_TTF headers.

**CPP**
```c++
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;
```

- Run the program to see if the links are correct.

## Tic-Tac-Toe Class
### Public Members
- Constructor
- Void InitializeBoard()
- Void CleanUp()
- Void HandleInput()
- Void Update()
- Void Render()
- Void DrawBoard()
- Void CheckWin()
- bool IsRunning() const
### Private Members
- const int SCREEN_WIDTH = 600;
- const int SCREEN_HEIGHT = 600;
- const int GRID_SIZE = 3;
- const int CELL_SIZE = SCREEN_WIDTH / GRID_SIZE;
- const int RECT_SIZE = CELL_SIZE;
- const int FONT_SIZE = 72;
- SDL_Window* window;
- SDL_Renderer* renderer;
- TTF_Font* font;
- char board[3][3];
- bool isRunning;
- bool isXTurn;
- bool gameOver;
- bool draw;
- char currentPlayer;
- SDL_Color tickColor = { 0,255,0,128 };
- SDL_Color textColor = { 255,0,0,128 };
### Method Details
#### Constructor
```c++
TicTacToe() : isRunning(true), isXTurn(true), gameOver(false), draw(false), currentPlayer('X'), window(nullptr), renderer(nullptr), font(nullptr) {};
void Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL_Error:" << SDL_GetError() << endl;
        isRunning = false;
        return;
    }
    if (TTF_Init() == -1) {
        cerr << "SDL_ttf could not initialize! TTF_Error:" << TTF_GetError() << endl;
        isRunning = false;
        return;
    }
    window = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cerr << "Window cannot be created! SDL_ERROR:" << SDL_GetError() << endl;
        isRunning = false;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cerr << "Renderer cannot be created! SDL_ERROR:" << SDL_GetError() << endl;
        isRunning = false;
        return;
    }
    font = TTF_OpenFont("Freedom-10eM.ttf", FONT_SIZE);
    if (font == nullptr) {
        cerr << "Font cannot be loaded! TTF_ERROR:" << TTF_GetError() << endl;
        isRunning = false;
        return;
    }
    InitializeBoard();
}
```
#### Initialise Board
```c++
void InitializeBoard() {
    for (int i=0;i<GRID_SIZE;i++)
        for (int j = 0; j < GRID_SIZE; j++)
            board[i][j] = ' ';
}
```
#### Clean Up
```c++
void CleanUp() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
```
#### Handle Input
Parsing mouse input with ```void HandleInput()```:
```c++
void HandleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (!gameOver && event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            //identify which cell was clicked
            int cellX = x / CELL_SIZE;
            int cellY = y / CELL_SIZE;
            if (cellX >= 0 && cellX < GRID_SIZE && cellY >= 0 && cellY < GRID_SIZE) {
                if (board[cellY][cellX] == ' ') {
                    board[cellY][cellX] == currentPlayer;
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            }
            cout << "(CellY" << cellY << ",cellX:" << cellX << ") clicked" << endl;
        }
    }
}
```
#### Update
```c++
void Update() {
    CheckWin();
}
```
#### Render
```c++
void Render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    DrawBoard();
    if (gameOver) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, "GameOver", textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect{ SCREEN_HEIGHT / 2,SCREEN_WIDTH / 2,FONT_SIZE,FONT_SIZE };
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
    else if (draw) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Draw", textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect{ SCREEN_HEIGHT / 2,SCREEN_WIDTH / 2,FONT_SIZE,FONT_SIZE};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
    SDL_RenderPresent(renderer);
}
```
#### Draw Board
```c++
void DrawBoard() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            char cellValue = board[y][x];
            if (cellValue == 'X' || cellValue == 'O') {
                int textX = (x * CELL_SIZE) - (FONT_SIZE / 2);
                int textY = (y * CELL_SIZE) - (FONT_SIZE / 2);
                
                SDL_Surface* surface = TTF_RenderText_Solid(font, &cellValue, textColor);
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_Rect textRect{ textX,textY,FONT_SIZE,FONT_SIZE };
                SDL_RenderCopy(renderer, texture, NULL, &textRect);
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int x = 0; x <= GRID_SIZE; x++) {
        int xPos = x * CELL_SIZE;
        SDL_RenderDrawLine(renderer, xPos, 0, xPos, SCREEN_HEIGHT);
    }
    for (int y = 0; y <= GRID_SIZE; y++) {
        int yPos = y * CELL_SIZE;
        SDL_RenderDrawLine(renderer, 0, yPos, SCREEN_WIDTH, yPos);
    }
    //Present the renderer
    SDL_RenderPresent(renderer);
}
```
#### Check Win
```c++
void CheckWin() {
    //check rows and columns
    for (int i = 0; i < GRID_SIZE; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            gameOver = true;
            return;
        }
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            gameOver = true;
            return;
        }
    }
    //check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
            gameOver = true;
            return;
        }
        if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
            gameOver = true;
            return;
        }
    //check for draw conditions
    draw = true;
    for (int x=0;x<GRID_SIZE;x++)
        for (int y = 0; y < GRID_SIZE; y++) {
            if (board[y][x] == ' ') {
                draw = false;
                return;
            }
        }
}
```
#### Is Running
```c++
bool IsRunning()const {
    return isRunning;
}
```
#### Main Game Loop
```c++
int main(int argc, char *argv[])
{
    TicTacToe game;
    game.Initialize();
    while (game.IsRunning()) {
        game.HandleInput();
        game.Update();
        game.Render();
    }
    game.CleanUp();
    return 0;
}
```

#### Task 1
The rendering of the X and O fonts have some issues associated with the data type. Fix this problem to render it properly.

#### Task 2
Tweak the rendering coordinates within the screen so the X and O render in the middle of the cells, and the “Gameover” or “Draw” texts render at the middle of the screen.