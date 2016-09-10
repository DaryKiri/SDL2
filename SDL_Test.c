#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define DISPLAY_WIDHT	640
#define DISPLAY_HEIGHT	320
#define WHRECT			10

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	
} RGBAColour;

/*
enum Color{
	WHITE,
	BLACK, 
	TOTAL_COLORS
};
*/

//	Initialize the display 
void InitDisplay(SDL_Window ** eWindow, SDL_Renderer ** eRenderer)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr,"Error on initializing display: %s\n",SDL_GetError());
		exit(1); 
	}
	
	*eWindow = SDL_CreateWindow("SDL Test",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								DISPLAY_WIDHT,
								DISPLAY_HEIGHT,
								0);
	
	if( NULL == *eWindow)
	{
		fprintf(stderr,"Error creating main window: %s\n",SDL_GetError());
		exit(1);
	}
	
	// Create renderer
	if(NULL == (*eRenderer = SDL_CreateRenderer(*eWindow, -1, SDL_RENDERER_ACCELERATED)))
	{
		fprintf(stderr,"Error creating renderer: %s\n",SDL_GetError());
		exit(1);
	}
	
	// Initialize renderer color
	if(SDL_SetRenderDrawColor(*eRenderer, 0x00, 0x00, 0x00, 0x00) < 0) //Black colour with alpha transparency
	{
		fprintf(stderr,"Error setting renderer draw color: %s\n",SDL_GetError());
		exit(1);
	}
	
	//Initialize SDL_image library
	int imgflags = IMG_INIT_PNG | IMG_INIT_JPG;
	
	if( !(IMG_Init(imgflags) & imgflags))
	{
		fprintf(stderr, "Error loading SDL_image library: %s\n",IMG_GetError());
		exit(1);
	}
	
	// Clear the screen
	SDL_RenderClear(*eRenderer);
	
	//Update screen
	SDL_RenderPresent(*eRenderer);
	
	// Seed for random
	srand(time(NULL));
	
}

void CloseDisplay(SDL_Window * eWindow, SDL_Renderer * eRenderer)
{
	SDL_DestroyRenderer(eRenderer);
	SDL_DestroyWindow(eWindow);
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char ** argv)
{
	// Variables
	SDL_Window * eWindow;
	SDL_Renderer * eRenderer;
	SDL_Event e;
	// Array of rgba colors
	RGBAColour colors[2];
	SDL_Rect rectangle;
	int quit = 0;
	int x = 0;
	int y = 0;
	// Colours index
	int i = 0;
	
	InitDisplay(&eWindow, &eRenderer);
	
	// Initialize colours
	RGBAColour white;
	RGBAColour black;
	RGBAColour red;
	
	black.r = 0x00;
	black.g = 0x00;
	black.b = 0x00;
	black.a = 0x00;
	
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	white.a = 0x00;
	
	colors[0] = white;
	colors[1] = black;
	
	while(!quit)
	{
		//Polling events
		while(SDL_PollEvent(&e) > 0)
		{
			if(e.type == SDL_QUIT)
				quit = 1;
		}
		
		if(y < DISPLAY_HEIGHT/10)
		{
			if(x < DISPLAY_WIDHT/10)
			{
				SDL_SetRenderDrawColor(eRenderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
				rectangle.x = x *10;
				rectangle.y = y * 10;
				rectangle.w = WHRECT;
				rectangle.h = WHRECT;
				SDL_RenderFillRect(eRenderer, &rectangle);
				++x;
			}
			else
			{
				x = 0;
				++y;
			}
			
			if(i == 1)
			{
				i = 0;
			}
			else
			{
				i = 1;
			}
		}
		
		SDL_RenderPresent(eRenderer);
		// Wait for 3 seconds
		SDL_Delay(100); 
	}
	
	SDL_RenderClear(eRenderer);
	
	CloseDisplay(eWindow, eRenderer);
	
	return 0;
}


