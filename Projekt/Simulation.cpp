#include "Simulation.h"
#include "Board.h"
#include "Worm.h"
#include "SimulationConfig.h"
#include <iostream>

void Simulation::setup() {
	int maxAge, maxHunger, maxSize, wormsAmount;
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
	do {
		std::cout << "Podaj startowa ilosc robaczkow: ";
		std::cin >> wormsAmount;
	} while (wormsAmount < 0);
	config.setMaxSize(maxSize);
	addWorm(wormsAmount);
}

void Simulation::printConfig() const {
	config.printConfig();
}

//void Simulation::step() {
//	std::cout << worms.size() << " robaczkow\n";
//	for (int i = 0; i < worms.size(); i++) {
//		worms[i]->ageUp();
//		std::cout << "Robaczek " << i << " martwy?" << worms[i]->isDead() << "\n";
//		/*std::cout << "Jestem robak " << i << " mam " << worms[i]->getAge() << std::endl;*/
//	}
//	/*for (auto i : worms) {
//		std::cout << i;
//	}*/
//	auto newEnd = std::remove_if(worms.begin(), worms.end(), [](Worm* worm) {
//		return worm->isDead();
//	});
//	worms.erase(newEnd, worms.end());
//}

void Simulation::step() {
	std::cout << "Symulacja " << worms.size() << " robaczkow\n";
	ageWorm();
	killWorm();
	addWorm(1);
}

void Simulation::killWorm() {
	auto newEnd = std::remove_if(worms.begin(), worms.end(), [](Worm* worm) {
		return worm->isDead();
	});
	worms.erase(newEnd, worms.end());
}

void Simulation::ageWorm() {
	for (int i = 0; i < worms.size(); i++) {
		worms[i]->ageUp();
	}
	killWorm();
}

void Simulation::addWorm(int wormsAmount) {
	for (int i = 0; i < wormsAmount; i++) {
		Worm* pWorm = new Worm;
		pWorm->setMaxAge(config.getMaxAge()+i);
		pWorm->setMaxHunger(config.getMaxHunger());
		pWorm->setMaxSize(config.getMaxSize());
		worms.push_back(pWorm);
	}
}