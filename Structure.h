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
        FPS_Processor();
        ~FPS_Processor();
        void initTimeCounting();
        void cappingFrame();
        void printFPS(SDL_Renderer* renderer, TTF_Font* gFont);
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
		LButton();
        LButton(LTexture* _keyUp, LTexture* _keyDown);
        ~LButton();
        bool getPressed();
        bool getInside();
        int getXCen();
        int getYCen();
        int getXPos();
        int getYPos();
        int getWidth();
        int getHeight();
        void setSize(int w, int h);
        void setPressed(bool _pressed);
        void setTexture(LTexture* _keyUp, LTexture* _keyDown);
        void setPosition( int x, int y );
		void setCenterPosition( int x, int y );
        void handleEvents(SDL_Event* e, bool circleButton = 0);
		void render(SDL_Renderer* renderer, int x = 0, int y = 0);
        bool isInside(int x, int y);
};
extern LButton* backButton;
extern LButton* replayButton;
#endif