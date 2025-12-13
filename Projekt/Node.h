#pragma once
#include <climits>
#include <vector>
#include "Tile.h"

class Node
{
	int x;
	int y;

	int g;
	int h;
	Node* pParent = nullptr;
	int parentX;
	int parentY;
public:
	Node(int x, int y);
	void reset();
	static Node tileToNode(Tile& tile);
	void setG(int g);
	void setH(int h);
	void setXY(int x, int y);
	void setParent(int parentX, int parentY);
	void setParent(Node* pParent);
	Node* getParent();
	int getParentX();
	int getParentY();
	int getF();
	int getH();
	int getG();
	int getX();
	int getY();
	int getDistance(Node* neighbour);
	std::vector <Node> getNeighbours();
};

