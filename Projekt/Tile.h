#pragma once
class Tile {
	int pos[2];
	int foodAmount;
public:
	Tile(int foodAmount);
	int getX() const;
	int getY() const;
	void setPos(int x, int y);
	int getFoodAmount() const;
	void setFoodAmount(int foodAmount);
};

