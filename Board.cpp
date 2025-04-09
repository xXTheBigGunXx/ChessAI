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
