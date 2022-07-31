#include "GameWorld.h"

GameWorld::GameWorld() 
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Game Loop constructed at (%p)", this);
}

GameWorld::~GameWorld() //deconstructor
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Game Loop deconstructed at (%p)", this);
}

void GameWorld::InitGameWorld(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    aTimer.resetTicksTimer(); //frame timer set to 0
	int flags = 0;

	if (fullscreen) 
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) //attempts to init entire SDL Library
	{
		printf("SDL initialised \n");

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags); //window is created
		if (window) 
		{
			printf("Window created! \n");
			renderer = SDL_CreateRenderer(window, -1, 0);
		}
        else
        {
            printf("Window could not be created! \n");
            //return; //program ends if window could not be created
        }

        if (renderer) //if renderer created
        {
            printf("Renderer created! \n"); //message sent to console
        }
        else
        {
            printf("Renderer could not be created! \n"); //message sent to console
            //return; //program ends if renderer could not be created
        }
        isRunning = true; //used to verify program is running
    }
    else
    {
        isRunning = false;
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }
}

void GameWorld::Input()
{
    //function for keys pressed, mouse movement, controller etc.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        if (event.type == SDL_KEYDOWN && event.key.repeat == NULL) //checks to see if a key is pressed and not repeated
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                printf("Escape has been pressed. \n");
                isRunning = false;
                break;
            case SDLK_w:
                printf("W has been pressed. \n");
                break;
            case SDLK_a:
                printf("A has been pressed. \n");
                break;
            case SDLK_s:
                printf("S has been pressed. \n");
                break;
            case SDLK_d:
                printf("D has been pressed. \n");
                break;
            case SDLK_SPACE:
                printf("Space has been pressed. \n");
                break;
            }
        }
    }
}

void GameWorld::Update()
{
    //function for updating game world based on inputs. E.g. updated character positions, game state (win or lose), NPC decisions etc.
}

void GameWorld::Render()
{
    //function for rendering updates onto the screen, such as game states and updated character positions.

    SDL_SetRenderDrawColor(renderer, 0, 0, 120, 255); //set colour of renderer
    SDL_RenderClear(renderer); //clears the window to colour of renderer
    //SDL_RenderPresent(renderer); //shows colour of renderer to screen, always call at end of render function

    SDL_Rect rect;
    rect.x = 30;
    rect.y = 30;
    rect.w = 50;
    rect.h = 50;

    //rect.x++;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderPresent(renderer); //shows colour of renderer to screen

    //block of code below calculates FPS and locks it
    // if less time has passed than allocated block, wait difference
    if (aTimer.getTicks() < DELTA_TIME)
    {
        SDL_Delay(DELTA_TIME - aTimer.getTicks());
    }
}

void GameWorld::CleanUp()
{
    SDL_DestroyWindow(window);
    printf("Window destroyed! \n");
    SDL_DestroyRenderer(renderer);
    printf("Renderer destroyed! \n");
    SDL_Quit();

    printf("All processes eliminated! \n");
}
