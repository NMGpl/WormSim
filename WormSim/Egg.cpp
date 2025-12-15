#include "Egg.h"

Egg::Egg(int posX, int posY, int newWorms) {
	this->posX = posX;
	this->posY = posY;
	this->newWorms = newWorms;
}

void Egg::ageUp() {
	this->age += 1;
}

bool Egg::hatch() {
	if (age >= maxAge) {
		hatched = 1;
		return 1;
	}
	ageUp();
	return 0;
}

bool Egg::isHatched() const {
	return hatched;
}

int Egg::getX() const {
	return posX;
}

int Egg::getY() const {
	return posY;
}

int Egg::getNewWorms() const {
	return newWorms;
}