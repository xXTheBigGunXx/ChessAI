#include <utility>
#include <vector>
#include <memory>
#include "Board.h"
#include "Pieces.h"
#include "BoardRenderer.h"
#include <iostream>

void King::PlaceLegalMove(Board* board) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                if(board->matrix[newY][newX] == "  ")
                    legalMoves.emplace_back(newX, newY);
            }
        }
    }
}

void Queen::PlaceLegalMove(Board* board)
{
    for (int i = 1; i < 8; i++)
    {
        if (x + i < 8 && y + i < 8 && board->matrix[y + i][x + i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x + i, y + i));
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++) {
        if (x - i > -1 && y + i < 8 && board->matrix[y + i][x - i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x - i, y + i));
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++) {
        if (x + i < 8 && y - i > -1 && board->matrix[y - i][x + i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x + i, y - i));
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++) {
        if (x - i > -1 && y - i > -1 && board->matrix[y - i][x - i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x - i, y - i));
        }
        else {
            break;
        }
    }

    for (int i = y; i > -1; i--)
    {
        if (board->matrix[i][x] == "  ")
        {
            legalMoves.push_back(std::make_pair(x, i));
        }
        else if (y == i)
            continue;
        else {
            break;
        }
    }
    for (int i = y; i < 8; i++)
    {
        if (board->matrix[i][x] == "  ")
        {
            legalMoves.push_back(std::make_pair(i, y));
        }
        else if (x == i)
            continue;
        else {
            break;
        }
    }

    for (int i = x; i > -1; i--)
    {
        if (board->matrix[y][i] == "  ")
        {
            legalMoves.push_back(std::make_pair(i, y));
        }
        else if (x == i)
            continue;
        else {
            break;
        }
    }
    for (int i = y; i < 8; i++)
    {
        if (board->matrix[y][i] == "  ")
        {
            legalMoves.push_back(std::make_pair(x, i));
        }
        else if (y == i)
            continue;
        else {
            break;
        }
    }
}

void Rook::PlaceLegalMove(Board *board)
{
    for (int i = y; i > -1; i--)
    {
        if (board->matrix[i][x] == "  ")
        {
            legalMoves.push_back(std::make_pair(x, i));
        }
        else if (y == i)
            continue;
        else {
            break;
        }
    }
    for (int i = y; i < 8; i++)
    {
        if (board->matrix[i][x] == "  ")
        {
            legalMoves.push_back(std::make_pair(x, i));
        }
        else if (y == i)
            continue;
        else {
            break;
        }
    }

    for (int i = x; i > -1; i--)
    {
        if (board->matrix[y][i] == "  ")
        {
            legalMoves.push_back(std::make_pair(i, y));
        }
        else if (x == i)
            continue;
        else {
            break;
        }
    }
    for (int i = x; i < 8; i++)
    {
        if (board->matrix[y][i] == "  ")
        {
            legalMoves.push_back(std::make_pair(i, y));
        }
        else if (x == i)
            continue;
        else {
            break;
        }
    }
}

void Bishop::PlaceLegalMove(Board* board)
{
    std::cout << "Bishop " << x << ' ' << y << std::endl;
    for (int i = 1; i < 8; i++)
    {
        if (x + i < 8 && y + i < 8 && board->matrix[y + i][x + i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x + i, y + i));
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++){
        if (x - i > -1 && y + i < 8 && board->matrix[y + i][x - i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x - i, y + i));
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++) {
        if (x + i < 8 && y - i > -1 && board->matrix[y - i][x + i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x + i, y - i));
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++){
        if (x - i > -1 && y - i > -1 && board->matrix[y - i][x - i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x - i, y - i));
		}
        else {
            break;
        }
	}
}

void Knight::PlaceLegalMove(Board* board)
{
    const int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    const int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    for (int i = 0; i < 8; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 &&
            (board->matrix[newY][newX] == "  " || board->matrix[newY][newX][1] != color)) {
            legalMoves.emplace_back(newX, newY);
        }
    }
}

void Pawn::PlaceLegalMove(Board* board) {
    if (color == 'W') {
        if (y > 0 && board->matrix[y - 1][x][0] == ' ') {
            legalMoves.emplace_back(x, y - 1);
            if (y == 6 && y > 1 && board->matrix[y - 2][x][0] == ' ')
                legalMoves.emplace_back(x, y - 2);
        }
    }
    else if (color == 'B') {
        if (y < 7 && board->matrix[y + 1][x][0] == ' ') {
            legalMoves.emplace_back(x, y + 1);
            if (y == 1 && y < 6 && board->matrix[y + 2][x][0] == ' ')
                legalMoves.emplace_back(x, y + 2);
        }
    }
}

std::unique_ptr<Piece> GetPiece(Board* board, int x, int y)
{

	if (x >= 0 && x < 8 && y > 0 && x < 8) {
		switch (board->matrix[y][x][0]) {
		case 'P':
			return std::make_unique<Pawn>(board->matrix[y][x][1], x, y);
		case 'K':
			return std::make_unique<King>(board->matrix[y][x][1], x, y);
		case 'N':
			return std::make_unique<Knight>(board->matrix[y][x][1], x, y);
		case 'B':
			return std::make_unique<Bishop>(board->matrix[y][x][1], x, y);
		case 'Q':
			return std::make_unique<Queen>(board->matrix[y][x][1], x, y);
		case 'R':
			return std::make_unique<Rook>(board->matrix[y][x][1], x, y);
		}
	}
	return nullptr;
}