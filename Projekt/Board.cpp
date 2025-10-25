#include "Board.h"
#include <stdio.h>
#include <iostream>

void Board::initializeBoard() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			board[j][i] = 5;
		}
	}
}

void Board::printBoard() const {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			std::cout << "[" << board[j][i] << "]";
		}
		std::cout << std::endl;
	}
}
