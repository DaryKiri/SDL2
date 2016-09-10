#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH	640
#define HEIGHT	480

int main(int argc, char ** argv)
{
	//Variables
	SDL_Window * gWindow;
	SDL_Surface * gScreenSurface;
	SDL_Surface * gImage;
	// Event Handler
	SDL_Event e;
	// For main loop
	int quit = 0;
	
	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr,"Error couldnt initialize SDL, %s\n",SDL_GetError());
		exit(1);
	}
	
	//Create window
	gWindow = SDL_CreateWindow(
		"Test SDL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		0);
	
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	
	gImage = SDL_LoadBMP("thirdlesson/ram.bmp");
	SDL_BlitSurface(gImage,NULL,gScreenSurface,NULL);
	SDL_FreeSurface(gImage);
	
	SDL_UpdateWindowSurface(gWindow);
	
	while(!quit)
	{
		// Handle pending events
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = 1;
			}
		}
	}
	
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
	
}
