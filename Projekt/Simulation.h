#pragma once
#include "Worm.h"
#include "SimulationConfig.h"
#include "Tile.h"
#include "Egg.h"
#include "AStar.h"
#include <vector>
#include <ctime>

class Simulation{
	SimulationConfig config;
	std::vector <Worm> worms;
	std::vector <std::vector <Tile>> tiles;
	std::vector <Egg> eggs;
	int maxHunger = 20, maxAge = 100, maxSize = 2;
	int boardWidth = 670, boardHeight = 670;
	long long tickTime;
	int deadWorms = 0;
	std::vector <int> searchFood(int headX, int headY, int distance) const;
	std::vector <int> searchClosestFood(std::vector <std::vector <int>> foodTiles, int distance, int headX, int headY) const;
	std::vector <std::vector <int>> findMovement(std::vector <int> headPos, std::vector <int> foodTile);

	int prepareTile() const;
	int prepareTile(int k, int i, int j, std::vector <std::vector <int>> hotspots) const;

	void wormsSystems();
	void wormsPathfind(Worm& worm, int distance);
	void passMovement(Worm& worm, int distance);
	void wormsMove(Worm& worm);
	void freeIfDead(Worm& worm);
	void starveWorm(Worm& worm);
	void ageWorm(Worm& worm);
	void growWorm(Worm& worm);
	void killWorms();
	void layEgg(Worm& worm);
	void hatchEggs();
	void destroyEggs();

	void foodRegenerate();
public:
	Simulation(int tps = 1);
	void simulate();
	void addWorm(int wormsAmount);
	void addWorm(int wormsAmount, int headX, int headY);
	void deleteWorms();
	void deleteEggs();

	void generateBoardRandom(int width, int height);
	void generateBoardHotspot(int width, int height, int hotspotAmount);
	
	void setTickTime(int tps);
	
	std::vector <std::vector <Tile>>& getTilesRef();
	SimulationConfig& getConfigRef();
	std::vector <Worm> getWorms() const;
	std::vector <Egg> getEggs() const;
	int getSimSpeed() const;
	int getDeadWorms() const;
};

