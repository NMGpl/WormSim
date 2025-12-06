#pragma once
class SimulationConfig{
	int maxAge, maxHunger, maxSize, regenSpeed;
public:
	SimulationConfig(int maxAge = 100, int maxHunger = 20, int maxSize = 4);
	void setMaxAge(int maxAge);
	void setMaxHunger(int maxHunger);
	void setMaxSize(int maxSize);
	void setRegenSpeed(int regenSpeed);
	int getMaxAge();
	int getMaxHunger();
	int getMaxSize();
	int getRegenSpeed();
};

