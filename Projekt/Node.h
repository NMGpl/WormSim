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
	
	static Node tileToNode(Tile& tile);

	void setG(int g);
	void setH(int h);
	void setXY(int x, int y);
	void setProcessed(bool processed);
	void setToSearch(bool toSearch);
	void setParent(Node* pParent);

	int getF() const;
	int getH() const;
	int getG() const;
	int getX() const;
	int getY() const;
	bool isProcessed() const;
	bool isToSeach() const;
	Node* getParent() const;
	int getDistance(Node* neighbour) const;
};

