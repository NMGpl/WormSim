#pragma once
class SimulationConfig{
	int maxAge, maxHunger, maxSize, regenSpeed, maxProductivity, newWormsAmount;
public:
	SimulationConfig(int maxAge = 200, int maxHunger = 20, int maxSize = 4, int regenSpeed = 50, int maxProductivity = 175, int newWormsAmount = 2);
	void setMaxAge(int maxAge);
	void setMaxHunger(int maxHunger);
	void setMaxSize(int maxSize);
	void setRegenSpeed(int regenSpeed);
	void setMaxProductivity(int maxProductivity);
	void setNewWormsAmount(int newWormsAmount);
	int getMaxAge();
	int getMaxHunger();
	int getMaxSize();
	int getRegenSpeed();
	int getMaxProductivity();
	int getNewWormsAmount();
};

