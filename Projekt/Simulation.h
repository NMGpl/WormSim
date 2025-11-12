#pragma once
#include "Worm.h"
#include "SimulationConfig.h"
#include "Tile.h"
#include<vector>

class Simulation{
	SimulationConfig config;
	std::vector<int*> worms;
	std::vector<std::vector <int*>> tiles;
	int boardWidth, boardHeight;
public:
	//void setup();
	//void step();
	void printConfig() const;
	//void addWorm(int wormsAmount);
	//void prepareBoard(int width, int height);
	int prepareTile();
	//void ageWorm();
	//void starveWorm();
	//void killWorm();
	//int checkGround(int wormHeadX, int wormHeadY);
	//void printBoard() const;

	//std::vector <std::vector <Tile>> generateBoard(int width, int height);
	std::vector <std::vector <int>> generateBoard(int width, int height);
};

