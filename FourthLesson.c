#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define HEIGHT	480
#define	WIDTH	640

void Init(SDL_Window **  gWindow, SDL_Surface ** gScreenSurface)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr,"Error iniciando SDL: %s\n",SDL_GetError());
		exit(1);
	}
	
	*gWindow = SDL_CreateWindow("FourthLesson",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								WIDTH,
								HEIGHT,
								0);
	
	*gScreenSurface = SDL_GetWindowSurface(*gWindow);

}

void Close(SDL_Window * gWindow, SDL_Surface * gScretchedSurface)
{
	SDL_FreeSurface(gScretchedSurface);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

SDL_Surface * loadOptimized(char * path, SDL_Surface * gScreenSurface)
{
	SDL_Surface * gImageOptimized;
	SDL_Surface * gImage;

	//Load image
	if(NULL == (gImage = SDL_LoadBMP(path)))
	{
		fprintf(stderr,"Error loading image: %s\n",SDL_GetError());
		exit(1);
	}
	
	/*
	//optimize the image
	gImageOptimized = SDL_ConvertSurface(gImage, gScreenSurface->format, 0);
	
	if(NULL == gImageOptimized)
	{
		fprintf(stderr,"Error converting surface: %s\n",SDL_GetError());
		exit(1);
	}*/
	
	
	//Free the original image
	//SDL_FreeSurface(gImage);
	
	return gImage;
}


int main(int argc, char ** argv)
{
	SDL_Window * gWindow;
	SDL_Surface * gScreenSurface;
	SDL_Event e;
	SDL_Surface * gStretchedSurface;
	SDL_Rect * strechtRect = malloc(sizeof(SDL_Rect));
	int quit = 0;
	
	// Initialize SDL
	Init(&gWindow, &gScreenSurface);
	
	gStretchedSurface = loadOptimized("parsee.bmp",gScreenSurface);
	
	//Initialize SDL_Rect structure
	strechtRect->x = 0;
	strechtRect->y = 0;
	strechtRect->w = WIDTH;
	strechtRect->h = HEIGHT;
	
	//Blit to the screen stretched
	SDL_BlitScaled(gStretchedSurface, //src 
					NULL, // rectangle of src
					gScreenSurface, // dest
					strechtRect); // rectangle of dest
					
	SDL_UpdateWindowSurface(gWindow);
					
	//Wait for 5 seconds		
	SDL_Delay(5000);
	
	Close(gWindow,gStretchedSurface);
	
	return 0;
}
