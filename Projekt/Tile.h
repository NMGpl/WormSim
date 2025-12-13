#pragma once
class Tile {
	int x;
	int y;
	int foodAmount;
	bool worm = false;
public:
	Tile(int x, int y, int foodAmount = 0);
	int getX() const;
	int getY() const;
	void setPos(int x, int y);
	int getFoodAmount() const;
	void modifyFoodAmount(int foodAmount);
	void setFoodAmount(int foodAmount);
	bool isWorm();
	void setIsFree(bool worm);
};