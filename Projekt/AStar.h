#pragma once
#include "Tile.h"
#include "Node.h"
#include <vector>

class AStar{
	Tile start;
	Tile goal;
	std::vector <std::vector <Tile>>& tiles;
	std::vector <Node*> getNeighbours(Node* current, std::vector <std::vector <Node>>& nodes) const;
	bool containsNode(std::vector <Node*>& list, Node* node) const;
public:
	AStar(Tile start, Tile goal, std::vector <std::vector <Tile>>& tiles);
	std::vector <std::vector <int>> findMovement() const;

};

