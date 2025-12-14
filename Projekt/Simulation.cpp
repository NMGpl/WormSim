#include "Simulation.h"
#include "Worm.h"
#include "SimulationConfig.h"
#include "Egg.h"
#include <iostream>
#include <ctime>
#include <vector>

Simulation::Simulation(int tps) {
	setTickTime(tps);
}

void Simulation::simulate() {
	wormsSystems();
	foodRegenerate();
	hatchEggs();
}

void Simulation::wormsSystems() {
	for (Worm& worm : worms) {
		wormsPathfind(worm, 10);
		wormsMove(worm);
		ageWorm(worm);
		starveWorm(worm);
		growWorm(worm);
		layEgg(worm);
		freeIfDead(worm);
	}
	killWorms();
}

void Simulation::freeIfDead(Worm& worm) {
	if (worm.isDead()) {
		tiles[worm.getHeadX()][worm.getHeadY()].setFree(true);
		for (auto segment : worm.getSegments()) {
			tiles[segment[0]][segment[1]].setFree(true);
		}
		deadWorms++;
	}
}

void Simulation::foodRegenerate() {
	for (int i = 0; i < config.getRegenSpeed(); i++) {
		int posX = rand() % ((boardWidth + 1) / 10);
		int posY = rand() % ((boardHeight + 1) / 10);
		int food = tiles[posX][posY].getFoodAmount();
		if (food < 3) {
			tiles[posX][posY].modifyFoodAmount(1);
		}
	}
}

void Simulation::hatchEggs() {
	bool hatched;
	for (Egg& egg : eggs) {
		hatched = egg.hatch();
		tiles[egg.getX()][egg.getY()].setFree(false);
		if (hatched) {
			addWorm(egg.getNewWorms(), egg.getX(), egg.getY());
			tiles[egg.getX()][egg.getY()].setFree(true);
		}
	}
	destroyEggs();
}

void Simulation::destroyEggs() {
	auto newEnd = std::remove_if(eggs.begin(), eggs.end(), [](Egg egg) {
		return egg.isHatched();
		});
	eggs.erase(newEnd, eggs.end());
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
		int tileFood = tiles[headX][headY].getFoodAmount();
		switch (tileFood) {
			case 3:
				tiles[headX][headY].modifyFoodAmount(-4);
				worm.modifyHunger(3);
				break;
			case 2:
				tiles[headX][headY].modifyFoodAmount(-3);
				worm.modifyHunger(2);
				break;
			case 1:
				tiles[headX][headY].modifyFoodAmount(-2);
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
	if (worm.getSize() < worm.getMaxSize() && worm.getHunger() >= 3 * (worm.getMaxHunger() / 4) && !worm.isDead()) {
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

void Simulation::layEgg(Worm& worm) {
	if ((worm.getSize() > (worm.getMaxSize() / 2)) && (worm.getAge() < worm.getMaxProductivity()) && (rand() % 101) > 92) {
		int tailX = worm.getSegments()[worm.getSize() - 1][0];
		int tailY = worm.getSegments()[worm.getSize() - 1][1];
		Egg egg(tailX, tailY, config.getNewWormsAmount());
		eggs.push_back(egg);
	}
}

void Simulation::addWorm(int wormsAmount) {
	for (int i = 0; i < wormsAmount; i++) {
		std::vector <int> headXY = { rand() % (670 / 10), rand() % (670 / 10) };
		Worm worm(headXY[0], headXY[1], config.getMaxAge(), config.getMaxHunger(), config.getMaxSize(), config.getMaxProductivity());
		worms.push_back(worm);
	}
}

void Simulation::addWorm(int wormsAmount, int headX, int headY) {
	for (int i = 0; i < wormsAmount; i++) {
		Worm worm(headX, headY, config.getMaxAge(), config.getMaxHunger(), config.getMaxSize());
		worms.push_back(worm);
	}
}

void Simulation::deleteWorms() {
	for (Worm& worm : worms) {
		tiles[worm.getHeadX()][worm.getHeadY()].setFree(true);
		for (auto segment : worm.getSegments()) {
			tiles[segment[0]][segment[1]].setFree(true);
		}
	}
	deadWorms = 0;
	worms.clear();
}

void Simulation::deleteEggs() {
	for (Egg& egg : eggs) {
		tiles[egg.getX()][egg.getY()].setFree(true);
	}
	eggs.clear();
}

std::vector <Worm> Simulation::getWorms() {
	return worms;
}

std::vector <Egg> Simulation::getEggs() {
	return eggs;
}

int Simulation::getDeadWorms() {
	return deadWorms;
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
				food = tiles[i][j].getFoodAmount();
				if (food > 0) {
					foodTiles.push_back({ i, j, food });
					maxFood = food;
				}
			}
		}
	}
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

void Simulation::wormsPathfind(Worm& worm, int distance) {
	bool needMovement = worm.getMovement().empty();
	if (needMovement) {
		passMovement(worm, distance);
	}
	needMovement = worm.getMovement().empty();
	if (!needMovement) {
		std::vector <int>& nextMove = worm.getMovement().back();
		std::vector <int>& food = worm.getMovement()[0];
		if (!tiles[nextMove[0]][nextMove[1]].isFree() || !tiles[food[0]][food[1]].isFree()) {
			passMovement(worm, distance);
		}
	}
}

void Simulation::passMovement(Worm& worm, int distance) {
	std::vector <int> foodTile = searchFood(worm.getHeadX(), worm.getHeadY(), distance);
	std::vector <int> wormPos = { worm.getHeadX(), worm.getHeadY() };
	std::vector <std::vector <int>> movement = findMovement(wormPos, foodTile);
	if (!movement.empty()) {
		worm.setMovement(movement);
	}
}

std::vector <std::vector <int>> Simulation::findMovement(std::vector <int> wormPos, std::vector <int> foodTile) {
	Tile start(wormPos[0], wormPos[1]);
	Tile goal(foodTile[0], foodTile[1]);
	AStar aStar(start, goal, getTilesRef());
	std::vector <std::vector <int>> movement = aStar.findMovement();

	return movement;
}

void Simulation::wormsMove(Worm& worm) {
	if (worm.getSize() > 0) {
		std::vector <int> lastSegmentXY = worm.getSegments().back();
		tiles[lastSegmentXY[0]][lastSegmentXY[1]].setFree(true);
	}
	else {
		tiles[worm.getHeadX()][worm.getHeadY()].setFree(true);
	}
	worm.move();
	tiles[worm.getHeadX()][worm.getHeadY()].setFree(false);

	std::vector <std::vector <int>>& movement = worm.getMovement();
	if (!movement.empty()) {
		std::vector <int> nextMove = worm.getMovement().back();
		//tiles[nextMove[0]][nextMove[1]].wantToMove(1);
	}
}

void Simulation::generateBoardRandom(int width, int height) {
	std::vector <std::vector <Tile>> tiles;
	for (int i = 0; i < width / 10; i++) {
		std::vector<Tile> row;
		for (int j = 0; j < height / 10; j++) {
			Tile tileFood(i, j, prepareTile());
			row.push_back(tileFood);
		}
		tiles.push_back(row);
	}
	this->tiles = tiles;
}

void Simulation::generateBoardHotspot(int width, int height, int hotspotAmount) {
	std::vector <std::vector <Tile>> tiles;
	for (int i = 0; i < width / 10; i++) {
		std::vector <Tile> row;
		for (int j = 0; j < height / 10; j++) {
			Tile tileFood(i, j, 0);
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
			tiles[i][j].setFoodAmount(tileFood);
		}
	}
	this->tiles = tiles;
}

std::vector <std::vector <Tile>>& Simulation::getTilesRef() {
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