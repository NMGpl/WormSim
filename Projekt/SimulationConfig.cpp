#include "SimulationConfig.h"
#include <iostream>

SimulationConfig::SimulationConfig(int maxAge, int maxHunger, int maxSize, int regenSpeed, int maxProductivity, int newWormsAmount) {
	this->maxAge = maxAge;
	this->maxHunger = maxHunger;
	this->maxSize = maxSize;
	this->regenSpeed = regenSpeed;
	this->maxProductivity = maxProductivity;
	this->newWormsAmount = newWormsAmount;
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

void SimulationConfig::setMaxProductivity(int maxProductivity) {
	this->maxProductivity = maxProductivity;
}

void SimulationConfig::setNewWormsAmount(int newWormsAmount) {
	this->newWormsAmount = newWormsAmount;
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

int SimulationConfig::getMaxProductivity() {
	return maxProductivity;
}

int SimulationConfig::getNewWormsAmount() {
	return newWormsAmount;
}