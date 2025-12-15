#pragma once
class Tile {
	int x;
	int y;
	int foodAmount;
	bool free = true;
public:
	Tile(int x, int y, int foodAmount = 0);
	
	void setPos(int x, int y);
	void setFoodAmount(int foodAmount);
	void modifyFoodAmount(int foodAmount);
	void setFree(bool free);
	
	int getX() const;
	int getY() const;
	int getFoodAmount() const;
	bool isFree() const;
};