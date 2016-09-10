#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define HEIGHT	480
#define	WIDTH	640

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL,
};

SDL_Surface * loadSurface(char * path)
{
	SDL_Surface * gSurface;
	if(NULL == (gSurface = SDL_LoadBMP(path)))
	{
		fprintf(stderr,"Error loading bmp image: %s SDL_Error: %s\n",path,SDL_GetError());
		exit(1);
	}
	
	return gSurface;
}

int main(int argc, char ** argv)
{
	//Variables 
	SDL_Window * gWindow;
	SDL_Surface * gScreenSurface;
	SDL_Surface * gImageCurrent;
	SDL_Surface * gKeyPressedSurfaces[KEY_PRESS_SURFACE_TOTAL];
	//Event handler
	SDL_Event  e;
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
	
	//Load default surface
	gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("thirdlesson/ram.bmp");
	
	//Load rest of surfaces
	gKeyPressedSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("thirdlesson/ram1.bmp");
	gKeyPressedSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("thirdlesson/ram2.bmp");
	gKeyPressedSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("thirdlesson/ram3.bmp");
	gKeyPressedSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("thirdlesson/ram4.bmp");
	
	//Set current surface
	gImageCurrent = gKeyPressedSurfaces[KEY_PRESS_SURFACE_DEFAULT];

	//Main Loop
	while(!quit)
	{
		// Handle pending events
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = 1;
			}
			else
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						gImageCurrent = gKeyPressedSurfaces[ KEY_PRESS_SURFACE_UP];
						break;
					case SDLK_DOWN:
						gImageCurrent = gKeyPressedSurfaces[ KEY_PRESS_SURFACE_DOWN];
						break;
					case SDLK_LEFT:
						gImageCurrent = gKeyPressedSurfaces[ KEY_PRESS_SURFACE_LEFT];
						break;
					case SDLK_RIGHT:
						gImageCurrent = gKeyPressedSurfaces[ KEY_PRESS_SURFACE_RIGHT];
						break;
					default:
						printf("Key not implemented\n");
						break;
				}
			}
		}
		
		//Blit the image
		SDL_BlitSurface(gImageCurrent,NULL,gScreenSurface,NULL);
		SDL_UpdateWindowSurface(gWindow);
	}
	
	// Free surfaces
	//SDL_FreeSurface(gImageCurrent);
	int i = 0;
	for (;i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(gKeyPressedSurfaces[i]);
	}
	
	//Destroy window and quit SDL
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
	
	return 0;
}
