#include "Board.h"

Board::Board() {
	const std::string pattern = "RNBQKBNR";

	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			if (i == 0) matrix[i][j] = std::string(1, pattern[j]) + "B";
			else if (i == 1) matrix[i][j] = "PB";
			else if (i == 6) matrix[i][j] = "PW";
			else if (i == 7) matrix[i][j] = std::string(1, pattern[j]) + "W";
			else matrix[i][j] = "  ";
		}
    } 
};

void Board::FindKing(int& x, int& y, char color)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (matrix[i][j][0] == 'K' && matrix[i][j][1] == color)
			{
				x = j;
				y = i;
				return;
			}
		}
	}
}
