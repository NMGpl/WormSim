#pragma once
class SimulationConfig{
	int maxAge, maxHunger, maxSize;
public:
	SimulationConfig(int maxAge = 100, int maxHunger = 20, int maxSize = 4);
	void setMaxAge(int maxAge);
	void setMaxHunger(int maxHunger);
	void setMaxSize(int maxSize);
	int getMaxAge();
	int getMaxHunger();
	int getMaxSize();
};

