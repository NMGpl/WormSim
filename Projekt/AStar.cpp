#include "AStar.h"

AStar::AStar(Tile start, Tile goal, std::vector <std::vector <Tile>> tiles): goal(goal), start(start), tiles(tiles) {}

std::vector <Node> AStar::getNeighbours(Node& current) {
	int x = current.getX();
	int y = current.getY();
	std::vector <Node> neighbours;
	int dX[4] = { -1, 0, 1, 0 };
	int dY[4] = { 0, -1, 0, 1 };

	for (int i = 0; i < 4; i++) {
		int newX = x + dX[i];
		int newY = y + dY[i];

		if (newX >= 0 && newX < tiles.size() && newY >= 0 && newY < tiles[0].size()) {
			if (tiles[newX][newY].isWorm()) {
				neighbours.push_back(Node::tileToNode(tiles[newX][newY]));
			}
		}
	}
	return neighbours;
}

std::vector <Node*> AStar::getNeighbours(Node* pCurrent, std::vector <std::vector <Node>>& nodes) {
	int x = pCurrent->getX();
	int y = pCurrent->getY();
	std::vector <Node*> neighbours;
	int dX[4] = { -1, 0, 1, 0 };
	int dY[4] = { 0, -1, 0, 1 };

	for (int i = 0; i < 4; i++) {
		int newX = x + dX[i];
		int newY = y + dY[i];

		if (newX >= 0 && newX < tiles.size() && newY >= 0 && newY < tiles[0].size()) {
			if (tiles[newX][newY].isWorm()) {
				neighbours.push_back(&nodes[newX][newY]);
			}
		}
	}
	return neighbours;
}

bool AStar::containsNode(std::vector <Node*> list, Node* node) {
	for (Node* n : list) {
		if (n->getX() != node->getX() && n->getY() != node->getY()) {
			return true;
		}
	}
	return false;
}

void AStar::goToParent(Node& node, std::vector <Node>& processedNodes) {
	for (Node& n : processedNodes) {
		if (n.getX() == node.getParentX() && n.getY() == node.getParentY()) {
			node.setXY(n.getX(), n.getY());
			node.setParent(n.getParentX(), n.getParentY());
		}
	}
}

//std::vector <std::vector <int>> AStar::findMovement() {
//	Node start(this->start.getX(), this->start.getY());
//	Node goal(this->goal.getX(), this->goal.getY());
//	std::vector <Node> toSearch = { start };
//	std::vector <Node> processed;
//
//	start.setG(0);
//	start.setH(start.getDistance(goal));
//
//	while (!toSearch.empty()) {
//		Node current = toSearch[0];
//		Node* pCurrent = &toSearch[0];
//		/*for (Node& node : toSearch) {
//			if (node.getF() < current.getF() || node.getF() == current.getF() && node.getH() < current.getH()) {
//				current = node;
//			}
//		}*/
//		for (int i = 0; i < toSearch.size(); i++) {
//			Node& node = toSearch[i];
//			if (node.getF() < current.getF() || node.getF() == current.getF() && node.getH() < current.getH()) {
//				current = node;
//				pCurrent = &toSearch[i];
//			}
//		}
//		
//		processed.push_back(current);
//		int index = pCurrent - &toSearch[0];
//		toSearch.erase(toSearch.begin() + index);
//
//		if (current.getX() == goal.getX() && current.getY() == goal.getY()) {
//			std::vector <std::vector <int>> movement;
//			Node pathTile = goal;
//			while (pathTile.getX() != start.getX() || pathTile.getY() != start.getY()) {
//				movement.push_back({ pathTile.getX(), pathTile.getY() });
//				goToParent(pathTile, processed);
//			}
//			return movement;
//		}
//
//		std::vector <Node> neighbours = getNeighbours(current);
//		for (Node& neighbour : neighbours) {
//			if (!containsNode(processed, neighbour)) {
//				bool inSearch = containsNode(toSearch, neighbour);
//				int costToNeighbor = current.getG() + current.getDistance(neighbour);
//				if (!inSearch || costToNeighbor < neighbour.getG()) {
//					neighbour.setG(costToNeighbor);
//					neighbour.setParent(current.getX(), current.getY());
//					if (!inSearch) {
//						neighbour.setH(neighbour.getDistance(goal));
//						toSearch.push_back(neighbour);
//					}
//				}
//			}
//		}
//	}
//	return {};
//}

std::vector <std::vector <int>> AStar::findMovement() {
	std::vector <std::vector <Node>> nodes(tiles[0].size(), std::vector<Node>(tiles.size()));
	for (int i = 0; i < tiles[0].size(); i++) {
		for (int j = 0; j < tiles.size(); j++) {
			nodes[i][j] = Node::tileToNode(tiles[i][j]);
		}
	}
	
	Node* pGoal = &nodes[goal.getX()][goal.getY()];
	Node* pStart = &nodes[start.getX()][start.getY()];
	pStart->setG(0);
	pStart->setH(pStart->getDistance(pGoal));


	std::vector <Node*> toSearch = { pStart };
	std::vector <Node*> processed;

	while (!toSearch.empty()) {
		Node* pCurrent = toSearch[0];
		for (Node* pNode : toSearch) {
			if (pNode->getF() < pCurrent->getF() || (pNode->getF() == pCurrent->getF() && pNode->getH() < pCurrent->getH())) {
				pCurrent = pNode;
			}
		}

		processed.push_back(pCurrent);
		auto index = std::find(toSearch.begin(), toSearch.end(), pCurrent);
		toSearch.erase(index);

		if (pCurrent->getX() == pGoal->getX() && pCurrent->getY() == pGoal->getY()) {
			std::vector <std::vector <int>> movement;
			Node* pPath = pGoal;
			while (pPath != pStart) {
				movement.push_back({ pPath->getX(), pPath->getY() });
				pPath = pPath->getParent();		//nigdzie nie ustawiam wskaznika na parent??????
			}
			return movement;
		}

		std::vector <Node*> neighbours = getNeighbours(pCurrent, nodes);
		for (Node* neighbour : neighbours) {
			if (!containsNode(processed, neighbour)) {
				bool inSearch = containsNode(toSearch, neighbour);
				int costToNeighbor = pCurrent->getG() + pCurrent->getDistance(neighbour);
				if (!inSearch || costToNeighbor < neighbour->getG()) {
					neighbour->setG(costToNeighbor);
					neighbour->setParent(pCurrent);
					if (!inSearch) {
						neighbour->setH(neighbour->getDistance(pGoal));
						toSearch.push_back(neighbour);
					}
				}
			}
		}
	}
	return {};
}