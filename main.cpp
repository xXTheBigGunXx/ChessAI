#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

#include "BoardRenderer.h"
#include "Pieces.h"
#include <typeinfo>

int main(int argc, char** argv) {
	
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

	SDL_Window* window = SDL_CreateWindow("Chess game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BoardRenderer::WINDOW_WIDTH, BoardRenderer::WINDOW_WIDTH, SDL_WINDOW_SHOWN);
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

	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderClear(renderer);

	Board* board = new Board();

	BoardRenderer* boardRenderer = new BoardRenderer();
	boardRenderer->LoadTextures(renderer);
	boardRenderer->Render(renderer, *board);

	bool isRunning = true;
	SDL_Event event;
	int mouseX, mouseY;
	int matrixIndexX = -1, matrixIndexY = -1;

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		SDL_RenderClear(renderer);

		boardRenderer->Render(renderer, *board);
		
		auto piecePtr = GetPiece(board, matrixIndexX, matrixIndexY);

		SDL_GetMouseState(&mouseX, &mouseY);

		Uint32 buttons = SDL_GetMouseState(nullptr, nullptr);
		if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			matrixIndexX = mouseX / BoardRenderer::SQUARE_SIZE;
			matrixIndexY = mouseY / BoardRenderer::SQUARE_SIZE;
		}

		if (piecePtr != nullptr && matrixIndexX != -1 && matrixIndexY != -1)
		{
			piecePtr->PlaceLegalMove(board);
			for (auto& i : piecePtr->legalMoves)
			{
				if (matrixIndexX == i.first && matrixIndexY == i.second)
				{
					board->matrix[i.second][i.first] = board->matrix[piecePtr->y][piecePtr->x];
					board->matrix[piecePtr->y][piecePtr->x] = "  ";
					piecePtr->x = i.first;
					piecePtr->y = i.second;
					piecePtr->legalMoves.clear();
					matrixIndexX = -1;
					matrixIndexY = -1;
					board->whitesMove = !board->whitesMove;

					if ((piecePtr->y == 0 || piecePtr->y == 7) && typeid(*piecePtr) == typeid(Pawn)) {
						board->matrix[piecePtr->y][piecePtr->x] = std::string(1, 'Q') + piecePtr->color;
					}
					piecePtr = nullptr;

					break;
				}
			}
		}

		if (matrixIndexX != -1 && matrixIndexY != -1 && board->matrix[matrixIndexY][matrixIndexX][0] != ' ') {
			SDL_Rect square = {
				BoardRenderer::SQUARE_SIZE * matrixIndexX,
				BoardRenderer::SQUARE_SIZE * matrixIndexY,
				BoardRenderer::SQUARE_SIZE,
				BoardRenderer::SQUARE_SIZE
			};
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &square);
			SDL_SetRenderDrawColor(renderer, (int)BoardRenderer::SquareColor::YELLOW_SQUARE_RED, (int)BoardRenderer::SquareColor::YELLOW_SQUARE_GREEN, (int)BoardRenderer::SquareColor::YELLOW_SQUARE_BLUE, 255);
			SDL_RenderFillRect(renderer, &square);

			char color = board->whitesMove ? 'W' : 'B';
			if (piecePtr != nullptr && piecePtr->color == color)
			{
				piecePtr->PlaceLegalMove(board);
				boardRenderer->DrawDots(renderer, std::move(piecePtr));
			}
		}

		std::cout << std::boolalpha;
		King* temp = new King('W', 4 , 7);
		std::cout << CanKingMove(board, temp) << std::endl;

		boardRenderer->PlacePieces(renderer, *board);

		SDL_RenderPresent(renderer);
	}

	boardRenderer->Free();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}