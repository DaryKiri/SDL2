#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define	WIDTH	640
#define HEIGHT	480

SDL_Surface * loadImageOptimized(char * path, SDL_Surface * gScreenSurface)
{
	SDL_Surface * gOptimizedSurface;
	SDL_Surface * gLoadedSurface;
	
	if(NULL == (gLoadedSurface = IMG_Load(path)))
	{
		fprintf(stderr,"Error loading image: %s\n",IMG_GetError());
		exit(1);
	}
	
	//Convert surface to screen format
	if(NULL == (gOptimizedSurface = SDL_ConvertSurface(gLoadedSurface, gScreenSurface->format, 0)))
	{
		fprintf(stderr,"Error converting suface: %s\n",SDL_GetError());
		exit(1);
	} 
	
	SDL_FreeSurface(gLoadedSurface);
	
	return gOptimizedSurface;
}

//	Load PNG with SDL_Image

int main(int argc, char ** argv)
{
	SDL_Window * gWindow;
	SDL_Surface * gScreenSurface;
	SDL_Surface * gOptimizedSurface;
	SDL_Rect stretchedConf;
	int imgFlags;
	
	//	Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr,"Error initializing SDL: %s\n",SDL_GetError());
		exit(1);
	}
	
	gWindow = SDL_CreateWindow("Fifth Lesson",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								WIDTH,
								HEIGHT,
								0);
								
	if(NULL == gWindow)
	{
		fprintf(stderr,"Error creating window: %s\n",SDL_GetError());
		exit(1);
	}
	
	if(NULL == (gScreenSurface = SDL_GetWindowSurface(gWindow)))
	{
		fprintf(stderr,"Error obtaining window surface: %s\n",SDL_GetError());
		exit(1);
	}
	
	//Initialize PNG loading
	imgFlags = IMG_INIT_PNG; //Flags to initialize SDL_image
	if(!(IMG_Init(imgFlags) & imgFlags)) //IMG_Init returns the flags that loaded succesfully
	{
		fprintf(stderr,"SDL_Image could not initialize! SDL_Image Error: %s\n",IMG_GetError());
		exit(1);
	}
	
	//Load the image
	gOptimizedSurface = loadImageOptimized("ram.png",gScreenSurface);
	
	//Initialize stretchedConf
	stretchedConf.x = 0;
	stretchedConf.y = 0;
	stretchedConf.w = WIDTH;
	stretchedConf.h = HEIGHT;
	
	//Blit image to screen and update
	//SDL_BlitSurface(gOptimizedSurface, NULL, gScreenSurface, NULL); //Normal Blit
	SDL_BlitScaled(gOptimizedSurface, NULL, gScreenSurface, &stretchedConf); // Scaled Blit
	SDL_UpdateWindowSurface(gWindow);
	
	//Wait 5 seconds and quit
	SDL_Delay(5000);
	SDL_FreeSurface(gOptimizedSurface);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
	
	return 0;
}
