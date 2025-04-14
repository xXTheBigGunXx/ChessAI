#include <utility>
#include <vector>
#include <memory>
#include "Board.h"
#include "Pieces.h"
#include "BoardRenderer.h"
#include <iostream>
#include <typeinfo>

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

    int tempx, tempy;
    board->FindKing(tempx, tempy, color);
    if (tempx == -1 || tempy == -1)
    {
        std::cout << "There is no " << color << " king on a board.\n";
        return;
    }

    King* king = new King(color, tempx, tempy);
    board->matrix[y][x] = "  ";
    auto piece = CanKingBeCaptured(board, king);
	board->matrix[y][x] = std::string(1, 'Q') + color;  

    std::vector<std::pair<int, int>> filteredMoves;
    if (piece != nullptr)
    {
        std::cout << "King can't move, because of piece: " << piece->x << ", " << piece->y << std::endl;
		piece->PlaceLegalMove(board);

        for (const auto& checkMove : piece->legalMoves)
        {
            
            for (const auto& move : legalMoves)
            {
                if (move.first == checkMove.first && move.second == checkMove.second)
                {
                    filteredMoves.push_back(std::make_pair(move.first, move.second));
                }
            }
        }

        legalMoves = std::move(filteredMoves);
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

std::unique_ptr<Piece> CanKingBeCaptured(Board* board, King* king) 
{
    char oppColor = king->color == 'W' ? 'B' : 'W';
    auto bishopSim = std::make_unique<Bishop>(king->color, king->x, king->y);
    bishopSim->PlaceLegalMove(board);

    for (const auto& move : bishopSim->legalMoves) {
        std::string target = board->matrix[move.second][move.first];
        if (target == "B" + std::string(1, oppColor))
            return std::make_unique<Bishop>(oppColor, move.first, move.second);
        if (target == "Q" + std::string(1, oppColor))
            return std::make_unique<Queen>(oppColor, move.first, move.second);
    }

    auto rookSim = std::make_unique<Rook>(king->color, king->x, king->y);
    rookSim->PlaceLegalMove(board);

    for (const auto& move : rookSim->legalMoves) {
        std::string target = board->matrix[move.second][move.first];
        if (target == "R" + std::string(1, oppColor))
            return std::make_unique<Rook>(oppColor, move.first, move.second);
        if (target == "Q" + std::string(1, oppColor))
            return std::make_unique<Queen>(oppColor, move.first, move.second);
    }

    auto knightSim = std::make_unique<Knight>(king->color, king->x, king->y);
    knightSim->PlaceLegalMove(board);

    for (const auto& move : knightSim->legalMoves) {
        if (board->matrix[move.second][move.first] == "N" + std::string(1, oppColor))
            return std::make_unique<Knight>(oppColor, move.first, move.second);
    }

    int dy = (king->color == 'W') ? 1 : -1;
    int pawnY = king->y + dy;

    if (pawnY >= 0 && pawnY < 8) {
        if (king->x - 1 >= 0 && board->matrix[pawnY][king->x - 1] == "P" + std::string(1, oppColor))
            return std::make_unique<Pawn>(oppColor, king->x - 1, pawnY);
        if (king->x + 1 < 8 && board->matrix[pawnY][king->x + 1] == "P" + std::string(1, oppColor))
            return std::make_unique<Pawn>(oppColor, king->x + 1, pawnY);
    }
    return nullptr;
}