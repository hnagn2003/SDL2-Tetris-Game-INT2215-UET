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
	battleProcessor = new BallteProcessor;
	gFPS_Processor = new FPS_Processor;
	gameOver = new GameOverAnnouncement;
	helpsAndCredit = new HelpsAndCredit;
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
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
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
				SDL_SetHint (SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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
	
}
void Game::loadmedia()
{
	tabs_menu.setUpMenu(renderer);
	gameOver->setUp(renderer);
	helpsAndCredit->setUp(renderer);
	gFont1 = TTF_OpenFont( "font/Northstar3D-4D3x.otf", 24 );

	LTexture* backButtonTex = new LTexture;
	LTexture* backButtonTex_ = new LTexture;
	backButtonTex->loadFromFile(back_button, renderer);
    backButtonTex_->loadFromFile(back_button_, renderer);
	backButton.setTexture(*backButtonTex, *backButtonTex_);

	playingSoundtrack = Mix_LoadMUS( "assets/Musics/playing.mp3" );
	themeSoundtrack = Mix_LoadMUS( "assets/Musics/backgroundMusic.mp3" );
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
						tabs = gameState->getDirect();
						break;
					case InGame_BattleMode:
						battleProcessor->handleEvent(event);
						tabs = battleProcessor->getDirect();
						break;
					case GameOver:
						gameOver->handleEvents(&event);
						tabs = gameOver->getDirect();
						break;
					case Helps:
						helpsAndCredit->handleEvent(&event);
						tabs = helpsAndCredit->getDirect();
						break;
					default:
						break;
					}
					break;
			}
		}
} 
void Game::playMusic()
{
	switch (tabs)
	{
	case InGame_SoloMode:
		break;
	case InGame_BattleMode:
		break;
	default:
		if( Mix_PlayingMusic() == 0 ){
			Mix_PlayMusic( themeSoundtrack, -1 );
		}
		break;
	}
}
void Game::update()
{
	//if currentTetrads tiep dat, chuyen trang thai khoi, cho khoi moi tiep dat

	gFPS_Processor->cappingFrame();
	switch (tabs){
		case Menu:
			break;
		case InGame_SoloMode:
			backButton.setCenterPosition(100, 100);
			gameState->update();
			if (gameState->gameOver()){
				Mix_HaltMusic();
				tabs = GameOver; //...
				*gameState = Game_State();

			}
			break;
		case InGame_BattleMode:
			battleProcessor->update();
			backButton.setCenterPosition(100, 100);
			if (battleProcessor->gameOver()){
				tabs = BattleEnded;
				*battleProcessor = BallteProcessor();
			}
			
			// if (gameState->gameOver()){
			// 	tabs = GameOver; //...
			// 	*gameState = Game_State();

			// }
			break;
		case GameOver:
			backButton.setCenterPosition(1289, 569);
			break;
		case Helps:
			backButton.setCenterPosition(100, 100);
			break;
		default:
			break;
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
	case InGame_BattleMode:
		battleProcessor->render(renderer);
		break;
	case GameOver:
		gameOver->render(renderer);
		break;
	case Helps:
		helpsAndCredit->render(renderer);
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