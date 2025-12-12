#pragma once
#include "Worm.h"
#include "SimulationConfig.h"
#include "Tile.h"
#include "Egg.h"
#include<vector>

class Simulation{
	SimulationConfig config;
	std::vector <Worm> worms;
	//std::vector <std::vector <int>> tiles;
	std::vector <std::vector <Tile>> tiles;
	std::vector <Egg> eggs;
	int maxHunger = 20, maxAge = 100, maxSize = 2;
	int boardWidth = 670, boardHeight = 670;
	long long tickTime;
public:
	//void setup();
	//void step();
	//void printConfig() const;
	Simulation(int tps = 1);
	void simulate();
	void addWorm(int wormsAmount);
	void addWorm(int wormsAmount, int headX, int headY);
	void deleteWorms();
	void deleteEggs();
	void starveWorm(Worm& worm);
	void ageWorm(Worm& worm);
	void growWorm(Worm& worm);
	void killWorms();
	void layEgg(Worm& worm);
	void hatchEggs();
	void destroyEggs();
	std::vector <std::vector <Tile>>& getTilesRef();
	SimulationConfig& getConfigRef();
	std::vector <Worm> getWorms();
	std::vector <Egg> getEggs();
	std::vector <int> searchFood(int headX, int headY, int distance);
	std::vector <int> searchClosestFood(std::vector <std::vector <int>> foodTiles, int distance, int headX, int headY);
	void wormsPathfind(int distance);
	void wormsMove();
	void wormsSystems();
	void foodRegenerate();
	void setTickTime(int tps);
	int getSimSpeed();
	//void prepareBoard(int width, int height);
	int prepareTile();
	int prepareTile(int k, int i, int j, std::vector <std::vector <int>> hotspots);
	std::vector <std::vector <int>> findMovement(std::vector <int> headPos, std::vector <int> foodTile);
	//void ageWorm();
	//void starveWorm();
	//void killWorm();
	//int checkGround(int wormHeadX, int wormHeadY);
	//void printBoard() const;

	//std::vector <std::vector <Tile>> generateBoard(int width, int height);
	void generateBoardRandom(int width, int height);
	void generateBoardHotspot(int width, int height, int hotspotAmount);
};

