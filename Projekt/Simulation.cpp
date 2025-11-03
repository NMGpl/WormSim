#include "Simulation.h"
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
	config.setMaxSize(maxSize);
	do {
		std::cout << "Podaj startowa ilosc robaczkow: ";
		std::cin >> wormsAmount;
	} while (wormsAmount < 0);
	addWorm(wormsAmount);
	do {
		std::cout << "Podaj szerokosc planszy: ";
		std::cin >> boardWidth;
	} while (boardWidth < 0);

	do {
		std::cout << "Podaj wysokosc planszy: ";
		std::cin >> boardHeight;
	} while (boardHeight < 0);
	prepareBoard();
	
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
	ageWorm();
	starveWorm();
	//addWorm(10);
	killWorm();
	std::cout << "Symulacja " << worms.size() << " robaczkow\n";
	printBoard();
}

void Simulation::starveWorm() {
	for (int i = 0; i < worms.size(); i++) {
		int x = worms[i]->getHeadX();
		int y = worms[i]->getHeadY();
		if (checkGround(x, y) > 0) {
			if (worms[i]->getHunger() > 0) {
				worms[i]->setHunger(worms[i]->getHunger() - 1);
			}
			tiles[x][y]->setFoodAmount(tiles[x][y]->getFoodAmount() - 1);
		} else {
			worms[i]->setHunger(worms[i]->getHunger() + 1);
		}
		std::cout << "Glod robaka " << i << ": " << worms[i]->getHunger() << "\n";
	}
}

int Simulation::checkGround(int wormHeadX, int wormHeadY) {
	return tiles[wormHeadX][wormHeadY]->getFoodAmount();
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
}

void Simulation::addWorm(int wormsAmount) {
	for (int i = 0; i < wormsAmount; i++) {
		Worm* pWorm = new Worm;
		pWorm->setMaxAge(config.getMaxAge());
		pWorm->setMaxHunger(config.getMaxHunger());
		pWorm->setMaxSize(config.getMaxSize());
		worms.push_back(pWorm);
	}
}

void Simulation::prepareBoard() {
	for (int i = 0; i < boardHeight; i++) {
		std::vector<Tile*> row;
		for (int j = 0; j < boardWidth; j++) {
			Tile* pTile = new Tile;
			pTile->setPos(j, i);
			pTile->setFoodAmount(10);
			row.push_back(pTile);
		}
		tiles.push_back(row);
	}
}

void Simulation::printBoard() const {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			std::cout << "[" << tiles[i][j]->getFoodAmount() << "]";
		}
		std::cout << "\n";
	}
}