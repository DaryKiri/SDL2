#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH	640
#define HEIGHT	480

void InitDisplay(SDL_Window ** gWindow, SDL_Renderer ** gRenderer)
{
	int imgFlags = IMG_INIT_PNG;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Error initializing SDL: %s\n",SDL_GetError());
		exit(1);
	}
	
	//Create window
	*gWindow = SDL_CreateWindow("Six Lesson",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								WIDTH,
								HEIGHT,
								0);
	
	if(*gWindow == NULL)
	{
		fprintf(stderr,"Error creating the window: %s\n",SDL_GetError());
		exit(1);
	}
					
	//Create the renderer
	if(NULL == (*gRenderer = SDL_CreateRenderer(*gWindow, -1, SDL_RENDERER_ACCELERATED )))
	{
		fprintf(stderr,"Error creating renderer: %s\n",SDL_GetError());
		exit(1);
	}
	
	// Initialize renderer color
	if(SDL_SetRenderDrawColor(*gRenderer, 0xFF, 0xFF, 0xFF, 0xFF) < 0) //White colour without alpha transparency
	{
		fprintf(stderr,"Error setting renderer draw color: %s\n",SDL_GetError());
		exit(1);
	}
	
	// Initialize PNG Image library
	if(!(imgFlags & IMG_Init(imgFlags)))
	{
		fprintf(stderr,"Error initializing SDL_image library: %s\n",IMG_GetError());
		exit(1);
	}
	
}

SDL_Texture * LoadTexture(char * path, SDL_Renderer * gRenderer)
{
	SDL_Texture * newTexture;
	SDL_Surface * gLoadedImg;
	
	//Load image
	if(NULL == (gLoadedImg = IMG_Load(path)))
	{
		fprintf(stderr,"Error loading image on path: %s, IMG error: %s\n",path,IMG_GetError());
		exit(1);
	}
	
	// Creaate new texture from surface
	newTexture = SDL_CreateTextureFromSurface(gRenderer, gLoadedImg);
	newTexture = IMG_LoadTexture(gRenderer,path);
	printf("%s\n",IMG_GetError());
	if(NULL == newTexture)
	{
		printf("Esta a null\n");
	}
	/*
	if(NULL == (newTexture = SDL_CreateTextureFromSurface(gRenderer, gLoadedImg)))
	{
		fprintf(stderr,"Error creating texture from surface: %s\n",SDL_GetError());
		exit(1);
	}
	*/
	
	// Free the surface created for loading the image
	SDL_FreeSurface(gLoadedImg);
	
	// Return the new created texture
	return newTexture;
}


int main(int argc, char ** arv)
{
	SDL_Window * gWindow;
	// Window renderer
	SDL_Renderer * gRenderer;
	// Current display texture
	SDL_Texture * gTexture;
	//For polling events
	SDL_Event e;
	int quit = 0;
	
	InitDisplay(&gWindow, &gRenderer);
	
	SDL_UpdateWindowSurface(gWindow);
	
	gTexture = LoadTexture("ram.png",gRenderer);
	
	while(!quit)
	{
		while(SDL_PollEvent(&e) > 0)
		{
			if(e.type == SDL_QUIT)
				quit = 1;
		}
		
		//Clear Screen
		SDL_RenderClear(gRenderer);
		
		//Render texture to screen
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
		
		//Update screen
		SDL_RenderPresent(gRenderer);
	}
	
	// Close section
	SDL_DestroyTexture(gTexture);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	
	IMG_Quit();
	SDL_Quit();
	
	return 0;
} 
