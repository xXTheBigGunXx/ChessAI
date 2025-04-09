#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Board.h"
#include "Pieces.h"
#include <memory>

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
static constexpr int ROWS = 8;
static constexpr int COLUMNS = 8;
static constexpr int SQUARE_SIZE = 95;
static constexpr int WINDOW_WIDTH = SQUARE_SIZE * COLUMNS;
static constexpr int WINDOW_HEIGHT = SQUARE_SIZE * ROWS;
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
void PlacePieces(SDL_Renderer* renderer, const Board& board);
void DrawDots(SDL_Renderer* renderer, std::unique_ptr<Piece> piecePtr);
void DrawCircle(SDL_Renderer* renderer, int x, int y, int radius);
};