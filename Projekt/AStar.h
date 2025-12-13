#pragma once
#include <vector>
#include "Tile.h"
#include "Node.h"

class AStar{
	Tile start;
	Tile goal;
	std::vector <std::vector <Tile>>& tiles;
	std::vector <Node*> getNeighbours(Node* current, std::vector <std::vector <Node>>& nodes);
	bool containsNode(std::vector <Node*>& list, Node* node);
public:
	AStar(Tile start, Tile goal, std::vector <std::vector <Tile>>& tiles);
	std::vector <std::vector <int>> findMovement();

};

