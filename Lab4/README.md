# Lab 4 - Tic-Tac-Toe
## Pretext
In this lab you will learn how to:
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

![Includes](/Lab4/media/includes.png)

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
![Constructor](/Lab4/media/constructor.png)

#### Initialise Board
![InitialiseBoard](/Lab4/media/initialiseBoard.png)

#### Clean Up
![](/Lab4/media/cleanUp.png)

#### Handle Input
Parsing mouse input with ```void HandleInput()```:

![HandleInput](/Lab4/media/handleInput.png)

#### Update
![Update](/Lab4/media/update.png)

#### Render
![Render](/Lab4/media/render.png)

#### Draw Board
![DrawBoard](/Lab4/media/drawBoard.png)

#### Check Win
![CheckWin](/Lab4/media/checkWin.png)

#### Is Running
![IsRunning](/Lab4/media/isRunning.png)

#### Main Game Loop
![MainGameLoop](/Lab4/media/main.png)

#### Task 1
The rendering of the X and O fonts have some issues associated with the data type. Fix this problem to render it properly.

#### Task 2
Tweak the rendering coordinates within the screen so the X and O render in the middle of the cells, and the “Gameover” or “Draw” texts render at the middle of the screen.