#pragma once
class Tile {
	int x;
	int y;
	int foodAmount;
	bool isWorm = false;
public:
	Tile(int foodAmount);
	int getX() const;
	int getY() const;
	void setPos(int x, int y);
	int getFoodAmount() const;
	void setFoodAmount(int foodAmount);
};