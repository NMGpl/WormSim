#include "Simulation.h"
#include "Board.h"
#include "Worm.h"
#include "SimulationConfig.h"
#include <iostream>

void Simulation::start() {
	int maxAge, maxHunger, maxSize;
	Board board;
	Worm worm;
	SimulationConfig config;
	do {
		std::cout << "Podaj maksymalny wiek robaczka: ";
		std::cin >> maxAge;
	} while (maxAge <= 0);
	config.setMaxAge(maxAge);
	do {
		std::cout << "Podaj tolerancje na glod robaczka: ";
		std::cin >> maxHunger;
	} while (maxHunger <= 0);
	config.setMaxHunger(maxHunger);
	do {
		std::cout << "Podaj maksymalna wielkosc robaczka: ";
		std::cin >> maxSize;
	} while (maxSize < 0);
	config.setMaxSize(maxSize);
	board.initializeBoard();
	worm.initializeWorm();
}

void Simulation::step() {
	board
}