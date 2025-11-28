#pragma once
#include "Worm.h"
#include "SimulationConfig.h"
#include "Tile.h"
#include<vector>

class Simulation{
	SimulationConfig config;
	std::vector <Worm> worms;
	std::vector <std::vector <int>> tiles;
	int boardWidth, boardHeight;
public:
	//void setup();
	//void step();
	//void printConfig() const;
	void simulate();
	void addWorm(int wormsAmount);
	void deleteWorms();
	std::vector <Worm> getWorms();
	std::vector <int> searchFood(int headX, int headY, int distance);
	std::vector <int> searchClosestFood(std::vector <std::vector <int>> foodTiles, int distance, int headX, int headY);
	void wormsPathfind(int distance);
	void wormsMove();
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
	std::vector <std::vector <int>> generateBoardRandom(int width, int height);
	std::vector <std::vector <int>> generateBoardHotspot(int width, int height, int hotspotAmount);
};

