#include "SimulationConfig.h"
#include <iostream>

//void SimulationConfig::printConfig() const {
//	std::cout << "Max age: " << maxAge << std::endl;
//	std::cout << "Max hunger: " << maxHunger << std::endl;
//	std::cout << "Max size: " << maxSize << std::endl;
//}

void SimulationConfig::setMaxAge(int maxAge) {
	this->maxAge = maxAge;
}

int SimulationConfig::getMaxAge() const {
	return maxAge;
}

void SimulationConfig::setMaxHunger(int maxHunger) {
	this->maxHunger = maxHunger;
}

int SimulationConfig::getMaxHunger() const {
	return maxHunger;
}

void SimulationConfig::setMaxSize(int maxSize) {
	this->maxSize = maxSize;
}

int SimulationConfig::getMaxSize() const {
	return maxSize;
}