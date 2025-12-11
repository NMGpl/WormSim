#include "AStar.h"

AStar::AStar(std::vector <int> wormPos, std::vector <int> foodTile) {
	this->finalStep = foodTile;
	this->canMove.push_back(wormPos);
}

std::vector <std::vector <int>> AStar::findMovement() {

}