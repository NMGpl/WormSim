#include "SimulationConfig.h"

SimulationConfig::SimulationConfig(int maxAge, int maxHunger, int maxSize, int regenSpeed, int maxProductivity, int newWormsAmount, int width, int height) {
	this->maxAge = maxAge;
	this->maxHunger = maxHunger;
	this->maxSize = maxSize;
	this->regenSpeed = regenSpeed;
	this->maxProductivity = maxProductivity;
	this->newWormsAmount = newWormsAmount;
	this->width = width;
	this->height = height;
	this->wormOnMouse = false;
	this->foodOnMouse = false;
}

void SimulationConfig::setMaxAge(int maxAge) {
	this->maxAge = maxAge;
}

int SimulationConfig::getMaxAge() const {
	return maxAge;
}

void SimulationConfig::setMaxHunger(int maxHunger) {
	this->maxHunger = maxHunger;
}

void SimulationConfig::setRegenSpeed(int regenSpeed) {
	this->regenSpeed = regenSpeed;
}

void SimulationConfig::setMaxProductivity(int maxProductivity) {
	this->maxProductivity = maxProductivity;
}

void SimulationConfig::setNewWormsAmount(int newWormsAmount) {
	this->newWormsAmount = newWormsAmount;
}

void SimulationConfig::setWidth(int width) {
	this->width = width;
}

void SimulationConfig::setHeight(int height) {
	this->height = height;
}

void SimulationConfig::setMaxSize(int maxSize) {
	this->maxSize = maxSize;
}

void SimulationConfig::setWormOnMouse(bool state) {
	this->wormOnMouse = state;
}

void SimulationConfig::setFoodOnMouse(bool state) {
	this->foodOnMouse = state;
}

void SimulationConfig::toggleWormOnMouse() {
	this->wormOnMouse = !wormOnMouse;
}

void SimulationConfig::toggleFoodOnMouse() {
	this->foodOnMouse = !foodOnMouse;
}

void SimulationConfig::setBoardWidth(int newWidth) {
	this->width = newWidth;
}

void SimulationConfig::setBoardHeight(int newHeight) {
	this->height = newHeight;
}

int SimulationConfig::getMaxHunger() const {
	return maxHunger;
}

int SimulationConfig::getMaxSize() const {
	return maxSize;
}

int SimulationConfig::getRegenSpeed() const {
	return regenSpeed;
}

int SimulationConfig::getMaxProductivity() const {
	return maxProductivity;
}

int SimulationConfig::getNewWormsAmount() const {
	return newWormsAmount;
}

int SimulationConfig::getSize() const {
	if (width < height || height * maxWidth / width > maxHeight) {
		return maxHeight / height;
	}
	else {
		return maxWidth / width;
	}
}

int SimulationConfig::getStartX() const {
	return startX + ((maxWidth - width * getSize()) / 2);
}

bool SimulationConfig::getWormOnMouse() const {
	return wormOnMouse;
}

bool SimulationConfig::getFoodOnMouse() const {
	return foodOnMouse;
}

int SimulationConfig::getWidth() const {
	return width;
}

int SimulationConfig::getHeight() const {
	return height;
}