#pragma once

#include <string>
#include <memory>

class Board
{
private:
public:
	std::string matrix[8][8];
	bool whitesMove = true;
	Board();
	void FindKing(int& x, int& y, char color);
};
