#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

#include "Board.h"
#include "BoardRenderer.h"

int main(int argc, char** argv) {
	
	Board* board = new Board();

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)) {
		std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Chess game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)BoardRenderer::BoardDimmentions::WINDOWS_WIDTH, (int)BoardRenderer::BoardDimmentions::WINDOWS_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		std::cerr << "Rederer count not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	BoardRenderer* boardRenderer = new BoardRenderer();
	boardRenderer->LoadTextures(renderer);

	bool isRunning = true;
	SDL_Event event;

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderClear(renderer);

		boardRenderer->Render(renderer, *board);
		boardRenderer->PlacePeaces(renderer, *board);

		SDL_RenderPresent(renderer);
	}

	boardRenderer->Free();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}