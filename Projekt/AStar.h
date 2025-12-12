#pragma once
#include <vector>

class AStar{
	std::vector <int> currentPos;
	std::vector <int> goal;
	std::vector <int> start;
	std::vector <std::vector <int>> canMove;
	std::vector <std::vector <int>> cantMove;
	std::vector <std::vector <int>> movement;

	struct Node {
		bool isWorm = false;
		bool isVisited = false;
		int x;
		int y;
		std::vector <Node> neighbours;
	};

	int heuristic(std::vector <int> a, std::vector <int> b);
	bool foundEnd();
public:
	AStar(std::vector <int> wormPos, std::vector <int> foodTile);
	std::vector <std::vector <int>> findMovement();
	std::vector <std::vector <int>> findMovement2();
};

