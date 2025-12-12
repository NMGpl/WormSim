#include "Tile.h"

Tile::Tile(int x, int y, int foodAmount = 0) {
	this->x = x;
	this->y = y;
	this->foodAmount = foodAmount;
}

int Tile::getX() const {
	return x;
}

int Tile::getY() const {
	return y;
}

void Tile::setPos(int x, int y) {
	x = x;
	y = y;
}

int Tile::getFoodAmount() const {
	return foodAmount;
}

void Tile::modifyFoodAmount(int foodAmount) {
	this->foodAmount += foodAmount;
}

void Tile::setFoodAmount(int foodAmount) {
	this->foodAmount = foodAmount;
}
