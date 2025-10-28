#include "Tile.h"

Tile::Tile() {
	pos[0] = {5};
	pos[1] = {10};
	foodAmount = 0;
}

int Tile::getX() const {
	return pos[0];
}

int Tile::getY() const {
	return pos[1];
}

void Tile::setPos(int x, int y) {
	pos[0] = x;
	pos[1] = y;
}

int Tile::getFoodAmount() const {
	return foodAmount;
}
void Tile::setFoodAmount(int foodAmount) {
	this->foodAmount = foodAmount;
}
