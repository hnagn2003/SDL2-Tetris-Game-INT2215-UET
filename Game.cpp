#include "Game.h"
#include "Grid.h"
#include "Specifications.h"
#include <iostream>
#include <sstream>
void renderText(long long text, SDL_Renderer* renderer, TTF_Font* gFont, int xPos, int yPos, SDL_Color textColor){
    LTexture textTexture;
    std::stringstream ssText;
    ssText.str( "" );
    ssText << text;
    textTexture.loadFromRenderedText(ssText.str().c_str(), textColor, gFont, renderer);
	// std::cout << textTexture.getWidth() << ' ' << textTexture.getHeight() << std::endl;
    textTexture.render(renderer, xPos-textTexture.getWidth()/2, yPos-textTexture.getHeight()/2);
}
Game::Game()
{
	gameState = new Game_State;
	gFPS_Processor = new FPS_Processor;
	gameOver = new GameOverAnnouncement;
	tabs = -1;
}

Game::~Game()
{
    
}

void Game::init(const char* title, int xPos, int yPos, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
        isRunning = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( title, xPos, yPos, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! %s\n", IMG_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}

        isRunning = true;
	}

	if( !success )
	{
		printf( "Failed to initialize!\n" );
	}
	
	gFPS_Processor->initTimeCounting();
	// tabs_menu.setRenderer(renderer);
	tabs_menu.setUpMenu(renderer);
	
}
void Game::loadmedia()
{
	gFont1 = TTF_OpenFont( "font/Northstar3D-4D3x.otf", 24 );
	gameState->getGrid()->loadMedia(renderer);
}
void Game::handleEvents()
{
        SDL_Event event; 
		while(SDL_PollEvent(&event)){
			
			switch (event.type)
			{
				case SDL_QUIT:
					isRunning = false;
					break;
                case SDL_KEYDOWN:
					switch ( event.key.keysym.sym )
					{
					case SDLK_ESCAPE: //...
						isRunning = false;
						break;
					
					default:
						break;
					}
					// case ...
				default:
					switch (tabs)
					{
					case Menu:
						// std::cout <<"1 "<< tabs << std::endl;
						// std::cout <<"1 "<< tabs_menu.getDirect() << std::endl;
						tabs_menu.handleEvents(&event);
						tabs = tabs_menu.getDirect();
						// std::cout <<"2 "<< tabs_menu.getDirect() << std::endl;
						// std::cout <<"2 "<< tabs << std::endl;
						break;
					case InGame_SoloMode:
						//SDL_Delay...
						gameState->handleEvent(event);
						break;
					case GameOver:
						gameOver->handleEvents(&event);
						break;
					default:
						break;
					}
					break;
			}
		}
		
} 

void Game::update()
{
	//if currentTetrads tiep dat, chuyen trang thai khoi, cho khoi moi tiep dat
	gFPS_Processor->cappingFrame();

	if (tabs == Menu){
		// std::cout << tabs << std::endl;
		
		tabs_menu.render(renderer);
		// Tabs_Menu.handle
	}

	//Render text
	if (tabs == InGame_SoloMode){
		gameState->setPlaying(1);
		gameState->newTetradsFalling();
		// std::cout << "YPos2" << gameState->getNextTetrads()->getYPos() << std::endl;
		gameState->updateFallingTetrads();
		// std::cout << "YPos3" << gameState->getNextTetrads()->getYPos() << std::endl;
		if (gameState->gameOver()){
			tabs = GameOver; //...
			*gameState = Game_State();
			gameState->getGrid()->loadMedia(renderer);
			// khi game over ...
		}
	}
}

void Game::render()
{
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderClear(renderer);
	static LTexture backGround {backGroundPicture, renderer};
	backGround.render(renderer, 0, 0);
	
	switch (tabs)
	{
	case Menu:
		tabs_menu.render(renderer);
		break;
	case InGame_SoloMode:
		gameState->render(renderer);
		break;
	case GameOver:
		gameOver->render(renderer);
		break;
	default:
		break;
	}
	
	
	
	// gFPS_Processor->printFPS(renderer, gFont);
	
	// SDL_SetRenderDrawColor( renderer, 32, 64, 0, 0 );
    SDL_RenderPresent(renderer);
	
}

void Game::clean()
{
	TTF_CloseFont( gFont1 );
	gFont1 = NULL;

    SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}