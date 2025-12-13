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

void Node::reset() {
	g = INT_MAX;
	h = 0;
	pParent = nullptr;
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

Node* Node::getParent() {
	return pParent;
}

int Node::getF() {
	return g + h;
}

int Node::getG() {
	return g;
}

int Node::getH() {
	return h;
}

int Node::getX() {
	return x;
}

int Node::getY() {
	return y;
}

int Node::getDistance(Node* neighbour) {
	int distance;
	distance = abs(x - neighbour->getX()) + abs(y - neighbour->getY());
	return distance;
}