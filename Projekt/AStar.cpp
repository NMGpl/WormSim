#include "AStar.h"

AStar::AStar(std::vector <int> wormPos, std::vector <int> foodTile) {
	this->goal = foodTile;
	this->start = wormPos;
}

//std::vector <std::vector <int>> AStar::findMovement() {
//	currentPos = firstStep;
//	while (!foundEnd()) {
//		
//
//		if (!canMove.empty()) {
//			//currentPos = canMove.pop_back();
//		}
//		else {
//			break;
//		}
//
//		movement.push_back(currentPos);
//	}
//
//	return movement;
//}




//std::vector <std::vector <int>> AStar::findMovement2() {
//	std::vector <int> frontier = currentPos;
//	frontier.push_back(0);
//	cameFrom = NULL;
//	cost = 0;
//
//	while (!frontier.empty()) {
//		std::vector <int> current = frontier;
//
//		if (current[0] == finalStep[0] && current[1] == finalStep[1]) {
//			break;
//		}
//
//		for ()
//	}
//}

bool AStar::foundEnd() {
	if (currentPos == goal) {
		return true;
	}
	return false;
}

std::vector <std::vector <int>> checkNeighbors(std::vector <int> currentPos) {
	currentPos
}

int AStar::heuristic(std::vector <int> a, std::vector <int> b) {
	int heuristic = abs(a[0] - b[0]) + abs(a[1] - b[1]);
	return heuristic;
}

std::vector <std::vector <int>> AStar::findMovement() {
	std::vector <std::vector <int>> frontier = { start };
	frontier[0].push_back(0);											//frontier = {(X, Y, cost)}

	std::vector <int> cameFrom = start;
	std::vector <int> cost = { 0 };

	while (!frontier.empty()) {
		std::vector <std::vector <int>> currentPos = { frontier.front() };			//priority queue do zrobienia

		if (currentPos.front() == goal) {
			break;
		}

		for (std::vector <int> next : neighbors(currentPos.front()) {
			int newCost = cost[currentPos] + cost(currentPos, next);
			if (cost.find(next) == cost.end() || newCost < cost[next]) {
				cost = newCost;
				int priority = newCost + heuristic(next, goal);
				frontier.push_back(next, priority);
				cameFrom[next] = current;
			}
		}
	}
}

std::vector <int> neighbors(std::vector <int> currentPos) {

	return currentPos;
}