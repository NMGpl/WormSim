#pragma once
#include <vector>

class AStar{
	std::vector <int> finalStep;
	std::vector <std::vector <int>> canMove;
	std::vector <std::vector <int>> cantMove;

public:
	AStar(std::vector <int> wormPos, std::vector <int> foodTile);
	std::vector <std::vector <int>> findMovement();
};

