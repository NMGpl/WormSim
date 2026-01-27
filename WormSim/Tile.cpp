#include "Tile.h"

Tile::Tile(int x, int y, int foodAmount) {
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
	this->x = x;
	this->y = y;
}

int Tile::getFoodAmount() const {
	return foodAmount;
}

void Tile::modifyFoodAmount(int foodAmount) {
	if (this->foodAmount + foodAmount >= 0) {
		while (this->foodAmount + foodAmount > 3) {
			foodAmount -= 1;
		}
		this->foodAmount += foodAmount;
	}
}

void Tile::setFoodAmount(int foodAmount) {
	this->foodAmount = foodAmount;
}

bool Tile::isFree() const {
	return free;
}

void Tile::setFree(bool free) {
	this->free = free;
}