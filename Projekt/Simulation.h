#pragma once
#include "Worm.h"
#include "Board.h"
#include "SimulationConfig.h"
#include<vector>

class Simulation{
	//Worm worms[10];
	Board board;
	SimulationConfig config;
	std::vector<Worm*> worms;
public:
	void setup();
	void step();
	void printConfig() const;
	void addWorm(int wormsAmount);
};

