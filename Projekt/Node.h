#pragma once
#include "Tile.h"
#include <climits>
#include <vector>

class Node
{
	int x;
	int y;
	int g;
	int h;
	Node* pParent = nullptr;
	bool toSearch = false;
	bool processed = false;
public:
	Node();
	Node(int x, int y);
	void reset();
	static Node tileToNode(Tile& tile);
	void setG(int g);
	void setH(int h);
	void setXY(int x, int y);
	void setParent(Node* pParent);
	Node* getParent() const;
	int getF() const;
	int getH() const;
	int getG() const;
	int getX() const;
	int getY() const;
	int getDistance(Node* neighbour) const;
	bool isToSeach() const;
	void setToSearch(bool toSearch);
	bool isProcessed() const;
	void setProcessed(bool processed);
};

