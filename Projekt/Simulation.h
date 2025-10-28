#pragma once
#include "Worm.h"
#include "SimulationConfig.h"
#include "Tile.h"
#include<vector>

class Simulation{
	SimulationConfig config;
	std::vector<Worm*> worms;
	std::vector<std::vector <Tile*>> tiles;
public:
	void setup();
	void step();
	void printConfig() const;
	void addWorm(int wormsAmount);
	void prepareBoard(int boardWidth, int boardHeight);
	void ageWorm();
	//void starveWorm();
	void killWorm();
	//int checkGround();
};

