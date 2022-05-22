#ifndef Structure_h
#define Structure_h

// #include <stdio.h>
// #include <SDL_image.h>
// #include <SDL_ttf.h>
// #include <iostream>
#include <algorithm>   
#include "Data.h"
class LTexture
{
	public:
		LTexture();

		LTexture(std::string path, SDL_Renderer* gRenderer);

		~LTexture();
		LTexture(std::string textureText, SDL_Color textColor, TTF_Font* gFont1, SDL_Renderer* gRenderer );
		bool loadFromFile( std::string path, SDL_Renderer* gRenderer );
		
		// #if defined(SDL_TTF_MAJOR_VERSION)
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* gFont1, SDL_Renderer* gRenderer );
		// #endif

		void free();

		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void setBlendMode( SDL_BlendMode blending );

		void setAlpha( Uint8 alpha );
		
		void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		int getWidth();
		int getHeight();

	public:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};

class LTimer
{
    public:
		LTimer();

		void start();
		void stop();
		void pause();
		void unpause();

		Uint32 getTicks();

		bool isStarted();
		bool isPaused();

    private:
		Uint32 mStartTicks;

		Uint32 mPausedTicks;

		bool mPaused;
		bool mStarted;
};

// xử lý fps: print, capping
class FPS_Processor
{
    public:
        long long countedFrames;
        LTexture* gFPSTextTexture;
        LTimer* fpsTimer;
        LTimer* capTimer;
    public:
        FPS_Processor()
        {
            countedFrames = 0;
            gFPSTextTexture = new LTexture;
            fpsTimer = new LTimer;
            capTimer = new LTimer;
        }
        ~FPS_Processor()
        {
            gFPSTextTexture->free();
            delete fpsTimer;
            delete capTimer;
        }
        void initTimeCounting()
        {
            fpsTimer->start();
        }
        void cappingFrame()
        {
            capTimer->start();
            ++countedFrames;
            int frameTicks = capTimer->getTicks();
            if( frameTicks < SCREEN_TICK_PER_FRAME )
            {
                //Wait remaining time
                SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
            }
        }
        void printFPS(SDL_Renderer* renderer, TTF_Font* gFont){
            int avgFPS = countedFrames / ( fpsTimer->getTicks() / 1000.f );
            std::stringstream timeText;
            timeText.str( "" );
            timeText << "FPS: " << avgFPS; 
            SDL_Color textColor = { 0, 0, 0, 255 };
            if( !gFPSTextTexture->loadFromRenderedText( timeText.str().c_str(), textColor, gFont, renderer ))
            {
                printf( "Unable to render FPS texture!\n" );
	        }
            gFPSTextTexture->render( renderer,( SCREEN_WIDTH - gFPSTextTexture->getWidth() ), 0 );
        }
};

class LButton
{
    public:
		LTexture* keyUp;
        LTexture* keyDown;
        bool inside;
        bool motionMouse;
        bool pressed;
        int xCen, yCen, width, height;
        int xPos, yPos;
	public:
		LButton(){
            keyDown = new LTexture;
            keyUp = new LTexture;
            inside = 0;
            pressed = 0;
            xPos = 0; yPos = 0; xCen = 0; yCen = 0;
        }
        LButton(LTexture* _keyUp, LTexture* _keyDown)
        {
            motionMouse = 0;
            keyUp = _keyUp;
            keyDown = _keyDown;
            width = keyUp->getWidth();
            height = keyUp->getHeight();
            xPos = 0; yPos = 0; xCen = 0; yCen = 0;
        }
        ~LButton(){
            keyUp->free();
            keyDown->free();
            delete keyUp;
            delete keyDown;
        }
        bool getPressed()
        {
            return pressed;
        }
        bool getInside()
        {
            return inside;
        }
        int getXCen(){return xCen;}
        int getYCen(){return yCen;}
        int getXPos(){return xPos;}
        int getYPos(){return yPos;}
        int getWidth(){return width;}
        int getHeight(){return height;}
        void setSize(int w, int h){width = w; height = h;}
        void setPressed(bool _pressed){pressed = _pressed;}
        void setTexture(LTexture* _keyUp, LTexture* _keyDown)
        {
            keyUp = _keyUp;
            keyDown = _keyDown;
            width = keyUp->getWidth();
            height = keyUp->getHeight();
        }
        void setPosition( int x, int y )
        {
            xPos = x; yPos = y;
        }
		void setCenterPosition( int x, int y )
        {
            xCen = x; yCen = y;
        }
        void handleEvents(SDL_Event* e, bool circleButton = 0)
        {
            if (xPos == 0 && yPos == 0)
            {
                xPos = xCen - width/2, yPos = yCen - height/2;
            }
            motionMouse = 0;
            pressed = 0;
        	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
            {
                int x, y;
		        SDL_GetMouseState( &x, &y );
                bool inside = true;
                if (!circleButton)
                {
                    inside = isInside(x, y);
                }
                else
                {
                    if ( (x-xCen)*(x-xCen) + (y-yCen)*(y-yCen) <= width*width/4 )
                    {
                        inside = true;
                    }else
                    {
                        inside = false;
                    }
                }
                if (inside)
                {
                    switch (e->type)
                    {
                        case SDL_MOUSEMOTION:
                            motionMouse = 1;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            playSoundEffects(se_mouseClick);
                            motionMouse = 1;
                            pressed = 1;
                            break;
                        case SDL_MOUSEBUTTONUP:
                            pressed = 0;
                            break;
                        default:
                            break;
                    }
                }
            }
    
        }
		void render(SDL_Renderer* renderer, int x = 0, int y = 0)
        {
            if (x==0&&y==0)
            {
                x=xPos; y = yPos;
            }
            if (motionMouse)
            {
                keyDown->render(renderer, x, y);
            }
            else
            {
                keyUp->render(renderer, x, y);
            }
        }
        bool isInside(int x, int y){
        if (x<xPos)
        {
            return false;
        }
        else if (x>xPos+width)
        {
            return false;
        }
        else if (y<yPos)
        {
            return false;
        }
        else if (y>yPos + height)
        {
            return false;
        }
        return true;
        }
};
extern LButton* backButton;
extern LButton* replayButton;
#endif