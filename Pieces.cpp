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
                if(board->matrix[newY][newX][1] != color)
                    legalMoves.emplace_back(newX, newY);
            }
        }
    }
}

void Queen::PlaceLegalMove(Board* board)
{
    board->matrix[y][x] = "  ";
    int ax, ay;

	board->FindKing(ax, ay, color);

	King* king = new King(board->matrix[y][x][1], ax, ay);
    bool flag = CanKingMove(board, king);
    board->matrix[y][x] = std::string(1, 'Q') + color;

    if (flag == false)
        return;


    for (int i = 1; i < 8; i++)
    {
        if (x + i < 8 && y + i < 8 && board->matrix[y + i][x + i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x + i, y + i));
        }
        else if (x + i < 8 && y + i < 8 && board->matrix[y + i][x + i][1] != color)
        {
            legalMoves.push_back(std::make_pair(x + i, y + i));
            break;
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++) {
        if (x - i > -1 && y + i < 8 && board->matrix[y + i][x - i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x - i, y + i));
        }
        else if (x - i > -1 && y + i < 8 && board->matrix[y + i][x - i][1] != color)
        {
            legalMoves.push_back(std::make_pair(x - i, y + i));
            break;
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++) {
        if (x + i < 8 && y - i > -1 && board->matrix[y - i][x + i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x + i, y - i));
        }
        else if (x + i < 8 && y - i > -1 && board->matrix[y - i][x + i][1] != color)
        {
            legalMoves.push_back(std::make_pair(x + i, y - i));
            break;
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++) {
        if (x - i > -1 && y - i > -1 && board->matrix[y - i][x - i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x - i, y - i));
        }
        else if (x - i > -1 && y - i > -1 && board->matrix[y - i][x - i][1] != color)
        {
            legalMoves.push_back(std::make_pair(x - i, y - i));
            break;
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
        else if (board->matrix[i][x][1] != color)
        {
            legalMoves.push_back(std::make_pair(x, i));
            break;
        }
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
        else if (board->matrix[i][x][1] != color)
        {
            legalMoves.push_back(std::make_pair(x, i));
            break;
        }
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
        else if (board->matrix[y][i][1] != color)
        {
            legalMoves.push_back(std::make_pair(i, y));
            break;
        }
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
        else if (board->matrix[y][i][1] != color)
        {
            legalMoves.push_back(std::make_pair(i, y));
            break;
        }
        else {
            break;
        }
    }
}

void Rook::PlaceLegalMove(Board *board)
{
    board->matrix[y][x] = "  ";
    int ax, ay;

    board->FindKing(ax, ay, color);

    King* king = new King(board->matrix[y][x][1], ax, ay);
    bool flag = CanKingMove(board, king);
    board->matrix[y][x] = std::string(1, 'R') + color;

    if (flag == false)
        return;

    for (int i = y; i > -1; i--)
    {
        if (board->matrix[i][x] == "  ")
        {
            legalMoves.push_back(std::make_pair(x, i));
        }
        else if (y == i)
            continue;
        else if (board->matrix[i][x][1] != color)
        {
            legalMoves.push_back(std::make_pair(x,i));
            break;
        }
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
        else if (board->matrix[i][x][1] != color)
        {
            legalMoves.push_back(std::make_pair(x, i));
            break;
        }
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
        else if (board->matrix[y][i][1] != color)
        {
            legalMoves.push_back(std::make_pair(i,y));
            break;
        }
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
        else if (board->matrix[y][i][1] != color)
        {
            legalMoves.push_back(std::make_pair(i,y));
            break;
        }
        else {
            break;
        }
    }
}

void Bishop::PlaceLegalMove(Board* board)
{
    board->matrix[y][x] = "  ";
    int ax, ay;

    board->FindKing(ax, ay, color);

    King* king = new King(board->matrix[y][x][1], ax, ay);
    bool flag = CanKingMove(board, king);
    board->matrix[y][x] = std::string(1, 'B') + color;

    if (flag == false)
        return;

    for (int i = 1; i < 8; i++)
    {
        if (x + i < 8 && y + i < 8 && board->matrix[y + i][x + i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x + i, y + i));
        }
        else if (x + i < 8 && y + i < 8 && board->matrix[y + i][x + i][1] != color)
        {
			legalMoves.push_back(std::make_pair(x + i, y + i));
            break;
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++){
        if (x - i > -1 && y + i < 8 && board->matrix[y + i][x - i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x - i, y + i));
        }
        else if (x - i > -1 && y + i < 8 && board->matrix[y + i][x - i][1] != color) 
        {
            legalMoves.push_back(std::make_pair(x - i, y + i));
            break;
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++) {
        if (x + i < 8 && y - i > -1 && board->matrix[y - i][x + i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x + i, y - i));
        }
        else if (x + i < 8 && y - i > -1 && board->matrix[y - i][x + i][1] != color) 
        {
            legalMoves.push_back(std::make_pair(x + i, y - i));
            break;
        }
        else {
            break;
        }
    }
    for (int i = 1; i < 8; i++){
        if (x - i > -1 && y - i > -1 && board->matrix[y - i][x - i][0] == ' ') {
            legalMoves.push_back(std::make_pair(x - i, y - i));
		}
        else if (x - i > -1 && y - i > -1 && board->matrix[y - i][x - i][1] != color) 
        {
            legalMoves.push_back(std::make_pair(x - i, y - i));
            break;
        }
        else {
            break;
        }
	}
}

void Knight::PlaceLegalMove(Board* board)
{
    board->matrix[y][x] = "  ";
    int ax, ay;

    board->FindKing(ax, ay, color);

    King* king = new King(board->matrix[y][x][1], ax, ay);
    bool flag = CanKingMove(board, king);
    board->matrix[y][x] = std::string(1, 'N') + color;

    if (flag == false)
        return;

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

    board->matrix[y][x] = "  ";
    int ax, ay;

    board->FindKing(ax, ay, color);

    King* king = new King(board->matrix[y][x][1], ax, ay);
    bool flag = CanKingMove(board, king);
    board->matrix[y][x] = std::string(1, 'P') + color;

    if (flag == false)
        return;

    if (color == 'W') {
        if (y > 0 && board->matrix[y - 1][x][0] == ' ') {
            legalMoves.emplace_back(x, y - 1);
            if (y == 6 && y > 1 && board->matrix[y - 2][x][0] == ' ')
                legalMoves.emplace_back(x, y - 2);
        }
        if (y > 0)
        {
            if(x > 0){
                if (board->matrix[y - 1][x - 1][1] == 'B') {
                    legalMoves.emplace_back(x - 1, y - 1);
                }
            }
            if (x < 7) {
                if (board->matrix[y - 1][x + 1][1] == 'B') {
                    legalMoves.emplace_back(x + 1, y - 1);
                }
            }
        }
    }
    else if (color == 'B') {
        if (y < 7 && board->matrix[y + 1][x][0] == ' ') {
            legalMoves.emplace_back(x, y + 1);
            if (y == 1 && y < 6 && board->matrix[y + 2][x][0] == ' ')
                legalMoves.emplace_back(x, y + 2);
        }
        if (y < 7)
        {
            if (x > 0) {
                if (board->matrix[y + 1][x - 1][1] == 'W') {
                    legalMoves.emplace_back(x - 1, y + 1);
                }
            }
            if (x < 7) {
                if (board->matrix[y + 1][x + 1][1] == 'W') {
                    legalMoves.emplace_back(x + 1, y + 1);
                }
            }
        }
    }
}

std::unique_ptr<Piece> GetPiece(Board* board, int x, int y)
{

	if (x >= 0 && x < 8 && y >= 0 && x < 8) {
		char color = board->whitesMove ? 'W' : 'B';
        if (board->matrix[y][x][1] != color)
            return nullptr;
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

bool CanKingMove(Board* board, King* king)
{
	void* piece = new Bishop(board->matrix[king->y][king->x][1], king->x, king->y);
	char oppColor = king->color == 'W' ? 'B' : 'W';
    static_cast<Bishop*>(piece)->PlaceLegalMove(board);

    for (auto& i : static_cast<Bishop*>(piece)->legalMoves)
    {
        if (board->matrix[i.second][i.first] == std::string(1, 'B') + oppColor || board->matrix[i.second][i.first] == std::string(1, 'Q') + oppColor)
            return false;
    }

	piece = new Rook(board->matrix[king->y][king->x][1], king->x, king->y);
	static_cast<Rook*>(piece)->PlaceLegalMove(board);

	for (auto& i : static_cast<Rook*>(piece)->legalMoves)
	{
		if (board->matrix[i.second][i.first] == std::string(1, 'R') + oppColor || board->matrix[i.second][i.first] == std::string(1, 'Q') + oppColor)
			return false;
	}

	piece = new Knight(board->matrix[king->y][king->x][1], king->x, king->y);
	static_cast<Knight*>(piece)->PlaceLegalMove(board);

    for (auto& i : static_cast<Knight*>(piece)->legalMoves)
    {
		if (board->matrix[i.second][i.first] == std::string(1, 'N') + oppColor)
			return false;
    }
	//piece = new Pawn(board->matrix[king->y][king->x][1], king->x, king->y);

    if (king->color == 'W') {
        if (king->y + 1 < 7 && king->x - 1 > 0 && board->matrix[king->y + 1][king->x - 1] == std::string(1, 'P') + oppColor) {
            return false;
        }
        if (king->y + 1 < 7 && king->x + 1 < 8 && board->matrix[king->y + 1][king->x + 1] == std::string(1, 'P') + oppColor) {
            return false;
        }
    }

    return true;
}