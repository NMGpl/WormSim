#include "AStar.h"

AStar::AStar(Tile start, Tile goal, std::vector <std::vector <Tile>>& tiles): goal(goal), start(start), tiles(tiles) {}

std::vector <Node*> AStar::getNeighbours(Node* pCurrent, std::vector <std::vector <Node>>& nodes) const {
	int x = pCurrent->getX();
	int y = pCurrent->getY();
	std::vector <Node*> neighbours;
	int dX[4] = { -1, 0, 1, 0 };
	int dY[4] = { 0, -1, 0, 1 };

	for (int i = 0; i < 4; i++) {
		int newX = x + dX[i];
		int newY = y + dY[i];

		if (newX >= 0 && newX < tiles.size() && newY >= 0 && newY < tiles[0].size()) {		//Funkcja
			if (tiles[newX][newY].isFree()) {
				neighbours.push_back(&nodes[newX][newY]);
			}
		}
	}
	return neighbours;
}

bool AStar::containsNode(std::vector <Node*>& list, Node* node) const {
	for (Node* n : list) {
		if (n->getX() == node->getX() && n->getY() == node->getY()) {
			return true;
		}
	}
	return false;
}

std::vector <std::vector <int>> AStar::findMovement() const {
	std::vector <std::vector <Node>> nodes(tiles.size(), std::vector<Node>(tiles[0].size()));
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[0].size(); j++) {
			nodes[i][j] = Node::tileToNode(tiles[i][j]);
		}
	}
	
	Node* pGoal = &nodes[goal.getX()][goal.getY()];
	Node* pStart = &nodes[start.getX()][start.getY()];
	pStart->setG(0);
	pStart->setH(pStart->getDistance(pGoal));


	std::vector <Node*> toSearch = { pStart };

	pStart->setToSearch(true);

	while (!toSearch.empty()) {
		Node* pCurrent = toSearch[0];
		for (Node* pNode : toSearch) {
			if (pNode->getF() < pCurrent->getF() || (pNode->getF() == pCurrent->getF() && pNode->getH() < pCurrent->getH())) {
				pCurrent = pNode;
			}
		}

		auto index = std::find(toSearch.begin(), toSearch.end(), pCurrent);
		toSearch.erase(index);

		pCurrent->setToSearch(false);
		pCurrent->setProcessed(true);

		if (pCurrent->getX() == pGoal->getX() && pCurrent->getY() == pGoal->getY()) {
			std::vector <std::vector <int>> movement;
			Node* pPath = pGoal;
			while (pPath != pStart) {
				movement.push_back({ pPath->getX(), pPath->getY() });
				pPath = pPath->getParent();
			}
			return movement;
		}

		std::vector <Node*> neighbours = getNeighbours(pCurrent, nodes);			//Najwolniejsza funkcja siwata 2
		for (Node* neighbour : neighbours) {
			if (!neighbour->isProcessed()) {
			//if (!containsNode(processed, neighbour)) {							//Najwolniejsza funkcja œwiata
			//	bool inSearch = containsNode(toSearch, neighbour);
			bool inSearch = neighbour->isToSeach();

				int costToNeighbor = pCurrent->getG() + pCurrent->getDistance(neighbour);
				if (!inSearch || costToNeighbor < neighbour->getG()) {
					neighbour->setG(costToNeighbor);
					neighbour->setParent(pCurrent);
					if (!inSearch) {
						neighbour->setH(neighbour->getDistance(pGoal));
						neighbour->setToSearch(true);
						toSearch.push_back(neighbour);
					}
				}
			}
		}
	}
	return { {pStart->getX(), pStart->getY()} };
}