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



//void Simulation::ageWorm() {
//	for (int i = 0; i < worms.size(); i++) {
//		worms[i]->ageUp();
//	}
//}

Simulation::Simulation(int tps) {
	setTickTime(tps);
}

void Simulation::simulate() {
	wormsPathfind(10);
	wormsMove();
	wormsSystems();
	foodRegenerate();
}

void Simulation::wormsSystems() {
	for (Worm& worm : worms) {
		ageWorm(worm);
		starveWorm(worm);
		growWorm(worm);
	}
	killWorms();
}

void Simulation::foodRegenerate() {
	for (int i = 0; i < config.getRegenSpeed(); i++) {
		int posX = rand() % ((boardWidth + 1) / 10);
		int posY = rand() % ((boardHeight + 1) / 10);
		int food = tiles[posX][posY];
		if (food < 3) {
			tiles[posX][posY]++;
		}
	}
}

void Simulation::killWorms() {
	auto newEnd = std::remove_if(worms.begin(), worms.end(), [](Worm worm) {
		return worm.isDead();
	});
	worms.erase(newEnd, worms.end());
}

void Simulation::starveWorm(Worm& worm) {
	if (worm.getHunger() <= 0 || worm.isDead()) {
		worm.die();
	} else {
		int headX = worm.getHeadX();
		int headY = worm.getHeadY();
		int tileFood = tiles[headX][headY];
		switch (tileFood) {
			case 3:
				tiles[headX][headY] -= 3;
				worm.modifyHunger(3);
				break;
			case 2:
				tiles[headX][headY] -= 2;
				worm.modifyHunger(2);
				break;
			case 1:
				tiles[headX][headY] -= 1;
				worm.modifyHunger(1);
				break;
		}
		if (worm.getHunger() > worm.getMaxHunger()) {
			worm.setHunger(worm.getMaxHunger());
		}
	}
	worm.modifyHunger(-1);
}

void Simulation::growWorm(Worm& worm) {
	if (worm.getSize() < worm.getMaxSize() && worm.getHunger() >= 15 && !worm.isDead()) {
		worm.grow();
		worm.modifyHunger(-10);
	}
}

void Simulation::ageWorm(Worm& worm) {
	if (worm.getAge() >= worm.getMaxAge()) {
		worm.die();
	} else {
		worm.modifyAge(1);
	}
}

void Simulation::addWorm(int wormsAmount) {
	for (int i = 0; i < wormsAmount; i++) {
		std::vector <int> headXY = { rand() % (670 / 10), rand() % (670 / 10) };
		Worm worm(headXY[0], headXY[1], config.getMaxAge(), config.getMaxHunger(), config.getMaxSize());
		worms.push_back(worm);
	}
}

void Simulation::deleteWorms() {
	worms.clear();
}

std::vector <Worm> Simulation::getWorms() {
	return worms;
}

void Simulation::setTickTime(int tps) {
	if (tps != 0) {
		tickTime = 1000000000 / tps;
	} else {
		tickTime = tps;
	}
}

int Simulation::getSimSpeed() {
	return tickTime;
}
//std::vector <int> Simulation::searchFood(int headX, int headY, int distance) {
//	//????? TODO: generowanie od wewnatrz
//	std::vector <int> foodTile;
//	std::vector <std::vector <int>> temp;
//	int food = 0;
//	bool found = false;
//	for (int i = 0; i < distance; i++) {
//		int nHeadY = headY - i;
//		int nHeadX = headX + i;
//
//		if (nHeadX < 0 || nHeadX >= tiles.size())
//			continue;
//
//		if (nHeadY < 0 || nHeadY >= tiles[0].size())
//			continue;
//
//		temp.push_back({ headX, nHeadY });
//		if (tiles[temp.back()[0]][temp.back()[1]] > food) {
//			food = tiles[temp.back()[0]][temp.back()[1]];
//			foodTile = temp.back();
//		}
//		//prawo gora
//		for (int j = i - 1; j > 0; j--) {
//			temp.push_back({ headX + (i - j), nHeadY + (i - j) });
//			if (tiles[temp.back()[0]][temp.back()[1]] > food) {
//				food = tiles[temp.back()[0]][temp.back()[1]];
//				foodTile = temp.back();
//			}
//		}
//		temp.push_back({ nHeadX, headY });
//		if (tiles[temp.back()[0]][temp.back()[1]] > food) {
//			food = tiles[temp.back()[0]][temp.back()[1]];
//			foodTile = temp.back();
//		}
//		//prawo dol
//		for (int j = i - 1; j > 0; j--) {
//			temp.push_back({ nHeadX - (i - j), headY + (i - j) });
//			if (tiles[temp.back()[0]][temp.back()[1]] > food) {
//				food = tiles[temp.back()[0]][temp.back()[1]];
//				foodTile = temp.back();
//			}
//		}
//		nHeadY = headY + i;
//		nHeadX = headX - i;
//
//		if (nHeadX < 0 || nHeadX >= tiles.size())
//			continue;
//
//		if (nHeadY < 0 || nHeadY >= tiles[0].size())
//			continue;
//
//		temp.push_back({ headX, nHeadY });
//		if (tiles[temp.back()[0]][temp.back()[1]] > food) {
//			food = tiles[temp.back()[0]][temp.back()[1]];
//			foodTile = temp.back();
//		}
//		//lewo dol
//		for (int j = i - 1; j > 0; j--) {
//			temp.push_back({ headX - (i - j), nHeadY - (i - j) });
//			if (tiles[temp.back()[0]][temp.back()[1]] > food) {
//				food = tiles[temp.back()[0]][temp.back()[1]];
//				foodTile = temp.back();
//			}
//		}
//		temp.push_back({ nHeadX, headY });
//		if (tiles[temp.back()[0]][temp.back()[1]] > food) {
//			food = tiles[temp.back()[0]][temp.back()[1]];
//			foodTile = temp.back();
//		}
//		//lewo gora
//		for (int j = i - 1; j > 0; j--) {
//			temp.push_back({ nHeadX + (i - j), headY - (i - j) });
//			if (tiles[temp.back()[0]][temp.back()[1]] > food) {
//				food = tiles[temp.back()[0]][temp.back()[1]];
//				foodTile = temp.back();
//			}
//		}
//		if (food > 0) {
//			break;
//		}
//	}
//	
//
//	return foodTile;
//}

std::vector <int> Simulation::searchFood(int headX, int headY, int distance) {
	std::vector <int> foodTile;
	std::vector <std::vector <int>> foodTiles;
	int food = 0;
	int maxFood = 0;
	for (int i = headX - distance; i < headX + distance; i++) {
		for (int j = headY - distance; j < headY + distance; j++) {
			if (i < 0 || j < 0 || i >= tiles.size() || j >= tiles[0].size()) continue;
			int kolo = (i - headX) * (i - headX) + (j - headY) * (j - headY);
			if (kolo < distance * distance + distance / 10) {
				food = tiles[i][j];
				if (food > 0) {
					foodTiles.push_back({ i, j, food });
					maxFood = food;
				}
			}
		}
	}
	//if (maxFood == 0) robi blad w 1% przypadkow???????????????
	foodTile = searchClosestFood(foodTiles, distance, headX, headY);
	if (foodTile.empty()) {
		int x, y;
		int kolo;
		do {
			do {
				x = headX - distance + (rand() % (2 * distance + 1));
			} while (x < 0 || x >= tiles.size());
			do {
				y = headY - distance + (rand() % (2 * distance + 1));
			} while (y < 0 || y >= tiles[0].size());
			kolo = (x - headX) * (x - headX) + (y - headY) * (y - headY);
		} while (!(kolo < distance * distance + distance / 10));
		
		foodTile = { x, y, 0 };
		return foodTile;
	}
	return foodTile;
}

std::vector <int> Simulation::searchClosestFood(std::vector <std::vector <int>> foodTiles, int distance, int headX, int headY) {
	int food = 0;
	int foodDistance = distance;
	std::vector <int> foodTile;
	for (int i = 0; i < foodTiles.size(); i++) {
		foodDistance = abs(foodTiles[i][0] - headX) + abs(foodTiles[i][1] - headY);
		if (foodDistance < distance || (foodDistance == distance && food < foodTiles[i][2])) {
			foodTile = foodTiles[i];
			food = foodTile[2];
			distance = foodDistance;
		}
	}
	return foodTile;
}

std::vector <std::vector <int>> Simulation::findMovement(std::vector <int> wormPos, std::vector <int> foodTile) {
	std::vector <std::vector <int>> movement = {foodTile};
	//bresenham
	std::vector <int> diff = { abs(wormPos[0] - foodTile[0]), abs(wormPos[1] - foodTile[1]) };
	int moveX, moveY;
	if (foodTile[0] > wormPos[0]) {
		moveX = 1;
	}
	else {
		moveX = -1;
	}
	if (foodTile[1] > wormPos[1]) {
		moveY = 1;
	}
	else {
		moveY = -1;
	}
	int error = diff[0] - diff[1];
	while (true) {
		//movement.push_back({ wormPos[0], wormPos[1] });
		if (wormPos[0] == foodTile[0] && wormPos[1] == foodTile[1]) {
			break;
		}

		int errorMult = 2 * error;

		if (errorMult > -diff[1]) {
			error -= diff[1];
			wormPos[0] += moveX;
			movement.push_back({ wormPos[0], wormPos[1] });
		}
		if (errorMult < diff[0]) {
			error += diff[0];
			wormPos[1] += moveY;
			movement.push_back({ wormPos[0], wormPos[1] });
		}
	}
	return movement;
}

//std::vector<std::vector<int>> Simulation::searchPath(int headX, int headY, int distance)
//{
//	int bestX = headX;
//	int bestY = headY;
//	int bestVal = *tiles[headX][headY];
//
//	auto check = [&](int x, int y) {
//		int val = *tiles[x][y];
//		if (val > bestVal) {
//			bestVal = val;
//			bestX = x;
//			bestY = y;
//		}
//		};
//
//	for (int r = 1; r <= distance; r++) {
//
//		// 4 wierzcho³ki
//		check(headX, headY - r); // góra
//		check(headX + r, headY);     // prawo
//		check(headX, headY + r); // dó³
//		check(headX - r, headY);     // lewo
//
//		// 4 przek¹tne wype³niaj¹ce romb
//		for (int j = 1; j < r; j++) {
//			check(headX + j, headY - (r - j)); // prawa-góra
//			check(headX + (r - j), headY + j); // prawa-dó³
//			check(headX - j, headY + (r - j)); // lewa-dó³
//			check(headX - (r - j), headY - j); // lewa-góra
//		}
//	}
//
//	return { {bestX, bestY} };
//}

void Simulation::wormsPathfind(int distance) {
	for (Worm& worm : worms) {
		if (worm.getMovement().empty()) {
			std::vector <int> foodTile = searchFood(worm.getHeadX(), worm.getHeadY(), distance);
			std::vector <int> wormPos = { worm.getHeadX(), worm.getHeadY() };
			std::vector <std::vector <int>> movement = findMovement(wormPos, foodTile);
			//movement.pop_back();
			std::reverse(movement.begin(), movement.end());
			if (movement.size() != 1) {
				movement.pop_back();
			}
			worm.setMovement(movement);
			//std::cout << worm.getMovement()[0][0] << " " << worm.getMovement()[0][1] << "\n";
		}
	}
}

void Simulation::wormsMove() {
	for (Worm& worm : worms) {
		worm.move();
	}
}
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

void Simulation::generateBoardRandom(int width, int height) {
	std::vector <std::vector <int>> tiles;
	for (int i = 0; i < width / 10; i++) {
		std::vector<int> row;
		for (int j = 0; j < height / 10; j++) {
			int tileFood = prepareTile();
			row.push_back(tileFood);
		}
		tiles.push_back(row);
	}
	this->tiles = tiles;
}

void Simulation::generateBoardHotspot(int width, int height, int hotspotAmount) {
	std::vector <std::vector <int>> tiles;
	for (int i = 0; i < width / 10; i++) {
		std::vector <int> row;
		for (int j = 0; j < height / 10; j++) {
			int tileFood = 0;
			row.push_back(tileFood);
		}
		tiles.push_back(row);
	}
	std::vector <std::vector <int>> hotspots;
	for (int i = 0; i < hotspotAmount; i++) {
		std::vector <int> hotspot;
		hotspot.push_back(rand() % (width / 10));
		hotspot.push_back(rand() % (height / 10));
		hotspots.push_back(hotspot);
	}
	for (int i = 0; i < width / 10; i++) {
		for (int j = 0; j < height / 10; j++) {
			int hotspotFood = 0;
			int tileFood = 0;
			for (int k = 0; k < hotspotAmount; k++) {
				hotspotFood = prepareTile(k, i, j, hotspots);
				if (hotspotFood > tileFood) {
					tileFood = hotspotFood;
				}
			}
			tiles[i][j] = tileFood;
		}
	}
	this->tiles = tiles;
}

std::vector <std::vector <int>>& Simulation::getTilesRef() {
	return tiles;
}

SimulationConfig& Simulation::getConfigRef() {
	return config;
}

int Simulation::prepareTile() {
	int r = rand() % 100;
	if (r <= 60) {
		return 0;
	} else if (r <= 75){
		return 1;
	} else if (r <= 90){
		return 2;
	} else {
		return 3;
	}
}

int Simulation::prepareTile(int k, int i, int j, std::vector <std::vector <int>> hotspots) {
	int kolo = (i - hotspots[k][0]) * (i - hotspots[k][0]) + (j - hotspots[k][1]) * (j - hotspots[k][1]);
	if (kolo <= 48) {
		return 3;
	} else if (kolo <= 80 && kolo > 48) {
		return 2;
	} else if (kolo <= 99 && kolo > 80) {
		return 1;
	} else {
		return 0;
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