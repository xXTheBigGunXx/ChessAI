#include "BoardRenderer.h"
#include <iostream>

const char* BoardRenderer::stringConstants[] = {
	"Pieces\\bB.png",
	"Pieces\\bK.png",
	"Pieces\\bN.png",
	"Pieces\\bP.png",
	"Pieces\\bQ.png",
	"Pieces\\bR.png",
	"Pieces\\wB.png",
	"Pieces\\wK.png",
	"Pieces\\wN.png",
	"Pieces\\wP.png",
	"Pieces\\wQ.png",
	"Pieces\\wR.png",
};

void BoardRenderer::Render(SDL_Renderer* renderer, const Board& board)
{
	for (size_t i = 0; i < BoardRenderer::ROWS; i++) {
		for (size_t j = 0; j < BoardRenderer::COLUMNS; j++) {
			SDL_Rect square = {
				BoardRenderer::SQUARE_SIZE * j,
				BoardRenderer::SQUARE_SIZE * i,
				BoardRenderer::SQUARE_SIZE,
				BoardRenderer::SQUARE_SIZE
			};

			Color squaresColor = {
				(Uint8)SquareColor::DARK_SQUARE_RED, (Uint8)SquareColor::DARK_SQUARE_GREEN, (Uint8)SquareColor::DARK_SQUARE_BLUE, 255
			};
		
			if ((i + j) % 2 == 0) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				squaresColor = {
					(Uint8)SquareColor::LIGHT_SQUARE_RED, (Uint8)SquareColor::LIGHT_SQUARE_GREEN, (Uint8)SquareColor::LIGHT_SQUARE_BLUE, 255
				};
			}
			SDL_SetRenderDrawColor(renderer, squaresColor.r, squaresColor.g, squaresColor.b, squaresColor.a);
			SDL_RenderFillRect(renderer, &square);
		}
	}
}

void BoardRenderer::LoadTextures(SDL_Renderer* renderer)
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	
	bB = IMG_LoadTexture(renderer, stringConstants[0]);
	bK = IMG_LoadTexture(renderer, stringConstants[1]);
	bN = IMG_LoadTexture(renderer, stringConstants[2]);
	bP = IMG_LoadTexture(renderer, stringConstants[3]);
	bQ = IMG_LoadTexture(renderer, stringConstants[4]);
	bR = IMG_LoadTexture(renderer, stringConstants[5]);
	wB = IMG_LoadTexture(renderer, stringConstants[6]);
	wK = IMG_LoadTexture(renderer, stringConstants[7]);
	wN = IMG_LoadTexture(renderer, stringConstants[8]);
	wP = IMG_LoadTexture(renderer, stringConstants[9]);
	wQ = IMG_LoadTexture(renderer, stringConstants[10]);
	wR = IMG_LoadTexture(renderer, stringConstants[11]);
	if (!bB || !bK || !bN || !bP || !bQ || !bR || !wB || !wK || !wN || !wP || !wQ || !wR) {
		std::cerr << "Failed to load textures: " << SDL_GetError() << std::endl;
	}

	SDL_SetTextureBlendMode(bB, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(bK, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(bN, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(bP, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(bQ, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(bR, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(wB, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(wK, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(wN, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(wP, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(wQ, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(wR, SDL_BLENDMODE_BLEND);
		
}

void BoardRenderer::Free()
{
	SDL_DestroyTexture(bB);
	SDL_DestroyTexture(bK);
	SDL_DestroyTexture(bN);
	SDL_DestroyTexture(bP);
	SDL_DestroyTexture(bQ);
	SDL_DestroyTexture(bR);
	SDL_DestroyTexture(wB);
	SDL_DestroyTexture(wK);
	SDL_DestroyTexture(wN);
	SDL_DestroyTexture(wP);
	SDL_DestroyTexture(wQ);
	SDL_DestroyTexture(wR);
}

void BoardRenderer::PlacePieces(SDL_Renderer* renderer, const Board& board)
{
	for (size_t i = 0; i < BoardRenderer::ROWS; i++) {
		for (size_t j = 0; j < BoardRenderer::COLUMNS; j++) {

			SDL_Rect pieceRect = {
				BoardRenderer::SQUARE_SIZE * j,
				BoardRenderer::SQUARE_SIZE * i,
				BoardRenderer::SQUARE_SIZE,
				BoardRenderer::SQUARE_SIZE
			};

			SDL_Texture* texture = nullptr;

			switch (board.matrix[i][j][1]) {
			case 'B':
				switch (board.matrix[i][j][0]) {
				case 'B': texture = bB; break;
				case 'K': texture = bK; break;
				case 'N': texture = bN; break;
				case 'P': texture = bP; break;
				case 'Q': texture = bQ; break;
				case 'R': texture = bR; break;
				}
				break;
			case 'W':
				switch (board.matrix[i][j][0]) {
				case 'B': texture = wB; break;
				case 'K': texture = wK; break;
				case 'N': texture = wN; break;
				case 'P': texture = wP; break;
				case 'Q': texture = wQ; break;
				case 'R': texture = wR; break;
				}
				break;
			default:
				break;
			}
			if (texture != nullptr) {
				SDL_RenderCopy(renderer, texture, nullptr, &pieceRect);
			}
		}
	}
}

void BoardRenderer::DrawDots(SDL_Renderer* renderer, std::unique_ptr<Piece> piecePtr)
{
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	for (const auto& i : piecePtr->legalMoves) {
		SDL_Rect dot = {
			BoardRenderer::SQUARE_SIZE * i.first,
			BoardRenderer::SQUARE_SIZE * i.second,
			BoardRenderer::SQUARE_SIZE,
			BoardRenderer::SQUARE_SIZE
		};
		SDL_SetRenderDrawColor(renderer, 158, 116, 84, 255);
		if((i.first + i.second) % 2 == 0)
			SDL_SetRenderDrawColor(renderer, 204, 184, 151, 255);

		DrawCircle(renderer, dot.x + dot.w/2, dot.y + dot.h/2, SQUARE_SIZE/2);
	}
}

void BoardRenderer::DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
	for (int w = 0; w < radius * 2; w++) {
		for (int h = 0; h < radius * 2; h++) {
			int dx = radius - w;
			int dy = radius - h;
			if ((dx * dx + dy * dy) <= (radius * radius)) {
				SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
			}
		}
	}
}