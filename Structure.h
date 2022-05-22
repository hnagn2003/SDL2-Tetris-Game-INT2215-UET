#ifndef Structure_h
#define Structure_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <algorithm>  

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

#endif