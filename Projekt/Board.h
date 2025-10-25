#pragma once
class Board {
	int x, y;
	int boardWidth = 15;
	int boardHeight = 10;
	int board[15][10];
public:
	void initializeBoard();
	void printBoard() const;

};

