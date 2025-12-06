#include "SimulationConfig.h"
#include <iostream>

SimulationConfig::SimulationConfig(int maxAge, int maxHunger, int maxSize) {
	this->maxAge = maxAge;
	this->maxHunger = maxHunger;
	this->maxSize = maxSize;
}

void SimulationConfig::setMaxAge(int maxAge) {
	this->maxAge = maxAge;
}

int SimulationConfig::getMaxAge() {
	return maxAge;
}

void SimulationConfig::setMaxHunger(int maxHunger) {
	this->maxHunger = maxHunger;
}

void SimulationConfig::setRegenSpeed(int regenSpeed) {
	this->regenSpeed = regenSpeed;
}

int SimulationConfig::getMaxHunger() {
	return maxHunger;
}

void SimulationConfig::setMaxSize(int maxSize) {
	this->maxSize = maxSize;
}

int SimulationConfig::getMaxSize() {
	return maxSize;
}

int SimulationConfig::getRegenSpeed() {
	return regenSpeed;
}