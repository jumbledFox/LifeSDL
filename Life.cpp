#include <iostream>
#include<windows.h>

#include "include/SDL.h"

#include "CellMap.h"

// SDL window and surface for pixel manipulation
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

// width and height of cell in pixels
unsigned int cellSize = 5;

unsigned int cellMapWidth = 170;
unsigned int cellMapHeight = 170;

unsigned int screenWidth = cellMapWidth * cellSize;
unsigned int screenHeight = cellMapHeight * cellSize;

Life::CellMap cellMap(cellMapWidth, cellMapHeight);

void DrawCell(unsigned int i, int color[3]) {
	unsigned int x, y;
	x = i % cellMapHeight;
	y = floor(i / cellMapWidth);
	Uint8* pixel_ptr = (Uint8*)surface->pixels + (y * cellSize * screenWidth + x * cellSize) * 4;

	for (int i = 0; i < cellSize; i++) {
		for (int j = 0; j < cellSize; j++) {
			*(pixel_ptr + j * 4) = color[2];
			*(pixel_ptr + j * 4 + 1) = color[1];
			*(pixel_ptr + j * 4 + 2) = color[0];
		}
		pixel_ptr += screenWidth * 4;
	}

	delete[] color;
}

int main(int argc, char* argv[]) {

    // Boilerplate //
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Life - jumbledFox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);

	
	// SDL Event handler
	SDL_Event e;

	// Rendering Loop
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT) running = false;

		cellMap.Tick();

		for(int i = 0; i < cellMap.length; i++) {
			DrawCell(i, (cellMap.cells[i] & 0x01) ? new int[]{255, 255, 255} : new int[] {0, 0, 0});
		}

		SDL_UpdateWindowSurface(window);
		
		//SDL_Delay(20);
	}

	//Clean up SDL
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}