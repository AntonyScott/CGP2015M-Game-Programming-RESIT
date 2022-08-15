#include "GameWorld.h"

GameWorld::GameWorld() 
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Game Loop constructed at (%p)", this);
}

GameWorld::~GameWorld() //deconstructor
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Game Loop deconstructed at (%p)", this);
}
Uint32 GameWorld::TimerCallbackFunction(Uint32 interval, void* param)
{
    SDL_Event event;
    SDL_UserEvent userevent;
    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = (void*)"Timer Countdown";
    userevent.data2 = NULL;
    event.type = SDL_USEREVENT;
    event.user = userevent;
    SDL_PushEvent(&event);
    return(interval);
}

Uint32 GameWorld::TimerCallbackFunctionCB(Uint32 interval, void* param)
{
    return ((GameWorld*)param)->TimerCallbackFunction(interval, param);
}
void GameWorld::InitGameWorld(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    SDL_AddTimer(1000, &TimerCallbackFunctionCB, NULL);
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
            return; //program ends if window could not be created
        }
        //if renderer created
        if(aBallPaddleBrick.aRenderer)
        {
            printf("Renderer created! \n"); //message sent to console
        }
        else
        {
            printf("Renderer could not be created! \n"); //message sent to console
            //return; //program ends if renderer could not be created
        }
        if (SDL_Init(SDL_INIT_AUDIO) == -1) 
        {
            SDL_Quit();
        }
        isRunning = true; //used to verify program is running
    }
    else
    {
        isRunning = false;
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }
    

    aBallPaddleBrick.InitVariables();
    
    spaceBG = new SimpleSprite(0,0,480,640);
    spaceBG->load(aBallPaddleBrick.aRenderer, "Content/Space.jpg", false);

    splashScreen = new SimpleSprite(0, 0, 480, 640);
    splashScreen->load(aBallPaddleBrick.aRenderer, "Content/SplashScreen.png", false);
}

void GameWorld::Input()
{
    SDL_Event event;
    const Uint8* keyboardStates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (keyboardStates[SDL_SCANCODE_ESCAPE])
        {
            printf("Escape has been pressed. \n");
            globalKeys[SDLK_ESCAPE] = true;
            isRunning = false;
        }
        if (keyboardStates[SDL_SCANCODE_A])
        {
            printf("A has been pressed. \n");
            globalKeys[SDLK_a] = true;
            aBallPaddleBrick.paddle.x -= PADDLE_SPEED;
        }

        if (keyboardStates[SDL_SCANCODE_D])
        {
            printf("D has been pressed. \n");
            globalKeys[SDLK_d] = true;
            aBallPaddleBrick.paddle.x += PADDLE_SPEED;
        }

        if (keyboardStates[SDL_SCANCODE_W])
        {
            printf("W has been pressed. \n");
            globalKeys[SDLK_w] = true;
            aBallPaddleBrick.ballSize++;
            aBallPaddleBrick.ball.w = aBallPaddleBrick.ball.h = aBallPaddleBrick.ballSize;
            aBallPaddleBrick.trail.w = aBallPaddleBrick.trail.h = aBallPaddleBrick.ballSize;
        }
        if (keyboardStates[SDL_SCANCODE_S])
        {
            printf("S has been pressed. \n");
            globalKeys[SDLK_s] = true;
            aBallPaddleBrick.ballSize--;
            aBallPaddleBrick.ball.w = aBallPaddleBrick.ball.h = aBallPaddleBrick.ballSize;
            aBallPaddleBrick.trail.w = aBallPaddleBrick.trail.h = aBallPaddleBrick.ballSize;
        }

        if (keyboardStates[SDL_SCANCODE_SPACE])
        {
            printf("Space has been pressed. \n");
            globalKeys[SDLK_SPACE] = true;
            aBallPaddleBrick.ResetLevel(true);
        }

        if (event.type == SDL_USEREVENT)
        {
            printf("code: %i \n", event.user.code);

            if (event.user.data1 == "Timer Countdown")
            {
                CountDownSeconds -= 1;
                printf("Countdown : %i \n", CountDownSeconds);
                if (CountDownSeconds <= 0)
                {
                    isRunning = false;
                }
            }
        }
    }
}

void GameWorld::Update()
{
    aBallPaddleBrick.UpdateBallAndPaddle();

    if (aTimer.getTicks() < DELTA_TIME)
    {
        SDL_Delay(DELTA_TIME - aTimer.getTicks());
    }
}

void GameWorld::Render()
{
    //function for rendering updates onto the screen, such as game states and updated character positions.

    SDL_SetRenderDrawColor(aBallPaddleBrick.aRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE); //set colour of renderer
    SDL_RenderClear(aBallPaddleBrick.aRenderer); //clears the window to colour of renderer

    spaceBG->render(aBallPaddleBrick.aRenderer);
    //SDL_RenderPresent(aBallPaddleBrick.aRenderer);
    //aBallPaddleBrick.RenderBallPaddleBrick();
    //SDL_RenderPresent(aBallPaddleBrick.aRenderer); //shows renderer to screen
    aBallPaddleBrick.RenderBallPaddleBrick();
    SDL_RenderPresent(aBallPaddleBrick.aRenderer);
    
}

void GameWorld::HandleOneSecondTimerInterval() 
{
    CountDownSeconds -= 1;
    if (CountDownSeconds < 0) 
    {
        CountDownSeconds = 0;
    }
}




void GameWorld::SplashScreen() 
{
    splashScreen->render(aBallPaddleBrick.aRenderer);
    SDL_RenderPresent(aBallPaddleBrick.aRenderer);
}

void GameWorld::CleanUp()
{
    SDL_DestroyWindow(window);
    printf("Window destroyed! \n");
    SDL_DestroyRenderer(aBallPaddleBrick.aRenderer);
    printf("Renderer destroyed! \n");
    aBallPaddleBrick.CleanUpAudio();
    SDL_Quit();
    printf("All processes eliminated! \n");
}
