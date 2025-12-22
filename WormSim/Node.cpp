#include "Node.h"

Node::Node() {
	this->x = 0;
	this->y = 0;
	this->g = INT_MAX;
	this->h = INT_MAX;
}
Node::Node(int x, int y) {
	this->x = x;
	this->y = y;

	this->g = INT_MAX;
	this->h = INT_MAX;
}

Node Node::tileToNode(Tile& tile) {
	return Node(tile.getX(), tile.getY());
}

void Node::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}

void Node::setG(int g) {
	this->g = g;
}

void Node::setH(int h) {
	this->h = h;
}

void Node::setParent(Node* pParent) {
	this->pParent = pParent;
}

Node* Node::getParent() const {
	return pParent;
}

int Node::getF() const {
	return g + h;
}

int Node::getG() const {
	return g;
}

int Node::getH() const {
	return h;
}

int Node::getX() const {
	return x;
}

int Node::getY() const {
	return y;
}

int Node::getDistance(Node* neighbour) const {
	int distance = abs(x - neighbour->getX()) + abs(y - neighbour->getY());
	return distance;
}

bool Node::isToSeach() const {
	return toSearch;
}

void Node::setToSearch(bool toSearch) {
	this->toSearch = toSearch;
}

bool Node::isProcessed() const {
	return processed;
}

void Node::setProcessed(bool processed) {
	this->processed = processed;
}
