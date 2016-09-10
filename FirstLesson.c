#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH	640
#define HEIGHT	480

int main(int argc, char ** argv)
{
	//Window we are rendering
	SDL_Window * gWindow;
	//Surface contained by the window
	SDL_Surface * gScreenSurface;
	// Image to load and show to the screen
	SDL_Surface * gHelloWorld;
	
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
		
	if(NULL == gWindow)
	{
		fprintf(stderr,"Error, couldnt create window: %s\n",SDL_GetError());
		exit(1);
	}
	
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	
	//Load the media
	if(NULL == (gHelloWorld = SDL_LoadBMP("ram.bmp")))
	{
		fprintf(stderr,"Error, on loading image: %s\n",SDL_GetError());
		exit(1);
	}
	
	//Paste image to window surface
	if(0 != (SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL)))
	{
		fprintf(stderr,"Error, on bliting to surface: %s\n",SDL_GetError());
		exit(1);		
	}
	
	//Update the window
	SDL_UpdateWindowSurface(gWindow);
	
	//Wait five seconds
	SDL_Delay(5000);
	
	//Close
	SDL_FreeSurface(gHelloWorld); 
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
	
	return 0;
}
