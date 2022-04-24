#include "Game.h"
#include "Grid.h"
#include "Specifications.h"
#include <iostream>
#include <sstream>
Game::Game()
{
	gFPS_Processor = new FPS_Processor;
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
	
	gFont = TTF_OpenFont( rFont.c_str(), 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
	}
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
					tabs_menu.handleEvents(&event);
					// std::cout << tabs_menu.button[0].xPos << ' '<< tabs_menu.button[0].yPos << ' '<< tabs_menu.button[0].width << ' ' << std::endl;
					std::cout << tabs_menu.getDirect() << std::endl;
					gameState.handleEvent(event);
					break;
			}
			
		}
		
}

void Game::update()
{
	
	//if currentTetrads tiep dat, chuyen trang thai khoi, cho khoi moi tiep dat
	gFPS_Processor->cappingFrame();

	if (tabs == Menu){
		tabs_menu.render(renderer);
		// Tabs_Menu.handle
	}
	//Render text

	gameState.newTetradsFalling();
	// std::cout << "YPos2" << gameState.getNextTetrads()->getYPos() << std::endl;
	gameState.updateFallingTetrads();
	// std::cout << "YPos3" << gameState.getNextTetrads()->getYPos() << std::endl;
	if (gameState.gameOver()){
		// khi game over ...
	}
	
	
}

void Game::render()
{
	
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderClear(renderer);
	tabs_menu.render(renderer);
	// gameState.render(renderer);
	
	gFPS_Processor->printFPS(renderer, gFont);
	
	// SDL_SetRenderDrawColor( renderer, 32, 64, 0, 0 );
    SDL_RenderPresent(renderer);
	
}

void Game::clean()
{
	TTF_CloseFont( gFont );
	gFont = NULL;

    SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}