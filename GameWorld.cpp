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
	int flags = 0;
	if (fullscreen) 
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) //attempts to init entire SDL Library
	{
		printf("SDL initialised \n");
        aTimer.resetTicksTimer(); //frame timer set to 0
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags); //window is created
		if (window) 
		{
			printf("Window created! \n");
            SDL_GetWindowSize(window, &width, &height);
            printf("Width of the window: %i \n", width);
            printf("Height of the window: %i \n", height);

			//renderer = SDL_CreateRenderer(window, -1, 0);
            aBallPaddleBrick.aRenderer = SDL_CreateRenderer(window, -1, 0);
            SDL_SetRenderDrawBlendMode(aBallPaddleBrick.aRenderer, SDL_BLENDMODE_BLEND);
		}
        else
        {
            printf("Window could not be created! \n");
            //return; //program ends if window could not be created
        }

        //if (renderer) //if renderer created
        if(aBallPaddleBrick.aRenderer)
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
    aBallPaddleBrick.InitVariables();
    aBallPaddleBrick.ResetLevel(true);
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
                globalKeys[SDLK_ESCAPE] = true;
                isRunning = false;
                break;
            case SDLK_w:
                printf("W has been pressed. \n");
                globalKeys[SDLK_w] = true;
                break;
            case SDLK_a:
                printf("A has been pressed. \n");
                globalKeys[SDLK_a] = true;
                aBallPaddleBrick.paddle.x -= PADDLE_SPEED;
                break;
            case SDLK_s:
                printf("S has been pressed. \n");
                globalKeys[SDLK_s] = true;
                break;
            case SDLK_d:
                printf("D has been pressed. \n");
                globalKeys[SDLK_d] = true;
                aBallPaddleBrick.paddle.x += PADDLE_SPEED;
                break;
            case SDLK_SPACE:
                printf("Space has been pressed. \n");
                globalKeys[SDLK_SPACE] = true;
                break;
            }
        }

        if (event.type == SDL_KEYUP && event.key.repeat == NULL) //checks to see if a key is pressed and not repeated
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                printf("Escape has been unpressed. \n");
                globalKeys[SDLK_ESCAPE] = false;
                isRunning = false;
                break;
            case SDLK_w:
                printf("W has been unpressed. \n");
                globalKeys[SDLK_w] = false;
                break;
            case SDLK_a:
                printf("A has been unpressed. \n");
                globalKeys[SDLK_a] = false;
                aBallPaddleBrick.paddle.x = PADDLE_SPEED; //paddle speed reset once button has been unpressed
                break;
            case SDLK_s:
                printf("S has been unpressed. \n");
                globalKeys[SDLK_s] = false;
                break;
            case SDLK_d:
                printf("D has been unpressed. \n");
                globalKeys[SDLK_d] = false;
                aBallPaddleBrick.paddle.x = PADDLE_SPEED;
                break;
            case SDLK_SPACE:
                printf("Space has been unpressed. \n");
                globalKeys[SDLK_SPACE] = false;
                break;
            }
        }
        
    }
}

void GameWorld::Update()
{
    if (aTimer.getTicks() < DELTA_TIME)
    {
        SDL_Delay(DELTA_TIME - aTimer.getTicks());
    }
    aBallPaddleBrick.UpdateBallAndPaddle();
}

void GameWorld::Render()
{
    //function for rendering updates onto the screen, such as game states and updated character positions.

    //SDL_SetRenderDrawColor(aBallPaddleBrick.aRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE); //set colour of renderer
    //SDL_RenderClear(aBallPaddleBrick.aRenderer); //clears the window to colour of renderer
    //aBallPaddleBrick.RenderBallPaddleBrick();
    //SDL_RenderPresent(aBallPaddleBrick.aRenderer); //shows renderer to screen
    aBallPaddleBrick.RenderBallPaddleBrick();
    
}

void GameWorld::CleanUp()
{
    SDL_DestroyWindow(window);
    printf("Window destroyed! \n");
    SDL_DestroyRenderer(aBallPaddleBrick.aRenderer);
    printf("Renderer destroyed! \n");
    SDL_Quit();
    printf("All processes eliminated! \n");
}
