#pragma once
class Tile {
	int x;
	int y;
	int foodAmount;
	bool isWorm = false;
public:
	Tile(int x, int y, int foodAmount);
	int getX() const;
	int getY() const;
	void setPos(int x, int y);
	int getFoodAmount() const;
	void modifyFoodAmount(int foodAmount);
	void setFoodAmount(int foodAmount);
};