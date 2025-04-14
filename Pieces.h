#pragma once

#include <utility>
#include <vector>
#include <memory>
#include "Board.h"

struct Piece {
    std::vector<std::pair<int, int>> legalMoves;
    int x, y;
    char color;

    Piece(char col, int x, int y) : color(col), x(x), y(y) {}

    virtual void PlaceLegalMove(Board* board) {}
    virtual ~Piece() = default;
};

struct King : public Piece {
    King(char col, int x, int y) : Piece(col, x, y) {}
    void PlaceLegalMove(Board* board) override; 
};

struct Queen : public Piece {
	Queen(char col, int x, int y) : Piece(col, x, y) {}
	void PlaceLegalMove(Board* board) override;
};

struct Rook : public Piece {
	Rook(char col, int x, int y) : Piece(col, x, y) {}
	void PlaceLegalMove(Board* board) override;
};

struct Bishop : public Piece {
	Bishop(char col, int x, int y) : Piece(col, x, y) {}
	void PlaceLegalMove(Board* board) override;
};

struct Knight : public Piece {
	Knight(char col, int x, int y) : Piece(col, x, y) {}
	void PlaceLegalMove(Board* board) override;
};

struct Pawn : public Piece {
    Pawn(char col, int x, int y) : Piece(col, x, y) {}
    void PlaceLegalMove(Board* board) override; 
};

std::unique_ptr<Piece> GetPiece(Board* board, int x, int y);
std::unique_ptr<Piece> CanKingBeCaptured(Board* board, King* king);
