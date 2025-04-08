#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Board.h"

class BoardRenderer {
public:
enum class PieceType {
	EMPTY = ' ',
	PAWN = 'P',
	KNIGHT = 'N',
	BISHOP = 'B',
	ROOK = 'R',
	QUEEN = 'Q',
	KING = 'K',
};
enum class BoardDimmentions {
	ROWS = 8,
	COLUMNS = 8,
	SQUARE_SIZE = 95,
	WINDOWS_WIDTH = SQUARE_SIZE * COLUMNS,
	WINDOWS_HEIGHT = SQUARE_SIZE * ROWS,
};
enum class SquareColor {
	DARK_SQUARE_RED = 181,
	DARK_SQUARE_GREEN = 136,
	DARK_SQUARE_BLUE = 99,
	LIGHT_SQUARE_RED = 240,
	LIGHT_SQUARE_GREEN = 217,
	LIGHT_SQUARE_BLUE = 181,
	YELLOW_SQUARE_RED = 220,
	YELLOW_SQUARE_GREEN = 208,
	YELLOW_SQUARE_BLUE = 75,
};
struct Color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

SDL_Texture* bB;
SDL_Texture* bK;
SDL_Texture* bN;
SDL_Texture* bP;
SDL_Texture* bQ;
SDL_Texture* bR;
SDL_Texture* wB;
SDL_Texture* wK;
SDL_Texture* wN;
SDL_Texture* wP;
SDL_Texture* wQ;
SDL_Texture* wR;

static const char* stringConstants[];

void LoadTextures(SDL_Renderer* renderer);
void Render(SDL_Renderer* renderer, const Board& board);
void Free();
void PlacePeaces(SDL_Renderer* renderer, const Board& board);
};