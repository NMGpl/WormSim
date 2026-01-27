#include "Simulation.h"

Simulation::Simulation(int width, int height, int tps) {
	this->boardWidth = width;
	this->boardHeight = height;
	setTickTime(tps);
	config.setWidth(width);
	config.setHeight(height);
}

void Simulation::simulate() {
	if (timePassed()) {
		wormsSystems();
		foodRegenerate();
		hatchEggs();
	}
}

bool Simulation::timePassed() {
	tickTime = getSimSpeed();
	auto now = std::chrono::high_resolution_clock::now();
	if (tickTime != 0 && now - lastTick >= std::chrono::nanoseconds(tickTime)) {
		lastTick += std::chrono::nanoseconds(tickTime);
		return true;
	} else if (tickTime == 0) {
		lastTick = std::chrono::high_resolution_clock::now();
	}
	return false;
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
		int posX = rand() % (config.getWidth());
		int posY = rand() % (config.getHeight());
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
				tiles[headX][headY].modifyFoodAmount(-3);
				worm.modifyHunger(3);
				break;
			case 2:
				tiles[headX][headY].modifyFoodAmount(-2);
				worm.modifyHunger(2);
				break;
			case 1:
				tiles[headX][headY].modifyFoodAmount(-1);
				worm.modifyHunger(1);
				break;
			default:
				worm.modifyHunger(-1);
		}
		if (worm.getHunger() > worm.getMaxHunger()) {
			worm.setHunger(worm.getMaxHunger());
		}
	}
	
}

void Simulation::growWorm(Worm& worm) {
	if (worm.getSize() < worm.getMaxSize() && worm.getHunger() >= 3 * (worm.getMaxHunger() / 4) && !worm.isDead()) {
		worm.grow();
		worm.modifyHunger(-(worm.getMaxHunger() / 2));
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
	if ((worm.getSize() > (worm.getMaxSize() / 2)) && (worm.getAge() < worm.getMaxProductivity()) && worm.getEggCooldown() == 0) {
		int tailX = worm.getSegments()[worm.getSize() - 1][0];
		int tailY = worm.getSegments()[worm.getSize() - 1][1];
		Egg egg(tailX, tailY, config.getNewWormsAmount());
		eggs.push_back(egg);
		worm.modifyEggCooldown(worm.getMaxProductivity() / 3);
	}
	worm.modifyEggCooldown(-1);
}

void Simulation::addWorm(int wormsAmount) {
	for (int i = 0; i < wormsAmount; i++) {
		std::vector <int> headXY = { rand() % config.getWidth(), rand() % config.getHeight()};
		Worm worm(headXY[0], headXY[1], config.getMaxAge(), config.getMaxHunger(), config.getMaxSize(), config.getMaxProductivity());
		worms.push_back(worm);
	}
}

void Simulation::addWorm(int wormsAmount, int headX, int headY) {
	for (int i = 0; i < wormsAmount; i++) {
		Worm worm(headX, headY, config.getMaxAge(), config.getMaxHunger(), config.getMaxSize(), config.getMaxProductivity());
		worms.push_back(worm);
	}
}

void Simulation::addFood(int foodAmount, int posX, int posY) {
	tiles[posX][posY].modifyFoodAmount(foodAmount);
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

std::vector <Worm> Simulation::getWorms() const {
	return worms;
}

std::vector <Egg> Simulation::getEggs() const {
	return eggs;
}

int Simulation::getDeadWorms() const {
	return deadWorms;
}

void Simulation::setTickTime(int tps) {
	if (tps != 0) {
		tickTime = 1000000000 / tps;
	} else {
		tickTime = tps;
	}
}

int Simulation::getSimSpeed() const {
	return tickTime;
}

std::vector <int> Simulation::searchFood(int headX, int headY, int distance) const {
	std::vector <int> foodTile;
	std::vector <std::vector <int>> foodTiles;
	int food = 0;
	int maxFood = 0;
	for (int i = headX - distance; i < headX + distance; i++) {
		for (int j = headY - distance; j < headY + distance; j++) {
			if (i < 0 || j < 0 || i >= tiles.size() || j >= tiles[0].size()) continue;
			int kolo = (i - headX) * (i - headX) + (j - headY) * (j - headY);
			if (kolo < distance * distance + distance/* / 10*/) {
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
		} while (!(kolo < distance * distance + distance/* / 10*/));
		
		foodTile = { x, y, 0 };
		return foodTile;
	}
	return foodTile;
}

std::vector <int> Simulation::searchClosestFood(std::vector <std::vector <int>> foodTiles, int distance, int headX, int headY) const {
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
		if (nextMove[0] >= config.getWidth() || 
							nextMove[1] >= config.getHeight() || 
							food[0] >= config.getWidth() || 
							food[1] >= config.getHeight() || 
							!tiles[nextMove[0]][nextMove[1]].isFree() ||
							!tiles[food[0]][food[1]].isFree()) {
			passMovement(worm, distance);
		}
	}
}

void Simulation::passMovement(Worm& worm, int distance) {
	std::vector <int> foodTile = searchFood(worm.getHeadX(), worm.getHeadY(), distance);
	std::vector <int> wormPos = { worm.getHeadX(), worm.getHeadY() };
	std::vector <std::vector <int>> movement = findMovement(wormPos, foodTile);
	worm.setMovement(movement);
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
	for (int i = 0; i < width; i++) {
		std::vector<Tile> row;
		for (int j = 0; j < height; j++) {
			Tile tileFood(i, j, prepareTile());
			row.push_back(tileFood);
			//tiles[i][j].modifyFoodAmount(prepareTile());
		}
		tiles.push_back(row);
	}
	this->tiles = tiles;
}

void Simulation::addFoodRandom(int width, int height) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			tiles[i][j].modifyFoodAmount(prepareTile());
		}
	}
}

void Simulation::addFoodHotspot(int width, int height) {
	std::vector <int> hotspot;
	hotspot.push_back(rand() % (width));
	hotspot.push_back(rand() % (height));

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int hotspotFood = 0;
			int tileFood = 0;
			hotspotFood = prepareTile(i, j, hotspot);
			tiles[i][j].modifyFoodAmount(hotspotFood);
		}
	}
}

//void Simulation::generateBoardHotspot(int width, int height, int hotspotAmount) {
//	std::vector <std::vector <Tile>> tiles;
//	for (int i = 0; i < width; i++) {
//		std::vector <Tile> row;
//		for (int j = 0; j < height; j++) {
//			Tile tileFood(i, j, 0);
//			row.push_back(tileFood);
//		}
//		tiles.push_back(row);
//	}
//	std::vector <std::vector <int>> hotspots;
//	for (int i = 0; i < hotspotAmount; i++) {
//		std::vector <int> hotspot;
//		hotspot.push_back(rand() % (width));
//		hotspot.push_back(rand() % (height));
//		hotspots.push_back(hotspot);
//	}
//	for (int i = 0; i < width; i++) {
//		for (int j = 0; j < height; j++) {
//			int hotspotFood = 0;
//			int tileFood = 0;
//			for (int k = 0; k < hotspotAmount; k++) {
//				hotspotFood = prepareTile(k, i, j, hotspots);
//				if (hotspotFood > tileFood) {
//					tileFood = hotspotFood;
//				}
//			}
//			tiles[i][j].setFoodAmount(tileFood);
//		}
//	}
//	this->tiles = tiles;
//}

std::vector <std::vector <Tile>>& Simulation::getTilesRef() {
	return tiles;
}

SimulationConfig& Simulation::getConfigRef() {
	return config;
}

int Simulation::prepareTile() const {
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

int Simulation::prepareTile(int i, int j, std::vector <int> hotspot) const {
	int kolo = (i - hotspot[0]) * (i - hotspot[0]) + (j - hotspot[1]) * (j - hotspot[1]);
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

int Simulation::getBoardWidth() const {
	return boardWidth;
}

int Simulation::getBoardHeight() const {
	return boardHeight;
}
void Simulation::resizeBoard() {
	Tile newTile(0, 0, 0);
	int newWidth = config.getWidth();
	int newHeight = config.getHeight();

	if (newWidth < 1) {
		newWidth = 1;
		config.setWidth(1);
	}
	else if (newWidth > boardWidth * 10) {
		newWidth = boardWidth * 10;
		config.setWidth(boardWidth * 10);
	}
	if (newHeight < 1) {
		newHeight = 1;
		config.setHeight(1);
	}
	else if (newHeight > boardHeight * 10) {
		newHeight = boardHeight * 10;
		config.setHeight(boardHeight * 10);
	}

	tiles.resize(newWidth);
	for (std::vector <Tile>& row : tiles) {
		row.resize(newHeight, newTile);
	}
	fixNewTiles();
	deleteOutOfBounds();
}

void Simulation::fixNewTiles() {
	for (int i = 0; i < config.getWidth(); i++) {
		for (int j = 0; j < config.getHeight(); j++) {
			tiles[i][j].setPos(i, j);
		}
	}
}

void Simulation::deleteOutOfBounds() {
	int maxWidth = config.getWidth();
	int maxHeight = config.getHeight();

	auto newEnd = std::remove_if(worms.begin(), worms.end(), [maxWidth, maxHeight](Worm worm) {
		bool bodyOutOfBounds = false;
		for (auto segment : worm.getSegments()) {
			if (segment[0] >= maxWidth || segment[1] >= maxHeight) {
				bodyOutOfBounds = true;
			}
		}
		return worm.getHeadX() >= maxWidth || worm.getHeadY() >= maxHeight || bodyOutOfBounds;
		});
	worms.erase(newEnd, worms.end());

	auto newEndd = std::remove_if(eggs.begin(), eggs.end(), [maxWidth, maxHeight](Egg egg) {
		return egg.getX() >= maxWidth || egg.getY() >= maxHeight;
		});
	eggs.erase(newEndd, eggs.end());
}