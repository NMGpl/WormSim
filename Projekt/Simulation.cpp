#include "Simulation.h"
#include "Worm.h"
#include "SimulationConfig.h"
#include <iostream>
#include <ctime>
#include <vector>

//void Simulation::setup() {
//	int maxAge, maxHunger, maxSize, wormsAmount;
//	do {
//		std::cout << "Podaj szerokosc planszy: ";
//		std::cin >> boardWidth;
//	} while (boardWidth < 0);
//
//	do {
//		std::cout << "Podaj wysokosc planszy: ";
//		std::cin >> boardHeight;
//	} while (boardHeight < 0);
//	//prepareBoard();
//
//	do {
//		std::cout << "Podaj maksymalny wiek robaczka: ";
//		std::cin >> maxAge;
//	} while (maxAge <= 0);
//	config.setMaxAge(maxAge);
//
//	do {
//		std::cout << "Podaj tolerancje na glod robaczka: ";
//		std::cin >> maxHunger;
//	} while (maxHunger <= 0);
//	config.setMaxHunger(maxHunger);
//
//	do {
//		std::cout << "Podaj maksymalna wielkosc robaczka: ";
//		std::cin >> maxSize;
//	} while (maxSize < 0);
//	config.setMaxSize(maxSize);
//
//	do {
//		std::cout << "Podaj startowa ilosc robaczkow: ";
//		std::cin >> wormsAmount;
//	} while (wormsAmount < 0);
//	addWorm(wormsAmount);
//}

//void Simulation::printConfig() const {
//	config.printConfig();
//}

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

//void Simulation::step() {
//	addWorm(1);
//	ageWorm();
//	starveWorm();
//	killWorm();
//	std::cout << "Symulacja " << worms.size() << " robaczkow\n";
//	printBoard();
//}

//void Simulation::starveWorm() {
//	for (int i = 0; i < worms.size(); i++) {
//		int x = worms[i]->getHeadX();
//		int y = worms[i]->getHeadY();
//		if (checkGround(y, x) > 0) {
//			if (worms[i]->getHunger() > 0) {
//				worms[i]->setHunger(worms[i]->getHunger() - 1);
//			}
//			tiles[y][x]->setFoodAmount(tiles[y][x]->getFoodAmount() - 1);
//		} else {
//			worms[i]->setHunger(worms[i]->getHunger() + 1);
//		}
//	}
//}
//
//int Simulation::checkGround(int wormHeadX, int wormHeadY) {
//	return tiles[wormHeadX][wormHeadY]->getFoodAmount();
//}

//void Simulation::killWorm() {
//	auto newEnd = std::remove_if(worms.begin(), worms.end(), [](Worm* worm) {
//		return worm->isDead();
//	});
//	worms.erase(newEnd, worms.end());
//}

//void Simulation::ageWorm() {
//	for (int i = 0; i < worms.size(); i++) {
//		worms[i]->ageUp();
//	}
//}

//void Simulation::addWorm(int wormsAmount) {
//	srand(time(0));
//	for (int i = 0; i < wormsAmount; i++) {
//		Worm* pWorm = new Worm(rand() % boardWidth, rand() % boardHeight);
//		pWorm->setMaxAge(config.getMaxAge());
//		pWorm->setMaxHunger(config.getMaxHunger());
//		pWorm->setMaxSize(config.getMaxSize());
//		//pWorm->setHeadCords(rand() % boardWidth, rand() % boardHeight);
//		worms.push_back(pWorm);
//	}
//}

//void Simulation::prepareBoard(int width, int height) {
//	for (int i = 0; i < height; i++) {
//		std::vector<Tile*> row;
//		for (int j = 0; j < width; j++) {
//			Tile* pTile = new Tile;
//			pTile->setPos(j, i);
//			pTile->setFoodAmount(10);
//			row.push_back(pTile);
//		}
//		tiles.push_back(row);
//	}
//}

////////////////////////////////////////////////////////////////////////////////////////
//std::vector <std::vector <Tile>> Simulation::generateBoard(int width, int height) {
//	std::vector <std::vector <Tile>> tiles;
//	for (int i = 0; i < width / 10; i ++) {
//		std::vector<Tile> row;
//		for (int j = 0; j < height / 10; j ++) {
//			Tile tile = prepareTile();
//			int tileFood = tile.getFoodAmount();
//			row.push_back(tile);
//		}
//		tiles.push_back(row);
//	}
//	return tiles;
//}

std::vector <std::vector <int>> Simulation::generateBoardRandom(int width, int height) {
	std::vector <std::vector <int>> tiles;
	for (int i = 0; i < width / 10; i++) {
		std::vector<int> row;
		for (int j = 0; j < height / 10; j++) {
			int tileFood = prepareTile();
			row.push_back(tileFood);
		}
		tiles.push_back(row);
	}
	return tiles;
}

int Simulation::prepareTile() {
	int r = rand() % 100;
	if (r <= 75) {
		int food = 0;
		return food;
	} else if (r <= 85){
		int food = 1;
		return food;
	} else if (r <= 95){
		int food = 2;
		return food;
	} else {
		int food = 3;
		return food;
	}
}
/// ///////////////////////////////////////////////////////////////////////////////////
//void Simulation::printBoard() const {
//	for (int i = 0; i < boardHeight; i++) {
//		for (int j = 0; j < boardWidth; j++) {
//			std::cout << "[" << tiles[i][j]->getFoodAmount() << "]";
//		}
//		std::cout << "\n";
//	}
//}